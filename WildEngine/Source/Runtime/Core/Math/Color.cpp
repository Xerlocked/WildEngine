﻿// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

/*=============================================================================
	Color.cpp: Unreal color implementation.
=============================================================================*/

#include "CorePrivate.h"

// Common colors.
const FLinearColor FLinearColor::White(1.f,1.f,1.f);
const FLinearColor FLinearColor::Gray(0.5f,0.5f,0.5f);
const FLinearColor FLinearColor::Black(0,0,0);
const FLinearColor FLinearColor::Transparent(0,0,0,0);
const FLinearColor FLinearColor::Red(1.f,0,0);
const FLinearColor FLinearColor::Green(0,1.f,0);
const FLinearColor FLinearColor::Blue(0,0,1.f);
const FLinearColor FLinearColor::Yellow(1.f,1.f,0);

const FColor FColor::White(255,255,255);
const FColor FColor::Black(0,0,0);
const FColor FColor::Red(255,0,0);
const FColor FColor::Green(0,255,0);
const FColor FColor::Blue(0,0,255);
const FColor FColor::Yellow(255,255,0);
const FColor FColor::Cyan(0,255,255);
const FColor FColor::Magenta(255,0,255);

/** 
 * Helper used by FColor -> FLinearColor conversion. We don't use a lookup table as unlike pow, multiplication is fast.
 */
static constexpr float OneOver255 = 1.0f / 255.0f;

//	FColor->FLinearColor conversion.
FLinearColor::FLinearColor(const class FColor& C)
{
	R = PowOneOver255Table[C.R];
	G = PowOneOver255Table[C.G];
	B =	PowOneOver255Table[C.B];
	A =	static_cast<float>(C.A) * OneOver255;
}

FLinearColor::FLinearColor(const class FVector& Vector) :
	R(Vector.X),
	G(Vector.Y),
	B(Vector.Z),
	A(1.0f)
{}

// Convert from float to RGBE as outlined in Gregory Ward's Real Pixels article, Graphics Gems II, page 80.
FColor FLinearColor::ToRGBE() const
{
	const float	Primary = FMath::Max3( R, G, B );
	FColor	Color;

	if( Primary < 1E-32 )
	{
		Color = FColor(0,0,0,0);
	}
	else
	{
		int32	Exponent;
		const float Scale	= frexp(Primary, &Exponent) / Primary * 255.f;

		Color.R		= FMath::Clamp(FMath::Trunc(R * Scale), 0, 255);
		Color.G		= FMath::Clamp(FMath::Trunc(G * Scale), 0, 255);
		Color.B		= FMath::Clamp(FMath::Trunc(B * Scale), 0, 255);
		Color.A		= FMath::Clamp(FMath::Trunc(Exponent),-128,127) + 128;
	}

	return Color;
}


/** Quantizes the linear color and returns the result as a FColor with optional sRGB conversion and quality as goal. */
FColor FLinearColor::ToFColor(const bool bSRGB) const
{
	float FloatR = FMath::Clamp(R, 0.0f, 1.0f);
	float FloatG = FMath::Clamp(G, 0.0f, 1.0f);
	float FloatB = FMath::Clamp(B, 0.0f, 1.0f);
	float FloatA = FMath::Clamp(A, 0.0f, 1.0f);

	if(bSRGB)
	{
		FloatR = FMath::Pow(FloatR, 1.0f / 2.2f);
		FloatG = FMath::Pow(FloatG, 1.0f / 2.2f);
		FloatB = FMath::Pow(FloatB, 1.0f / 2.2f);
	}

	FColor ret;

	ret.A = FMath::Floor(FloatA * 255.999f);
	ret.R = FMath::Floor(FloatR * 255.999f);
	ret.G = FMath::Floor(FloatG * 255.999f);
	ret.B = FMath::Floor(FloatB * 255.999f);

	return ret;
}


FColor FLinearColor::Quantize() const
{
	return {
		(uint8)FMath::Clamp<int32>(FMath::Trunc(R*255.f),0,255),
		(uint8)FMath::Clamp<int32>(FMath::Trunc(G*255.f),0,255),
		(uint8)FMath::Clamp<int32>(FMath::Trunc(B*255.f),0,255),
		(uint8)FMath::Clamp<int32>(FMath::Trunc(A*255.f),0,255)
	};
}

/**
 * Returns a desaturated color, with 0 meaning no desaturation and 1 == full desaturation
 *
 * @param	Desaturation	Desaturation factor in range [0..1]
 * @return	Desaturated color
 */
FLinearColor FLinearColor::Desaturate( float Desaturation ) const
{
	float Lum = ComputeLuminance();
	return FMath::Lerp( *this, FLinearColor( Lum, Lum, Lum, 0 ), Desaturation );
}

/** Computes the perceptually weighted luminance value of a color. */
float FLinearColor::ComputeLuminance() const
{
	return R * 0.3f + G * 0.59f + B * 0.11f;
}

// Convert from RGBE to float as outlined in Gregory Ward's Real Pixels article, Graphics Gems II, page 80.
FLinearColor FColor::FromRGBE() const
{
	if( A == 0 )
		return FLinearColor::Black;
	else
	{
		const float Scale = ldexp( 1 / 255.0, A - 128 );
		return {R * Scale, G * Scale, B * Scale, 1.0f};
	}
}

/**
 * Converts byte hue-saturation-brightness to floating point red-green-blue.
 */
FLinearColor FLinearColor::FGetHSV( uint8 H, uint8 S, uint8 V )
{
	float Brightness = V * 1.4f / 255.f;
	Brightness *= 0.7f/(0.01f + FMath::Sqrt(Brightness));
	Brightness  = FMath::Clamp(Brightness,0.f,1.f);
	const FVector Hue = (H<86) ? FVector((85-H)/85.f,(H-0)/85.f,0) : (H<171) ? FVector(0,(170-H)/85.f,(H-85)/85.f) : FVector((H-170)/85.f,0,(255-H)/84.f);
	const FVector ColorVector = (Hue + S/255.f * (FVector(1,1,1) - Hue)) * Brightness;
	return {ColorVector.X,ColorVector.Y,ColorVector.Z,1};
}


/** Converts a linear space RGB color to an HSV color */
FLinearColor FLinearColor::LinearRGBToHSV() const
{
	const float RGBMin = FMath::Min3(R, G, B);
	const float RGBMax = FMath::Max3(R, G, B);
	const float RGBRange = RGBMax - RGBMin;

	const float Hue = (RGBMax == RGBMin ? 0.0f :
					   RGBMax == R    ? fmod((((G - B) / RGBRange) * 60.0f) + 360.0f, 360.0f) :
					   RGBMax == G    ?      (((B - R) / RGBRange) * 60.0f) + 120.0f :
					   RGBMax == B    ?      (((R - G) / RGBRange) * 60.0f) + 240.0f :
					   0.0f);
	
	const float Saturation = (RGBMax == 0.0f ? 0.0f : RGBRange / RGBMax);
	const float Value = RGBMax;

	// In the new color, R = H, G = S, B = V, A = A
	return {Hue, Saturation, Value, A};
}



/** Converts an HSV color to a linear space RGB color */
FLinearColor FLinearColor::HSVToLinearRGB() const
{
	// In this color, R = H, G = S, B = V
	const float Hue = R;
	const float Saturation = G;
	const float Value = B;

	const float HDiv60 = Hue / 60.0f;
	const float HDiv60_Floor = floorf(HDiv60);
	const float HDiv60_Fraction = HDiv60 - HDiv60_Floor;

	const float RGBValues[4] = {
		Value,
		Value * (1.0f - Saturation),
		Value * (1.0f - (HDiv60_Fraction * Saturation)),
		Value * (1.0f - ((1.0f - HDiv60_Fraction) * Saturation)),
	};
	const uint32 RGBSwizzle[6][3] = {
		{0, 3, 1},
		{2, 0, 1},
		{1, 0, 3},
		{1, 2, 0},
		{3, 1, 0},
		{0, 1, 2},
	};
	const uint32 SwizzleIndex = ((uint32)HDiv60_Floor) % 6;

	return {
		RGBValues[RGBSwizzle[SwizzleIndex][0]],
						RGBValues[RGBSwizzle[SwizzleIndex][1]],
						RGBValues[RGBSwizzle[SwizzleIndex][2]],
						A
	};
}


/**
 * Makes a random but quite nice color.
 */
FColor FColor::MakeRandomColor()
{
	const uint8 Hue = (uint8)( FMath::FRand()*255.f );
	return FColor( FLinearColor::FGetHSV(Hue, 0, 255) );
}

FColor FColor::MakeRedToGreenColorFromScalar(float Scalar)
{
	int32 R,G,B;
	R=G=B=0;

	float RedSclr = FMath::Clamp<float>((1.0f - Scalar)/0.5f,0.f,1.f);
	float GreenSclr = FMath::Clamp<float>((Scalar/0.5f),0.f,1.f);
	R = FMath::Trunc(255 * RedSclr);
	G = FMath::Trunc(255 * GreenSclr);
	return FColor(R,G,B);
}

void ComputeAndFixedColorAndIntensity(const FLinearColor& InLinearColor,FColor& OutColor,float& OutIntensity)
{
	float MaxComponent = FMath::Max(DELTA,FMath::Max(InLinearColor.R,FMath::Max(InLinearColor.G,InLinearColor.B)));
	OutColor = InLinearColor / MaxComponent;
	OutIntensity = MaxComponent;
}



/**
 * Pow table for fast FColor -> FLinearColor conversion.
 *
 * FMath::Pow( i / 255.f, 2.2f )
 */
float FLinearColor::PowOneOver255Table[256] = 
{
	0.0f,5.07705190066176E-06f,2.33280046660989E-05f,5.69217657121931E-05f,0.000107187362341244f,0.000175123977503027f,0.000261543754548491f,0.000367136269815943f,
	0.000492503787191433f,0.000638182842167022f,0.000804658499513058f,0.000992374304074325f,0.0012017395224384f,0.00143313458967186f,0.00168691531678928f,0.00196341621339647f,
	0.00226295316070643f,0.00258582559623417f,0.00293231832393836f,0.00330270303200364f,0.00369723957890013f,0.00411617709328275f,0.00455975492252602f,0.00502820345685554f,
	0.00552174485023966f,0.00604059365484981f,0.00658495738258168f,0.00715503700457303f,0.00775102739766061f,0.00837311774514858f,0.00902149189801213f,0.00969632870165823f,
	0.0103978022925553f,0.0111260823683832f,0.0118813344348137f,0.0126637200315821f,0.0134733969401426f,0.0143105193748841f,0.0151752381596252f,0.0160677008908869f,
	0.01698805208925f,0.0179364333399502f,0.0189129834237215f,0.0199178384387857f,0.0209511319147811f,0.0220129949193365f,0.0231035561579214f,0.0242229420675342f,
	0.0253712769047346f,0.0265486828284729f,0.027755279978126f,0.0289911865471078f,0.0302565188523887f,0.0315513914002264f,0.0328759169483838f,0.034230206565082f,
	0.0356143696849188f,0.0370285141619602f,0.0384727463201946f,0.0399471710015256f,0.0414518916114625f,0.0429870101626571f,0.0445526273164214f,0.0461488424223509f,
	0.0477757535561706f,0.049433457555908f,0.0511220500564934f,0.052841625522879f,0.0545922772817603f,0.0563740975519798f,0.0581871774736854f,0.0600316071363132f,
	0.0619074756054558f,0.0638148709486772f,0.0657538802603301f,0.0677245896854243f,0.0697270844425988f,0.0717614488462391f,0.0738277663277846f,0.0759261194562648f,
	0.0780565899581019f,0.080219258736215f,0.0824142058884592f,0.0846415107254295f,0.0869012517876603f,0.0891935068622478f,0.0915183529989195f,0.0938758665255778f,
	0.0962661230633397f,0.0986891975410945f,0.1011451642096f,0.103634096655137f,0.106156067812744f,0.108711149979039f,0.11129941482466f,0.113920933406333f,0.116575776178572f,
	0.119264013005047f,0.121985713169619f,0.124740945387051f,0.127529777813422f,0.130352278056244f,0.1332085131843f,0.136098549737202f,0.139022453734703f,0.141980290685736f,
	0.144972125597231f,0.147998022982685f,0.151058046870511f,0.154152260812165f,0.157280727890073f,0.160443510725344f,0.16364067148529f,0.166872271890766f,0.170138373223312f,
	0.173439036332135f,0.176774321640903f,0.18014428915439f,0.183548998464951f,0.186988508758844f,0.190462878822409f,0.193972167048093f,0.19751643144034f,0.201095729621346f,
	0.204710118836677f,0.208359655960767f,0.212044397502288f,0.215764399609395f,0.219519718074868f,0.223310408341127f,0.227136525505149f,0.230998124323267f,0.23489525921588f,
	0.238827984272048f,0.242796353254002f,0.24680041960155f,0.2508402364364f,0.254915856566385f,0.259027332489606f,0.263174716398492f,0.267358060183772f,0.271577415438375f,
	0.275832833461245f,0.280124365261085f,0.284452061560024f,0.288815972797219f,0.293216149132375f,0.297652640449211f,0.302125496358853f,0.306634766203158f,0.311180499057984f,
	0.315762743736397f,0.32038154879181f,0.325036962521076f,0.329729032967515f,0.334457807923889f,0.339223334935327f,0.344025661302187f,0.348864834082879f,0.353740900096629f,
	0.358653905926199f,0.363603897920553f,0.368590922197487f,0.373615024646202f,0.37867625092984f,0.383774646487975f,0.388910256539059f,0.394083126082829f,0.399293299902674f,
	0.404540822567962f,0.409825738436323f,0.415148091655907f,0.420507926167587f,0.425905285707146f,0.43134021380741f,0.436812753800359f,0.442322948819202f,0.44787084180041f,
	0.453456475485731f,0.45907989242416f,0.46474113497389f,0.470440245304218f,0.47617726539744f,0.481952237050698f,0.487765201877811f,0.493616201311074f,0.49950527660303f,
	0.505432468828216f,0.511397818884879f,0.517401367496673f,0.523443155214325f,0.529523222417277f,0.535641609315311f,0.541798355950137f,0.547993502196972f,0.554227087766085f,
	0.560499152204328f,0.566809734896638f,0.573158875067523f,0.579546611782525f,0.585972983949661f,0.592438030320847f,0.598941789493296f,0.605484299910907f,0.612065599865624f,
	0.61868572749878f,0.625344720802427f,0.632042617620641f,0.638779455650817f,0.645555272444934f,0.652370105410821f,0.659223991813387f,0.666116968775851f,0.673049073280942f,
	0.680020342172095f,0.687030812154625f,0.694080519796882f,0.701169501531402f,0.708297793656032f,0.715465432335048f,0.722672453600255f,0.729918893352071f,0.737204787360605f,
	0.744530171266715f,0.751895080583051f,0.759299550695091f,0.766743616862161f,0.774227314218442f,0.781750677773962f,0.789313742415586f,0.796916542907978f,0.804559113894567f,
	0.81224148989849f,0.819963705323528f,0.827725794455034f,0.835527791460841f,0.843369730392169f,0.851251645184515f,0.859173569658532f,0.867135537520905f,0.875137582365205f,
	0.883179737672745f,0.891262036813419f,0.899384513046529f,0.907547199521614f,0.915750129279253f,0.923993335251873f,0.932276850264543f,0.940600707035753f,0.948964938178195f,
	0.957369576199527f,0.96581465350313f,0.974300202388861f,0.982826255053791f,0.99139284359294f,1.0f
};