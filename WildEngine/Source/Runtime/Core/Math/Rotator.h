﻿// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

/** Stores Rotation information.*/
class FRotator
{
public:
	// Stored in degrees
	float Pitch; // Looking up and down (0=Straight Ahead, +Up, -Down).
	float Yaw;   // Rotating around (running in circles), 0=East, +North, -South.
	float Roll;  // Rotation about axis of screen, 0=Straight, +Clockwise, -CCW.
	
	/** Constructor.*/
	FORCEINLINE FRotator();

	/**
	 * Constructor.
	 *
	 * @param InPitch Pitch in degrees.
	 * @param InYaw Yaw in degrees.
	 * @param InRoll Roll in degrees.
	 */
	FORCEINLINE FRotator( float InPitch, float InYaw, float InRoll );
	
	/**
	 * Constructor.
	 *
	 * @param Quat Quaternion used to specify rotation.
	 */
	explicit  FRotator( const FQuat& Quat );

	// Binary arithmetic operators.

	/**
	 * Get the result of adding a rotator to this.
	 *
	 * @param R The other rotator.
	 *
	 * @return The result of adding a rotator to this.
	 */
	FRotator operator+( const FRotator &R ) const;

	/**
	 * Get the result of subtracting a rotator from this.
	 *
	 * @param R The other rotator.
	 *
	 * @return The result of subtracting a rotator from this.
	 */
	FRotator operator-( const FRotator &R ) const;

	/**
	 * Get the result of scaling this rotator.
	 *
	 * @param Scale The scaling factor.
	 *
	 * @return The result of scaling.
	 */
	FRotator operator*( float Scale ) const;

	/**
	 * Multiply this rotator by a scaling factor.
	 *
	 * @param Scale The scaling factor.
	 *
	 * @return Copy of the rotator after scaling.
	 */
	FRotator operator*= (float Scale);

	// Unary operators.

	/**
	 * Get a negated copy of the rotator.
	 *
	 * @return A negated copy of the rotator.
	 */
	FORCEINLINE FRotator operator-() const;

	// Binary comparison operators.

	/**
	 * Checks whether two rotators are identical.
	 *
	 * @param R The other rotator.
	 *
	 * @return true if two rotators are identical, otherwise false.
	 */
	bool operator==( const FRotator &R ) const;

	/**
	 * Checks whether two rotators are different.
	 *
	 * @param V The other rotator.
	 *
	 * @return true if two rotators are different, otherwise false.
	 */
	bool operator!=( const FRotator &V ) const;

	// Assignment operators.

	/**
	 * Adds another rotator to this.
	 *
	 * @param R The other rotator.
	 *
	 * @return Copy of rotator after addition.
	 */
	FRotator operator+=( const FRotator &R );

	/**
	 * Subtracts another rotator from this.
	 *
	 * @param R The other rotator.
	 *
	 * @return Copy of rotator after subtraction.
	 */
	FRotator operator-=( const FRotator &R );

	// Functions.

	/**
	 * Checks whether rotator is nearly zero, within specified tolerance.
	 *
	 * @param Tolerance Error Tolerance.
	 *
	 * @return true if rotator is nearly zero, within specified tolerance, otherwise false.
	 */
	bool IsNearlyZero(float Tolerance=KINDA_SMALL_NUMBER) const;

	/**
	 * Checks whether this has exactly zero rotation.
	 *
	 * @return true if this has exactly zero rotation, otherwise false.
	 */
	bool IsZero() const;

	/**
	 * Checks whether two rotators are equal, within specified tolerance.
	 *
	 * @param R The other rotator.
	 * @param Tolerance Error Tolerance.
	 *
	 * @return true if two rotators are equal, within specified tolerance, otherwise false.
	 */
	bool Equals(const FRotator &R, float Tolerance=KINDA_SMALL_NUMBER) const;

	/**
	 * Adds to each component of the rotator.
	 *
	 * @param DeltaPitch Change in pitch. (+/-)
	 * @param DeltaYaw Change in yaw. (+/-)
	 * @param DeltaRoll Change in roll. (+/-)
	 *
	 * @return Copy of rotator after addition.
	 */
	FRotator Add( float DeltaPitch, float DeltaYaw, float DeltaRoll );

	/**
	 * Get the rotation, snapped to specified degree segments.
	 *
	 * @param RotGrid A Rotator specifying how to snap each component.
	 *
	 * @return Snapped version of rotation.
	 */
	FRotator GridSnap( const FRotator &RotGrid ) const;

	/**
	 * Convert a rotation into a vector facing in its direction.
	 *
	 * @return Rotation as a direction vector.
	 */
	 FVector Vector() const;

	/**
	 * Get Rotation as a quaternion.
	 *
	 * @return Rotation as a quaternion.
	 */
	 FQuat Quaternion() const;

	/**
	 * Convert a Rotator into floating-point Euler angles (in degrees). Rotator now stored in degrees.
	 *
	 * @return Rotation as a Euler angle vector.
	 */
	 FVector Euler() const;

	/**
	 * Convert a vector of floating-point Euler angles (in degrees) into a Rotator. Rotator now stored in degrees
	 *
	 * @param Euler Euler angle vector.
	 *
	 * @return A rotator from a euler angle.
	 */
	static  FRotator MakeFromEuler(const FVector& Euler);


	/** Rotate a vector rotated by this rotator */
	 FVector RotateVector(const FVector& V) const;

	/* Returns the vector rotated by the inverse of this rotator */
	 FVector UnrotateVector(const FVector& V) const;


	/**
	 * Gets the rotation values so they fall within the range [0,360]
	 *
	 * @return Clamped version of rotator.
	 */
	FRotator Clamp() const;

	/**
	 * Clamps an angle to the range of [0, 360].
	 *
	 * @param Angle The angle to clamp.
	 *
	 * @return The clamped angle.
	 */
	static float ClampAxis(float Angle);

	/**
	 * Clamps an angle to the range of [-180, 180].
	 *
	 * @param Angle The Angle to clamp.
	 *
	 * @return The clamped angle.
	 */
	static float NormalizeAxis(float Angle);

	/**
	 * Compresses a floating point angle into a byte.
	 *
	 * @param Angle The angle to compress.
	 *
	 * @return The angle as a byte.
	 */
	static uint8 CompressAxisToByte(float Angle);

	/**
	 * Decompress a word into a floating point angle.
	 *
	 * @param Angle The word angle.
	 *
	 * @return The decompressed angle.
	 */
	static float DecompressAxisFromByte(uint16 Angle);

	/**
	 * Compress a floating point angle into a word.
	 *
	 * @param Angle The angle to compress.
	 *
	 * @return The decompressed angle.
	 */
	static uint16 CompressAxisToShort(float Angle);


	/**
	 * Decompress a short into a floating point angle.
	 *
	 * @param Angle The word angle.
	 *
	 * @return The decompressed angle.
	 */
	static float DecompressAxisFromShort(uint16 Angle);

	/** 
	 * Create a copy of this rotator and normalize, removes all winding and creates the "shortest route" rotation. 
	 *
	 * @return Normalized copy of this rotator
	 */
	FRotator GetNormalized() const;

	/** 
	 * Create a copy of this rotator and denormalize, clamping each axis to 0 - 360. 
	 *
	 * @return Denormalized copy of this rotator
	 */
	FRotator GetDenormalized() const;

	/** In-place normalize, removes all winding and creates the "shortest route" rotation. */
	void Normalize();

	/** 
	 * Decompose this Rotator into a Winding part (multiples of 360) and a Remainder part. 
	 * Remainder will always be in [-180, 180] range.
	 *
	 * @param Winding[Out] the Winding part of this Rotator
	 * @param Remainder[Out] the Remainder
	 */
	 void GetWindingAndRemainder(FRotator& Winding, FRotator& Remainder) const;

	/**
	 * Get a textual representation of the vector.
	 *
	 * @return Text describing the vector.
	 */
	// FString ToString() const;

	/** Get a short textural representation of this vector, for compact readable logging. */
	// FString ToCompactString() const;

	/**
	 * Initialize this Rotator based on an FString. The String is expected to contain P=, Y=, R=.
	 * The FRotator will be bogus when InitFromString returns false.
	 *
	 * @param	InSourceString	FString containing the rotator values.
	 *
	 * @return true if the P,Y,R values were read successfully; false otherwise.
	 */
	// bool InitFromString( const FString & InSourceString );

	static  const FRotator ZeroRotator;

	/**
	 * Utility to check if there are any NaNs in this Rotator.
	 *
	 * @return true if there are any NaNs in this Rotator, otherwise false.
	 */
	bool ContainsNaN() const;
};

/**
 * Scale a rotator and return
 *
 * @param Scale scale to apply to R
 * @param R rotator to be scaled
 *
 * @return Scaled rotator.
 */
FORCEINLINE FRotator operator*( float Scale, const FRotator &R )
{
	return R.operator*( Scale );
}

FORCEINLINE FRotator::FRotator() = default;

FORCEINLINE FRotator::FRotator( float InPitch, float InYaw, float InRoll )
	:	Pitch(InPitch), Yaw(InYaw), Roll(InRoll) 
{}


FORCEINLINE FRotator FRotator::operator+( const FRotator &R ) const
{
	return {Pitch+R.Pitch, Yaw+R.Yaw, Roll+R.Roll};
}

FORCEINLINE FRotator FRotator::operator-( const FRotator &R ) const
{
	return {Pitch-R.Pitch, Yaw-R.Yaw, Roll-R.Roll};
}

FORCEINLINE FRotator FRotator::operator*( float Scale ) const
{
	return {Pitch*Scale, Yaw*Scale, Roll*Scale};
}

FORCEINLINE FRotator FRotator::operator*= (float Scale)
{
	Pitch = Pitch*Scale; Yaw = Yaw*Scale; Roll = Roll*Scale;
	return *this;
}

FORCEINLINE FRotator FRotator::operator-() const
{
	return {-Pitch, -Yaw, -Roll};
}

FORCEINLINE bool FRotator::operator==( const FRotator &R ) const
{
	return Pitch==R.Pitch && Yaw==R.Yaw && Roll==R.Roll;
}

FORCEINLINE bool FRotator::operator!=( const FRotator &V ) const
{
	return Pitch!=V.Pitch || Yaw!=V.Yaw || Roll!=V.Roll;
}

FORCEINLINE FRotator FRotator::operator+=( const FRotator &R )
{
	Pitch += R.Pitch; Yaw += R.Yaw; Roll += R.Roll;
	return *this;
}

FORCEINLINE FRotator FRotator::operator-=( const FRotator &R )
{
	Pitch -= R.Pitch; Yaw -= R.Yaw; Roll -= R.Roll;
	return *this;
}

FORCEINLINE bool FRotator::IsNearlyZero(float Tolerance) const
{
	return
		FMath::Abs(NormalizeAxis(Pitch))<Tolerance
		&&	FMath::Abs(NormalizeAxis(Yaw))<Tolerance
		&&	FMath::Abs(NormalizeAxis(Roll))<Tolerance;
}

FORCEINLINE bool FRotator::IsZero() const
{
	return (ClampAxis(Pitch)==0.f) && (ClampAxis(Yaw)==0.f) && (ClampAxis(Roll)==0.f);
}

FORCEINLINE bool FRotator::Equals(const FRotator &R, float Tolerance) const
{
	return (FMath::Abs(NormalizeAxis(Pitch - R.Pitch)) < Tolerance) 
		&& (FMath::Abs(NormalizeAxis(Yaw - R.Yaw)) < Tolerance) 
		&& (FMath::Abs(NormalizeAxis(Roll - R.Roll)) < Tolerance);
}

FORCEINLINE FRotator FRotator::Add( float DeltaPitch, float DeltaYaw, float DeltaRoll )
{
	Yaw   += DeltaYaw;
	Pitch += DeltaPitch;
	Roll  += DeltaRoll;
	return *this;
}

FORCEINLINE FRotator FRotator::GridSnap( const FRotator &RotGrid ) const
{
	return {
		FMath::GridSnap(Pitch,RotGrid.Pitch),
		FMath::GridSnap(Yaw,  RotGrid.Yaw),
		FMath::GridSnap(Roll, RotGrid.Roll)
	};
}

FORCEINLINE FRotator FRotator::Clamp() const
{
	return {ClampAxis(Pitch), ClampAxis(Yaw), ClampAxis(Roll)};
}

FORCEINLINE float FRotator::ClampAxis(float Angle)
{
	// returns Angle in the range (-360,360)
	Angle = FMath::Fmod(Angle, 360.f);

	if (Angle < 0.f)
	{
		// shift to [0,360) range
		Angle += 360.f;
	}

	return Angle;
}

FORCEINLINE float FRotator::NormalizeAxis(float Angle)
{
	// returns Angle in the range [0,360)
	Angle = ClampAxis(Angle);

	if (Angle > 180.f)
	{
		// shift to (-180,180]
		Angle -= 360.f;
	}

	return Angle;
}

FORCEINLINE uint8 FRotator::CompressAxisToByte(float Angle)
{
	// map [0->360) to [0->256) and mask off any winding
	return FMath::Round(Angle * 256.f / 360.f) & 0xFF;
}

FORCEINLINE float FRotator::DecompressAxisFromByte(uint16 Angle)
{
	// map [0->256) to [0->360)
	return (Angle * 360.f / 256.f);
}

FORCEINLINE uint16 FRotator::CompressAxisToShort(float Angle)
{
	// map [0->360) to [0->65536) and mask off any winding
	return FMath::Round(Angle * 65536.f / 360.f) & 0xFFFF;
}


FORCEINLINE float FRotator::DecompressAxisFromShort(uint16 Angle)
{
	// map [0->65536) to [0->360)
	return (Angle * 360.f / 65536.f);
}

FORCEINLINE FRotator FRotator::GetNormalized() const
{
	FRotator Rot = *this;
	Rot.Normalize();
	return Rot;
}

FORCEINLINE FRotator FRotator::GetDenormalized() const
{
	FRotator Rot = *this;
	Rot.Pitch	= ClampAxis(Rot.Pitch);
	Rot.Yaw		= ClampAxis(Rot.Yaw);
	Rot.Roll	= ClampAxis(Rot.Roll);
	return Rot;
}

FORCEINLINE void FRotator::Normalize()
{
	Yaw = NormalizeAxis(Yaw);
	Pitch = NormalizeAxis(Pitch);
	Roll = NormalizeAxis(Roll);
}

FORCEINLINE bool FRotator::ContainsNaN() const
{
	return (FMath::IsNaN(Pitch) || !FMath::IsFinite(Pitch) 
			|| FMath::IsNaN(Yaw) || !FMath::IsFinite(Yaw) 
			|| FMath::IsNaN(Roll) || !FMath::IsFinite(Roll));
}