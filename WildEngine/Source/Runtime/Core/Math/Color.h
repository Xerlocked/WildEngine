// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

/*=============================================================================
	Color.h: Unreal color definitions.
=============================================================================*/

#pragma once

/**
 * A linear, 32-bit/component floating point RGBA color.
 */
struct FLinearColor
{
	float	R,
			G,
			B,
			A;

	/** Static lookup table used for FColor -> FLinearColor conversion. */
	static float PowOneOver255Table[256];

	FORCEINLINE FLinearColor() = default;
	FORCEINLINE FLinearColor(float InR,float InG,float InB,float InA = 1.0f): R(InR), G(InG), B(InB), A(InA) {}
	FLinearColor(const class FColor& C);
	FLinearColor(const class FVector& Vector);

	// Conversions.
	 FColor ToRGBE() const;

	// Operators.

	FORCEINLINE float& Component(int32 Index)
	{
		return (&R)[Index];
	}

	FORCEINLINE const float& Component(int32 Index) const
	{
		return (&R)[Index];
	}

	FORCEINLINE FLinearColor operator+(const FLinearColor& ColorB) const
	{
		return {
			this->R + ColorB.R,
			this->G + ColorB.G,
			this->B + ColorB.B,
			this->A + ColorB.A
		};
	}
	FORCEINLINE FLinearColor& operator+=(const FLinearColor& ColorB)
	{
		R += ColorB.R;
		G += ColorB.G;
		B += ColorB.B;
		A += ColorB.A;
		return *this;
	}

	FORCEINLINE FLinearColor operator-(const FLinearColor& ColorB) const
	{
		return {
			this->R - ColorB.R,
			this->G - ColorB.G,
			this->B - ColorB.B,
			this->A - ColorB.A
		};
	}
	FORCEINLINE FLinearColor& operator-=(const FLinearColor& ColorB)
	{
		R -= ColorB.R;
		G -= ColorB.G;
		B -= ColorB.B;
		A -= ColorB.A;
		return *this;
	}

	FORCEINLINE FLinearColor operator*(const FLinearColor& ColorB) const
	{
		return {
			this->R * ColorB.R,
			this->G * ColorB.G,
			this->B * ColorB.B,
			this->A * ColorB.A
		};
	}
	FORCEINLINE FLinearColor& operator*=(const FLinearColor& ColorB)
	{
		R *= ColorB.R;
		G *= ColorB.G;
		B *= ColorB.B;
		A *= ColorB.A;
		return *this;
	}

	FORCEINLINE FLinearColor operator*(const float Scalar) const
	{
		return {
			this->R * Scalar,
			this->G * Scalar,
			this->B * Scalar,
			this->A * Scalar
		};
	}

	FORCEINLINE FLinearColor& operator*=(const float Scalar)
	{
		R *= Scalar;
		G *= Scalar;
		B *= Scalar;
		A *= Scalar;
		return *this;
	}

	FORCEINLINE FLinearColor operator/(const FLinearColor& ColorB) const
	{
		return {
			this->R / ColorB.R,
			this->G / ColorB.G,
			this->B / ColorB.B,
			this->A / ColorB.A
		};
	}
	FORCEINLINE FLinearColor& operator/=(const FLinearColor& ColorB)
	{
		R /= ColorB.R;
		G /= ColorB.G;
		B /= ColorB.B;
		A /= ColorB.A;
		return *this;
	}

	FORCEINLINE FLinearColor operator/(float Scalar) const
	{
		const float	InvScalar = 1.0f / Scalar;
		return {
			this->R * InvScalar,
			this->G * InvScalar,
			this->B * InvScalar,
			this->A * InvScalar
		};
	}
	FORCEINLINE FLinearColor& operator/=(float Scalar)
	{
		const float	InvScalar = 1.0f / Scalar;
		R *= InvScalar;
		G *= InvScalar;
		B *= InvScalar;
		A *= InvScalar;
		return *this;
	}

	/** Comparison operators */
	FORCEINLINE bool operator==(const FLinearColor& ColorB) const
	{
		return this->R == ColorB.R && this->G == ColorB.G && this->B == ColorB.B && this->A == ColorB.A;
	}
	FORCEINLINE bool operator!=(const FLinearColor& Other) const
	{
		return this->R != Other.R || this->G != Other.G || this->B != Other.B || this->A != Other.A;
	}

	// Error-tolerant comparison.
	FORCEINLINE bool Equals(const FLinearColor& ColorB, float Tolerance=KINDA_SMALL_NUMBER) const
	{
		return FMath::Abs(this->R - ColorB.R) < Tolerance && FMath::Abs(this->G - ColorB.G) < Tolerance && FMath::Abs(this->B - ColorB.B) < Tolerance && FMath::Abs(this->A - ColorB.A) < Tolerance;
	}

	 FLinearColor CopyWithNewOpacity(float NewOpacity) const
	 {
		FLinearColor NewCopy = *this;
		NewCopy.A = NewOpacity;
		return NewCopy;
	}

	/**
	 * Converts byte hue-saturation-brightness to floating point red-green-blue.
	 */
	static  FLinearColor FGetHSV(uint8 H,uint8 S,uint8 V);

	/**
	 * Euclidean distance between two points.
	 */
	static inline float Dist( const FLinearColor &V1, const FLinearColor &V2 )
	{
		return FMath::Sqrt( FMath::Square(V2.R-V1.R) + FMath::Square(V2.G-V1.G) + FMath::Square(V2.B-V1.B) + FMath::Square(V2.A-V1.A) );
	}

	/**
	 * Generates a list of sample points on a Bezier curve defined by 2 points.
	 *
	 * @param	ControlPoints	Array of 4 Linear Colors (vert1, controlpoint1, controlpoint2, vert2).
	 * @param	NumPoints		Number of samples.
	 * @param	OutPoints		Receives the output samples.
	 * @return					Path length.
	 */
	static  float EvaluateBezier(const FLinearColor* ControlPoints, int32 NumPoints, TArray<FLinearColor>& OutPoints);

	/** Converts a linear space RGB color to an HSV color */
	 FLinearColor LinearRGBToHSV() const;

	/** Converts an HSV color to a linear space RGB color */
	 FLinearColor HSVToLinearRGB() const;

	/** Quantizes the linear color and returns the result as a FColor.  This bypasses the SRGB conversion. */
	 FColor Quantize() const;

	/** Quantizes the linear color and returns the result as a FColor with optional sRGB conversion and quality as goal. */
	 FColor ToFColor(const bool bSRGB) const;

	/**
	 * Returns a desaturated color, with 0 meaning no desaturation and 1 == full desaturation
	 *
	 * @param	Desaturation	Desaturation factor in range [0..1]
	 * @return	Desaturated color
	 */
	 FLinearColor Desaturate( float Desaturation ) const;

	/** Computes the perceptually weighted luminance value of a color. */
	 float ComputeLuminance() const;

	/**
	 * Returns the maximum value in this color structure
	 *
	 * @return	The maximum color channel value
	 */
	FORCEINLINE float GetMax() const
	{
		return FMath::Max( FMath::Max( FMath::Max( R, G ), B ), A );
	}

	/** useful to detect if a light contribution needs to be rendered */
	bool IsAlmostBlack() const
	{
		return FMath::Square(R) < DELTA && FMath::Square(G) < DELTA && FMath::Square(B) < DELTA;
	}

	/**
	 * Returns the minimum value in this color structure
	 *
	 * @return	The minimum color channel value
	 */
	FORCEINLINE float GetMin() const
	{
		return FMath::Min( FMath::Min( FMath::Min( R, G ), B ), A );
	}

	FORCEINLINE float GetLuminance() const 
	{ 
		return R * 0.3f + G * 0.59f + B * 0.11f; 
	}

	// Common colors.	
	static  const FLinearColor White;
	static  const FLinearColor Gray;
	static  const FLinearColor Black;
	static  const FLinearColor Transparent;
	static  const FLinearColor Red;
	static  const FLinearColor Green;
	static  const FLinearColor Blue;
	static  const FLinearColor Yellow;
};

FORCEINLINE FLinearColor operator*(float Scalar,const FLinearColor& Color)
{
	return Color.operator*( Scalar );
}

//
//	FColor
//

class FColor
{
public:
	// Variables.
#if PLATFORM_LITTLE_ENDIAN
    #if _MSC_VER
		// Win32 x86
	    union { struct{ uint8 B,G,R,A; }; uint32 AlignmentDummy; };
    #else
		// Linux x86, etc
	    uint8 B GCC_ALIGN(4);
	    uint8 G,R,A;
    #endif
#else // PLATFORM_LITTLE_ENDIAN
	union { struct{ uint8 A,R,G,B; }; uint32 AlignmentDummy; };
#endif

	uint32& DWColor(void) {return *((uint32*)this);}
	const uint32& DWColor(void) const {return *((uint32*)this);}

	// Constructors.
	FORCEINLINE FColor() {}
	FORCEINLINE FColor( uint8 InR, uint8 InG, uint8 InB, uint8 InA = 255 )
	{
		// put these into the body for proper ordering with INTEL vs non-INTEL_BYTE_ORDER
		R = InR;
		G = InG;
		B = InB;
		A = InA;

	}
	
	// fast, for more accuracy use FLinearColor::ToFColor()
	// TODO: doesn't handle negative colors well, implicit constructor can cause
	// accidental conversion (better use .ToFColor(true))
	FColor(const FLinearColor& C)
		// put these into the body for proper ordering with INTEL vs non-INTEL_BYTE_ORDER
	{
		R = FMath::Clamp(FMath::Trunc(FMath::Pow(C.R,1.0f / 2.2f) * 255.0f),0,255);
		G = FMath::Clamp(FMath::Trunc(FMath::Pow(C.G,1.0f / 2.2f) * 255.0f),0,255);
		B = FMath::Clamp(FMath::Trunc(FMath::Pow(C.B,1.0f / 2.2f) * 255.0f),0,255);
		A = FMath::Clamp(FMath::Trunc(C.A * 255.0f),0,255);
	}

	FORCEINLINE explicit FColor( uint32 InColor )
	{ 
		DWColor() = InColor; 
	}

	// Operators.
	FORCEINLINE bool operator==( const FColor &C ) const
	{
		return DWColor() == C.DWColor();
	}

	FORCEINLINE bool operator!=( const FColor& C ) const
	{
		return DWColor() != C.DWColor();
	}

	FORCEINLINE void operator+=(const FColor& C)
	{
		R = (uint8) FMath::Min((int32) R + (int32) C.R,255);
		G = (uint8) FMath::Min((int32) G + (int32) C.G,255);
		B = (uint8) FMath::Min((int32) B + (int32) C.B,255);
		A = (uint8) FMath::Min((int32) A + (int32) C.A,255);
	}

	 FLinearColor FromRGBE() const;
	
	/**
	 * Makes a random but quite nice color.
	 */
	static  FColor MakeRandomColor();

	/**
	 * Makes a color red->green with the passed in scalar (e.g. 0 is red, 1 is green)
	 */
	static  FColor MakeRedToGreenColorFromScalar(float Scalar);

	/**
	 * Reinterprets the color as a linear color.
	 *
	 * @return The linear color representation.
	 */
	FORCEINLINE FLinearColor ReinterpretAsLinear() const
	{
		return {R / 255.f, G / 255.f, B / 255.f, A / 255.f};
	}

	/** Some pre-inited colors, useful for debug code */
	static  const FColor White;
	static  const FColor Black;
	static  const FColor Red;
	static  const FColor Green;
	static  const FColor Blue;
	static  const FColor Yellow;
	static  const FColor Cyan;
	static  const FColor Magenta;
};

FORCEINLINE uint32 GetTypeHash( const FColor& Color )
{
	return Color.DWColor();
}

/** Computes a brightness and a fixed point color from a floating point color. */
extern  void ComputeAndFixedColorAndIntensity(const FLinearColor& InLinearColor,FColor& OutColor,float& OutIntensity);

/**
 * Helper struct for a 16 bit 565 color of a DXT1/3/5 block.
 */
struct FDXTColor565
{
	/** Blue component, 5 bit. */
	uint16 B:5;
	/** Green component, 6 bit. */
	uint16 G:6;
	/** Red component, 5 bit */
	uint16 R:5;
};

/**
 * Helper struct for a 16 bit 565 color of a DXT1/3/5 block.
 */
struct FDXTColor16
{
	union 
	{
		/** 565 Color */
		FDXTColor565 Color565;
		/** 16 bit entity representation for easy access. */
		uint16 Value;
	};
};

/**
 * Structure encompassing single DXT1 block.
 */
struct FDXT1
{
	/** Color 0/1 */
	union
	{
		FDXTColor16 Color[2];
		uint32 Colors;
	};
	/** Indices controlling how to blend colors. */
	uint32 Indices;
};

/**
 * Structure encompassing single DXT5 block
 */
struct FDXT5
{
	/** Alpha component of DXT5 */
	uint8	Alpha[8];
	/** DXT1 color component. */
	FDXT1	DXT1;
};