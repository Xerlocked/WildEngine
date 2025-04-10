﻿#pragma once


/*-----------------------------------------------------------------------------
	Definitions.
-----------------------------------------------------------------------------*/

// Forward declarations.
class  FVector;
class  FVector4;
class  FPlane;
class  FBox;
class  FRotator;
class  FMatrix;
class  FQuat;
class  FTransform;
class  FSphere;
struct FVector2D;
struct FLinearColor;
struct VectorRegister;

/*-----------------------------------------------------------------------------
    Floating point constants.
-----------------------------------------------------------------------------*/

#undef  PI
#define PI 					(3.1415926535897932f)
#define SMALL_NUMBER		(1.e-8f)
#define KINDA_SMALL_NUMBER	(1.e-4f)
#define BIG_NUMBER			(3.4e+38f)
#define EULERS_NUMBER       (2.71828182845904523536f)

// Copied from float.h
#define MAX_FLT 3.402823466e+38F

// Copied from int.h
#define MAX_int16 32767

// Aux constants.
#define INV_PI			(0.31830988618f)
#define HALF_PI			(1.57079632679f)

// Magic numbers for numerical precision.
#define DELTA			(0.00001f)

/**
 * Lengths of normalized vectors (These are half their maximum values
 * to assure that dot products with normalized vectors don't overflow).
 */
#define FLOAT_NORMAL_THRESH				(0.0001f)

//
// Magic numbers for numerical precision.
//
#define THRESH_POINT_ON_PLANE			(0.10f)		/* Thickness of plane for front/back/inside test */
#define THRESH_POINT_ON_SIDE			(0.20f)		/* Thickness of polygon side's side-plane for point-inside/outside/on side test */
#define THRESH_POINTS_ARE_SAME			(0.00002f)	/* Two points are same if within this distance */
#define THRESH_POINTS_ARE_NEAR			(0.015f)	/* Two points are near if within this distance and can be combined if imprecise math is ok */
#define THRESH_NORMALS_ARE_SAME			(0.00002f)	/* Two normal points are same if within this distance */
                                                    /* Making this too large results in incorrect CSG classification and disaster */
#define THRESH_VECTORS_ARE_NEAR			(0.0004f)	/* Two vectors are near if within this distance and can be combined if imprecise math is ok */
                                                    /* Making this too large results in lighting problems due to inaccurate texture coordinates */
#define THRESH_SPLIT_POLY_WITH_PLANE	(0.25f)		/* A plane splits a polygon in half */
#define THRESH_SPLIT_POLY_PRECISELY		(0.01f)		/* A plane exactly splits a polygon */
#define THRESH_ZERO_NORM_SQUARED		(0.0001f)	/* Size of a unit normal that is considered "zero", squared */
#define THRESH_VECTORS_ARE_PARALLEL		(0.02f)		/* Vectors are parallel if dot product varies less than this */

#define ZERO_ANIMWEIGHT_THRESH			(0.0001f)

/*-----------------------------------------------------------------------------
	Global functions.
-----------------------------------------------------------------------------*/

/**
 * Structure for all math helper functions, inherits from platform math to pick up platform-specific implementations
 * Check GenericPlatformMath.h for additional math functions
 */
struct FMath : public FGenericPlatformMath
{
	// Random Number Functions

	/** Helper function for rand implementations. Returns a random number in [0..A) */
	static FORCEINLINE int32 RandHelper(int32 A)
	{
		// RAND_MAX+1 give interval [0..A) with even distribution.
		return A>0 ? Trunc(Rand()/(float)((uint32)RAND_MAX+1) * A) : 0;
	}

	/** Helper function for rand implementations. Returns a random number >= Min and <= Max */
	static FORCEINLINE int32 RandRange(int32 Min, int32 Max)
	{
		const int32 Range = (Max - Min) + 1;
		return Min + RandHelper(Range);
	}

	/** Util to generate a random number in a range. */
	static FORCEINLINE float FRandRange(float InMin, float InMax)
	{
		return InMin + (InMax - InMin) * FRand();
	}

	/** Return a uniformly distributed random unit length vector = point on the unit sphere surface. */
	static FVector VRand();
	
	/*
	 * Returns a random unit vector, uniformly distributed, within the specified cone
	 * ConeHalfAngleRad is the half-angle of cone, in radians.  Returns a normalized vector. 
	 */
	static  FVector VRandCone(FVector const& Dir, float ConeHalfAngleRad);

	/** 
	 * This is a version of VRandCone that handles "squished" cones, i.e. with different angle limits in the Y and Z axes.
	 * Assumes world Y and Z, although this could be extended to handle arbitrary rotations.
	 */
	static  FVector VRandCone(FVector const& Dir, float HorizontalConeHalfAngleRad, float VerticalConeHalfAngleRad);


	// Predicates

	/** Checks if value is within a range, exclusive on MaxValue) */
	template< class U > 
	static FORCEINLINE bool IsWithin(const U& TestValue, const U& MinValue, const U& MaxValue)
	{
		return ((TestValue>=MinValue) && (TestValue < MaxValue));
	}

	/** Checks if value is within a range, inclusive on MaxValue) */
	template< class U > 
	static FORCEINLINE bool IsWithinInclusive(const U& TestValue, const U& MinValue, const U& MaxValue)
	{
		return ((TestValue>=MinValue) && (TestValue <= MaxValue));
	}
	
	/**
	 *	Checks if two floating point numbers are nearly equal.
	 *	@param A				First number to compare
	 *	@param B				Second number to compare
	 *	@param ErrorTolerance	Maximum allowed difference for considering them as 'nearly equal'
	 *	@return					true if A and B are nearly equal
	 */
	static FORCEINLINE bool IsNearlyEqual(float A, float B, float ErrorTolerance = SMALL_NUMBER)
	{
		return Abs<float>( A - B ) < ErrorTolerance;
	}

	/**
	 *	Checks if two floating point numbers are nearly equal.
	 *	@param A				First number to compare
	 *	@param B				Second number to compare
	 *	@param ErrorTolerance	Maximum allowed difference for considering them as 'nearly equal'
	 *	@return					true if A and B are nearly equal
	 */
	static FORCEINLINE bool IsNearlyEqual(double A, double B, double ErrorTolerance = SMALL_NUMBER)
	{
		return Abs<double>( A - B ) < ErrorTolerance;
	}

	/**
	 *	Checks if a floating point number is nearly zero.
	 *	@param Value			Number to compare
	 *	@param ErrorTolerance	Maximum allowed difference for considering Value as 'nearly zero'
	 *	@return					true if Value is nearly zero
	 */
	static FORCEINLINE bool IsNearlyZero(float Value, float ErrorTolerance = SMALL_NUMBER)
	{
		return Abs<float>( Value ) < ErrorTolerance;
	}

	/**
	 *	Checks if a floating point number is nearly zero.
	 *	@param Value			Number to compare
	 *	@param ErrorTolerance	Maximum allowed difference for considering Value as 'nearly zero'
	 *	@return					true if Value is nearly zero
	 */
	static FORCEINLINE bool IsNearlyZero(double Value, double ErrorTolerance = SMALL_NUMBER)
	{
		return Abs<double>( Value ) < ErrorTolerance;
	}

	/**
	 *	Checks whether a number is a power of two.
	 *	@param Value	Number to check
	 *	@return			true if Value is a power of two
	 */
	static FORCEINLINE bool IsPowerOfTwo( uint32 Value )
	{
		return ((Value & (Value - 1)) == 0);
	}


	// Math Operations

	/** Returns highest of 3 values */
	template< class T > 
	static FORCEINLINE T Max3( const T A, const T B, const T C )
	{
		return Max ( Max( A, B ), C );
	}

	/** Returns lowest of 3 values */
	template< class T > 
	static FORCEINLINE T Min3( const T A, const T B, const T C )
	{
		return Min ( Min( A, B ), C );
	}

	/** Multiples value by itself */
	template< class T > 
	static FORCEINLINE T Square( const T A )
	{
		return A*A;
	}

	/** Clamps X to be between Min and Max, inclusive */
	template< class T > 
	static FORCEINLINE T Clamp( const T X, const T Min, const T Max )
	{
		return X<Min ? Min : X<Max ? X : Max;
	}

	/** Snaps a value to the nearest grid multiple */
	static FORCEINLINE float GridSnap( float Location, float Grid )
	{
		if( Grid==0.f )	return Location;
		else			
		{
			return Floor((Location + 0.5*Grid)/Grid)*Grid;
		}
	}

	/** Snaps a value to the nearest grid multiple */
	static FORCEINLINE double GridSnap( double Location, double Grid )
	{
		if( Grid==0.0 )	return Location;
		else			
		{
			return FloorDouble((Location + 0.5*Grid)/Grid)*Grid;
		}
	}

	/** Divides two integers and rounds up */
	template <class T>
	static FORCEINLINE T DivideAndRoundUp(T Dividend,T Divisor)
	{
		return (Dividend + Divisor - 1) / Divisor;
	}

	/**
	 * Computes the base 2 logarithm of the specified value
	 *
	 * @param Value the value to perform the log on
	 *
	 * @return the base 2 log of the value
	 */
	static FORCEINLINE float Log2(float Value)
	{
		// Cached value for fast conversions
		static const float LogToLog2 = 1.f / Loge(2.f);
		// Do the platform specific log and convert using the cached value
		return Loge(Value) * LogToLog2;
	}


	// Conversion Functions

	/** 
	 * Converts radians to degrees.
	 * @param	RadVal			Value in radians.
	 * @return					Value in degrees.
	 */
	template<class T>
	static FORCEINLINE T RadiansToDegrees(T const& RadVal)
	{
		return RadVal * (180.f / PI);
	}

	/** 
	 * Converts degrees to radians.
	 * @param	DegVal			Value in degrees.
	 * @return					Value in radians.
	 */
	template<class T>
	static FORCEINLINE T DegreesToRadians(T const& DegVal)
	{
		return DegVal * (PI / 180.f);
	}

	/** 
	 * Clamps an arbitrary angle to be between the given angles.  Will clamp to nearest boundary.
	 * 
	 * @param MinAngleDegrees	"from" angle that defines the beginning of the range of valid angles (sweeping clockwise)
	 * @param MaxAngleDegrees	"to" angle that defines the end of the range of valid angles
	 * @return Returns clamped angle in the range -180..180.
	 */
	static float  ClampAngle(float AngleDegrees, float MinAngleDegrees, float MaxAngleDegrees);

	/** Find the smallest angle between two headings (in radians) */
	static float FindDeltaAngle(float A1, float A2)
	{
		// Find the difference
		float Delta = A2 - A1;

		// If change is larger than PI
		if(Delta > PI)
		{
			// Flip to negative equivalent
			Delta = Delta - (PI * 2.0f);
		}
		else if(Delta < -PI)
		{
			// Otherwise, if change is smaller than -PI
			// Flip to positive equivalent
			Delta = Delta + (PI * 2.0f);
		}

		// Return delta in [-PI,PI] range
		return Delta;
	}

	/** Given a heading which may be outside the +/- PI range, 'unwind' it back into that range. */
	static float UnwindRadians(float A)
	{
		while(A > PI)
		{
			A -= ((float)PI * 2.0f);
		}

		while(A < -PI)
		{
			A += ((float)PI * 2.0f);
		}

		return A;
	}

	/** Utility to ensure angle is between +/- 180 degrees by unwinding. */
	static float UnwindDegrees(float A)
	{
		while(A > 180.f)
		{
			A -= 360.f;
		}

		while(A < -180.f)
		{
			A += 360.f;
		}

		return A;
	}

	/** Returns a new rotation component value
	 *
	 * @param InCurrent is the current rotation value
	 * @param InDesired is the desired rotation value
	 * @param InDeltaRate is the rotation amount to apply
	 *
	 * @return a new rotation component value
	 */
	static  float FixedTurn(float InCurrent, float InDesired, float InDeltaRate);

	/** Converts given Cartesian coordinate pair to Polar coordinate system. */
	static FORCEINLINE void CartesianToPolar(float X, float Y, float& OutRad, float& OutAng)
	{
		OutRad = Sqrt(Square(X) + Square(Y));
		OutAng = Atan2(Y, X);
	}
	/** Converts given Polar coordinate pair to Cartesian coordinate system. */
	static FORCEINLINE void PolarToCartesian(float Rad, float Ang, float& OutX, float& OutY)
	{
		OutX = Rad * Cos(Ang);
		OutY = Rad * Sin(Ang);
	}

	/**
	 * Calculates the dotted distance of vector 'Direction' to coordinate system O(AxisX,AxisY,AxisZ).
	 *
	 * Orientation: (consider 'O' the first person view of the player, and 'Direction' a vector pointing to an enemy)
	 * - positive azimuth means enemy is on the right of crosshair. (negative means left).
	 * - positive elevation means enemy is on top of crosshair, negative means below.
	 *
	 * @Note: 'Azimuth' (.X) sign is changed to represent left/right and not front/behind. front/behind is the funtion's return value.
	 *
	 * @param	OutDotDist	.X = 'Direction' dot AxisX relative to plane (AxisX,AxisZ). (== Cos(Azimuth))
	 *						.Y = 'Direction' dot AxisX relative to plane (AxisX,AxisY). (== Sin(Elevation))
	 * @param	Direction	direction of target.
	 * @param	AxisX		X component of reference system.
	 * @param	AxisY		Y component of reference system.
	 * @param	AxisZ		Z component of reference system.
	 *
	 * @return	true if 'Direction' is facing AxisX (Direction dot AxisX >= 0.f)
	 */
	static  bool GetDotDistance(FVector2D &OutDotDist, const FVector &Direction, const FVector &AxisX, const FVector &AxisY, const FVector &AxisZ);

	/**
	 * Returns Azimuth and Elevation of vector 'Direction' in coordinate system O(AxisX,AxisY,AxisZ).
	 *
	 * Orientation: (consider 'O' the first person view of the player, and 'Direction' a vector pointing to an enemy)
	 * - positive azimuth means enemy is on the right of crosshair. (negative means left).
	 * - positive elevation means enemy is on top of crosshair, negative means below.
	 *
	 * @param	Direction		Direction of target.
	 * @param	AxisX			X component of reference system.
	 * @param	AxisY			Y component of reference system.
	 * @param	AxisZ			Z component of reference system.
	 *
	 * @return	FVector2D	X = Azimuth angle (in radians) (-PI, +PI)
	 *						Y = Elevation angle (in radians) (-PI/2, +PI/2)
	 */
	static  FVector2D GetAzimuthAndElevation(const FVector &Direction, const FVector &AxisX, const FVector &AxisY, const FVector &AxisZ);

	// Interpolation Functions

	/** Calculates the percentage along a line from MinValue to MaxValue that Value is. */
	static FORCEINLINE float GetRangePct(float MinValue, float MaxValue, float Value)
	{
		return (Value - MinValue) / (MaxValue - MinValue);
	}

	/** Same as above, but taking a 2d vector as the range. */
	static float GetRangePct(FVector2D const& Range, float Value);
	
	/** Basically a Vector2d version of Lerp. */
	static float GetRangeValue(FVector2D const& Range, float Pct);

	/**
	 * For the given value in the input range, returns the corresponding value in the output range.
	 * Useful for mapping one value range to another value range.  Output is clamped to the OutputRange.
	 * e.g. given that velocities [50..100] correspond to a sound volume of [0.2..1.4], this makes it easy to 
	 *      find the volume for a velocity of 77.
	 */
	static FORCEINLINE float GetMappedRangeValue(FVector2D const& InputRange, FVector2D const& OutputRange, float Value)
	{
		float const ClampedPct = Clamp<float>(GetRangePct(InputRange, Value), 0.f, 1.f);
		return GetRangeValue(OutputRange, ClampedPct);
	}

	/** Performs a linear interpolation between two values, Alpha ranges from 0-1 */
	template< class T, class U > 
	static  T Lerp( const T& A, const T& B, const U& Alpha )
	{
		return (T)(A + Alpha * (B-A));
	}

	/** Performs a linear interpolation between two values, Alpha ranges from 0-1. Handles full numeric range of T */
	template< class T > 
	static  T LerpStable( const T& A, const T& B, double Alpha )
	{
		return (T)((A * (1.0 - Alpha)) + (B * Alpha));
	}

	/** Performs a 2D linear interpolation between four values values, FracX, FracY ranges from 0-1 */
	template< class T, class U > 
	static  T BiLerp(const T& P00,const T& P10,const T& P01,const T& P11, const U& FracX, const U& FracY)
	{
		return Lerp(
			Lerp(P00,P10,FracX),
			Lerp(P01,P11,FracX),
			FracY
			);
	}

	/**
	 * Performs a cubic interpolation
	 *
	 * @param  P0 - end points
	 * @param  T0 - tangent directions at end points
	 * @param  A - distance along spline
	 *
	 * @return  Interpolated value
	 */
	template< class T, class U > 
	static  T CubicInterp( const T& P0, const T& T0, const T& P1, const T& T1, const U& A )
	{
		const float A2 = A  * A;
		const float A3 = A2 * A;

		return (T)(((2*A3)-(3*A2)+1) * P0) + ((A3-(2*A2)+A) * T0) + ((A3-A2) * T1) + (((-2*A3)+(3*A2)) * P1);
	}

	/**
	 * Performs a first derivative cubic interpolation
	 *
	 * @param  P0 - end points
	 * @param  T0 - tangent directions at end points
	 * @param  A - distance along spline
	 *
	 * @return  Interpolated value
	 */
	template< class T, class U > 
	static  T CubicInterpDerivative( const T& P0, const T& T0, const T& P1, const T& T1, const U& A )
	{
		T a = 6.f*P0 + 3.f*T0 + 3.f*T1 - 6.f*P1;
		T b = -6.f*P0 - 4.f*T0 - 2.f*T1 + 6.f*P1;
		T c = T0;

		const float A2 = A  * A;

		return (a * A2) + (b * A) + c;
	}

	/**
	 * Performs a second derivative cubic interpolation
	 *
	 * @param  P0 - end points
	 * @param  T0 - tangent directions at end points
	 * @param  A - distance along spline
	 *
	 * @return  Interpolated value
	 */
	template< class T, class U > 
	static  T CubicInterpSecondDerivative( const T& P0, const T& T0, const T& P1, const T& T1, const U& A )
	{
		T a = 12.f*P0 + 6.f*T0 + 6.f*T1 - 12.f*P1;
		T b = -6.f*P0 - 4.f*T0 - 2.f*T1 + 6.f*P1;

		return (a * A) + b;
	}

	/** Interpolate between A and B, applying an ease in/out function.  Exp controls the degree of the curve. */
	template< class T > 
	static  T InterpEaseInOut( const T& A, const T& B, float Alpha, float Exp )
	{
		float const ModifiedAlpha = ( Alpha < 0.5f ) ?
			0.5f * Pow(2.f * Alpha, Exp) :
		1.f - 0.5f * Pow(2.f * (1.f - Alpha), Exp);

		return Lerp<T>(A, B, ModifiedAlpha);
	}

	// Rotator specific interpolation
	template< class U > static FRotator Lerp( const FRotator& A, const FRotator& B, const U& Alpha);

	// Quat-specific interpolation

	template< class U > static FQuat Lerp( const FQuat& A, const FQuat& B, const U& Alpha);
	template< class U > static FQuat BiLerp(const FQuat& P00, const FQuat& P10, const FQuat& P01, const FQuat& P11, float FracX, float FracY);

	/**
	 * In the case of quaternions, we use a bezier like approach.
	 * T - Actual 'control' orientations.
	 */
	template< class U > static FQuat CubicInterp( const FQuat& P0, const FQuat& T0, const FQuat& P1, const FQuat& T1, const U& A);

	// Special-case interpolation

	/** Interpolate a normal vector Current to Target, by interpolating the angle between those vectors with constant step. */
	static  FVector VInterpNormalRotationTo(const FVector& Current, const FVector& Target, float DeltaTime, float RotationSpeedDegrees);

	/** Interpolate vector from Current to Target with constant step */
	static  FVector VInterpConstantTo(const FVector Current, const FVector& Target, float DeltaTime, float InterpSpeed);

	/** Interpolate vector from Current to Target. Scaled by distance to Target, so it has a strong start speed and ease out. */
	static  FVector VInterpTo( const FVector& Current, const FVector& Target, float DeltaTime, float InterpSpeed );
	
	/** Interpolate vector2D from Current to Target with constant step */
	static  FVector2D Vector2DInterpConstantTo( const FVector2D& Current, const FVector2D& Target, float DeltaTime, float InterpSpeed );

	/** Interpolate vector2D from Current to Target. Scaled by distance to Target, so it has a strong start speed and ease out. */
	static  FVector2D Vector2DInterpTo( const FVector2D& Current, const FVector2D& Target, float DeltaTime, float InterpSpeed );

	/** Interpolate rotator from Current to Target with constant step */
	static  FRotator RInterpConstantTo( const FRotator& Current, const FRotator& Target, float& DeltaTime, float InterpSpeed);

	/** Interpolate rotator from Current to Target. Scaled by distance to Target, so it has a strong start speed and ease out. */
	static  FRotator RInterpTo( const FRotator& Current, const FRotator& Target, const float& DeltaTime, float InterpSpeed);

	/** Interpolate float from Current to Target with constant step */
	static  float FInterpConstantTo( float Current, float Target, float DeltaTime, float InterpSpeed );

	/** Interpolate float from Current to Target. Scaled by distance to Target, so it has a strong start speed and ease out. */
	static  float FInterpTo( float Current, float Target, float DeltaTime, float InterpSpeed );

	/**
	 * Simple function to create a pulsating scalar value
	 *
	 * @param  InCurrentTime  Current absolute time
	 * @param  InPulsesPerSecond  How many full pulses per second?
	 * @param  InPhase  Optional phase amount, between 0.0 and 1.0 (to synchronize pulses)
	 *
	 * @return  Pulsating value (0.0-1.0)
	 */
	static float MakePulsatingValue( const double InCurrentTime, const float InPulsesPerSecond, const float InPhase = 0.0f )
	{
		return 0.5f + 0.5f * (float)sin( ( ( 0.25f + InPhase ) * PI * 2.0 ) + ( InCurrentTime * PI * 2.0 ) * InPulsesPerSecond );
	}

	// Geometry intersection 


	/**
	 * Find the intersection of an infinite line (defined by two points) and
	 * a plane.  Assumes that the line and plane do indeed intersect; you must
	 * make sure they're not parallel before calling.
	 */
	static FVector LinePlaneIntersection( const FVector &Point1, const FVector &Point2, const FVector &PlaneOrigin, const FVector &PlaneNormal);
	static FVector LinePlaneIntersection( const FVector &Point1, const FVector &Point2, const FPlane  &Plane);

	/**
	 * Determine if a plane and an AABB intersect
	 * @param P - the plane to test
	 * @param AABB - the axis aligned bounding box to test
	 * @return if collision occurs
	 */
	static  bool PlaneAABBIntersection(const FPlane& P, const FBox& AABB);

	/**
	 * Performs a sphere vs box intersection test using Arvo's algorithm:
	 *
	 *	for each i in (x, y, z)
	 *		if (SphereCenter(i) < BoxMin(i)) d2 += (SphereCenter(i) - BoxMin(i)) ^ 2
	 *		else if (SphereCenter(i) > BoxMax(i)) d2 += (SphereCenter(i) - BoxMax(i)) ^ 2
	 *
	 * @param SphereCenter the center of the sphere being tested against the AABB
	 * @param RadiusSquared the size of the sphere being tested
	 * @param AABB the box being tested against
	 *
	 * @return Whether the sphere/box intersect or not.
	 */
	static bool SphereAABBIntersection(const FVector& SphereCenter,const float RadiusSquared,const FBox& AABB);

	/**
	 * Converts a sphere into a point plus radius squared for the test above
	 */
	static bool SphereAABBIntersection(const FSphere& Sphere,const FBox& AABB);

	/** Determines whether a point is inside a box. */
	static bool PointBoxIntersection( const FVector& Point, const FBox& Box );

	/** Determines whether a line intersects a box. */
	static bool LineBoxIntersection( const FBox& Box, const FVector& Start, const FVector& End, const FVector& Direction, const FVector& OneOverDirection );

	/* Swept-Box vs Box test */
	static  bool LineExtentBoxIntersection(const FBox& inBox, const FVector& Start, const FVector& End, const FVector& Extent, FVector& HitLocation, FVector& HitNormal, float& HitTime);

	/** Determines whether a line intersects a sphere. */
	static bool LineSphereIntersection(const FVector& Start,const FVector& Dir,float Length,const FVector& Origin,float Radius);

	/**
	 * Assumes the cone tip is at 0,0,0 (means the SphereCenter is relative to the cone tip)
	 * @return true: cone and sphere do intersect, false otherwise
	 */
	static  bool SphereConeIntersection(const FVector& SphereCenter, float SphereRadius, const FVector& ConeAxis, float ConeAngleSin, float ConeAngleCos);

	/** Find the point on line segment from LineStart to LineEnd which is closest to Point */
	static  FVector ClosestPointOnLine(const FVector& LineStart, const FVector& LineEnd, const FVector& Point);

	/** Compute intersection point of three planes. Return 1 if valid, 0 if infinite. */
	static bool IntersectPlanes3( FVector& I, const FPlane& P1, const FPlane& P2, const FPlane& P3 );

	/**
	 * Compute intersection point and direction of line joining two planes.
	 * Return 1 if valid, 0 if infinite.
	 */
	static bool IntersectPlanes2( FVector& I, FVector& D, const FPlane& P1, const FPlane& P2 );

	/**
	 * Calculates the distance of a given Point in world space to a given line,
	 * defined by the vector couple (Origin, Direction).
	 *
	 * @param	Point				point to check distance to Axis
	 * @param	Direction			    unit vector indicating the direction to check against
	 * @param	Origin				point of reference used to calculate distance
	 * @param	OutClosestPoint	optional point that represents the closest point projected onto Axis
	 *
	 * @return	distance of Point from line defined by (Origin, Direction)
	 */
	static  float PointDistToLine(const FVector &Point, const FVector &Direction, const FVector &Origin, FVector &OutClosestPoint);
	static  float PointDistToLine(const FVector &Point, const FVector &Direction, const FVector &Origin);

	/**
	 * Returns closest point on a segment to a given point.
	 * The idea is to project point on line formed by segment.
	 * Then we see if the closest point on the line is outside of segment or inside.
	 *
	 * @param	Point			point for which we find the closest point on the segment
	 * @param	StartPoint		StartPoint of segment
	 * @param	EndPoint		EndPoint of segment
	 *
	 * @return	point on the segment defined by (StartPoint, EndPoint) that is closest to Point.
	 */
	static  FVector ClosestPointOnSegment(const FVector &Point, const FVector &StartPoint, const FVector &EndPoint);

	/**
	 * Returns distance from a point to the closest point on a segment.
	 *
	 * @param	Point			point to check distance for
	 * @param	StartPoint		StartPoint of segment
	 * @param	EndPoint		EndPoint of segment
	 *
	 * @return	closest distance from Point to segment defined by (StartPoint, EndPoint).
	 */
	static  float PointDistToSegment(const FVector &Point, const FVector &StartPoint, const FVector &EndPoint);

	/**
	 * Returns square of the distance from a point to the closest point on a segment.
	 *
	 * @param	Point			point to check distance for
	 * @param	StartPoint		StartPoint of segment
	 * @param	EndPoint		EndPoint of segment
	 *
	 * @return	square of the closest distance from Point to segment defined by (StartPoint, EndPoint).
	 */
	static  float PointDistToSegmentSquared(const FVector &Point, const FVector &StartPoint, const FVector &EndPoint);

	/** 
	 * Find closest points between 2 segments.
	 * @param	(A1, B1)	defines the first segment.
	 * @param	(A2, B2)	defines the second segment.
	 * @param	OutP1		Closest point on segment 1 to segment 2.
	 * @param	OutP2		Closest point on segment 2 to segment 1.
	 */
	static  void SegmentDistToSegment(FVector A1, FVector B1, FVector A2, FVector B2, FVector& OutP1, FVector& OutP2);

	/** 
	 * Find closest points between 2 segments.
	 * @param	(A1, B1)	defines the first segment.
	 * @param	(A2, B2)	defines the second segment.
	 * @param	OutP1		Closest point on segment 1 to segment 2.
	 * @param	OutP2		Closest point on segment 2 to segment 1.
	 */
	static  void SegmentDistToSegmentSafe(FVector A1, FVector B1, FVector A2, FVector B2, FVector& OutP1, FVector& OutP2);

	/**
	 * returns the time (t) of the intersection of the passed segment and a plane (could be <0 or >1)
	 * @param StartPoint - start point of segment
	 * @param EndPoint   - end point of segment
	 * @param Plane		- plane to intersect with
	 * @return time(T) of intersection
	 */
	static  float GetTForSegmentPlaneIntersect(const FVector& StartPoint, const FVector& EndPoint, const FPlane& Plane);

	/**
	 * Returns true if there is an intersection between the segment specified by StartPoint and Endpoint, and
	 * the plane on which polygon Plane lies. If there is an intersection, the point is placed in IntersectionPoint
	 * @param StartPoint - start point of segment
	 * @param EndPoint   - end point of segment
	 * @param Plane		- plane to intersect with
	 * @param out_InterSectPoint - out var for the point on the segment that intersects the mesh (if any)
	 * @return true if intersection occured
	 */
	static  bool SegmentPlaneIntersection(const FVector& StartPoint, const FVector& EndPoint, const FPlane& Plane, FVector& out_IntersectPoint);

	/**
	 * Returns closest point on a triangle to a point.
	 * The idea is to identify the halfplanes that the point is
	 * in relative to each triangle segment "plane"
	 *
	 * @param	Point			point to check distance for
	 * @param	A,B,C			counter clockwise ordering of points defining a triangle
	 *
	 * @return	Point on triangle ABC closest to given point
	 */
	static  FVector ClosestPointOnTriangleToPoint(const FVector& Point, const FVector& A, const FVector& B, const FVector& C);

	/**
	 * Returns closest point on a tetrahedron to a point.
	 * The idea is to identify the halfplanes that the point is
	 * in relative to each face of the tetrahedron
	 *
	 * @param	Point			point to check distance for
	 * @param	A,B,C,D			four points defining a tetrahedron
	 *
	 * @return	Point on tetrahedron ABCD closest to given point
	 */
	static  FVector ClosestPointOnTetrahedronToPoint(const FVector& Point, const FVector& A, const FVector& B, const FVector& C, const FVector& D);

	/** 
	 * Find closest point on a Sphere to a Line.
	 * When line intersects		Sphere, then closest point to LineOrigin is returned.
	 * @param SphereOrigin		Origin of Sphere
	 * @param SphereRadius		Radius of Sphere
	 * @param LineOrigin		Origin of line
	 * @param LineDir			Direction of line. Needs to be normalized!!
	 * @param OutClosestPoint	Closest point on sphere to given line.
	 */
	static  void SphereDistToLine(FVector SphereOrigin, float SphereRadius, FVector LineOrigin, FVector LineDir, FVector& OutClosestPoint);

	/**
	 * Calculates whether a Point is within a cone segment, and also what percentage within the cone (100% is along the center line, whereas 0% is along the edge)
	 *
	 * @param Point - The Point in question
	 * @param ConeStartPoint - the beginning of the cone (with the smallest radius)
	 * @param ConeLine - the line out from the start point that ends at the largest radius point of the cone
	 * @param RadiusAtStart - the radius at the ConeStartPoint (0 for a 'proper' cone)
	 * @param RadiusAtEnd - the largest radius of the cone
	 * @param PercentageOut - output variable the holds how much within the cone the point is (1 = on center line, 0 = on exact edge or outside cone).
	 *
	 * @return true if the point is within the cone, false otherwise.
	 */
	static  bool GetDistanceWithinConeSegment(FVector Point, FVector ConeStartPoint, FVector ConeLine, float RadiusAtStart, float RadiusAtEnd, float &PercentageOut);


	// Formatting functions

	/**
	 * Formats an integer value into a human readable string (i.e. 12345 becomes "12,345")
	 *
	 * @param	Val		The value to use
	 * @return	FString	The human readable string
	 */
	// static FString FormatIntToHumanReadable(int32 Val);


	// Utilities

	/**
	 * Tests a memory region to see that it's working properly.
	 *
	 * @param BaseAddress	Starting address
	 * @param NumBytes		Number of bytes to test (will be rounded down to a multiple of 4)
	 * @return				true if the memory region passed the test
	 */
	// static  bool MemoryTest( void* BaseAddress, uint32 NumBytes );

	/**
	 * Evaluates a numerical equation.
	 *
	 * Operators and precedence: 1:+- 2:/% 3:* 4:^ 5:&|
	 * Unary: -
	 * Types: Numbers (0-9.), Hex ($0-$f)
	 * Grouping: ( )
	 *
	 * @param	Str			String containing the equation.
	 * @param	OutValue		Pointer to storage for the result.
	 * @return				1 if successful, 0 if equation fails.
	 */
	// static  bool Eval( FString Str, float& OutValue );

	/*
	 * Computes the barycentric coordinates for a given point in a triangle - simpler version
	 *
	 * @param	Point			point to convert to barycentric coordinates (in plane of ABC)
	 * @param	A,B,C			three non-colinear points defining a triangle in CCW
	 * 
	 * @return Vector containing the three weights a,b,c such that Point = a*A + b*B + c*C
	 *							                                or Point = A + b*(B-A) + c*(C-A) = (1-b-c)*A + b*B + c*C
	 */
	static  FVector GetBaryCentric2D(const FVector& Point, const FVector& A, const FVector& B, const FVector& C);

	/*
	 * Computes the barycentric coordinates for a given point in a triangle
	 *
	 * @param	Point			point to convert to barycentric coordinates (in plane of ABC)
	 * @param	A,B,C			three non-collinear points defining a triangle in CCW
	 * 
	 * @return Vector containing the three weights a,b,c such that Point = a*A + b*B + c*C
	 *							                               or Point = A + b*(B-A) + c*(C-A) = (1-b-c)*A + b*B + c*C
	 */
	static  FVector ComputeBaryCentric2D(const FVector& Point, const FVector& A, const FVector& B, const FVector& C);

	/*
	 * Computes the barycentric coordinates for a given point on a tetrahedron (3D)
	 *
	 * @param	Point			point to convert to barycentric coordinates
	 * @param	A,B,C,D			four points defining a tetrahedron
	 *
	 * @return Vector containing the four weights a,b,c,d such that Point = a*A + b*B + c*C + d*D
	 */
	static  FVector4 ComputeBaryCentric3D(const FVector& Point, const FVector& A, const FVector& B, const FVector& C, const FVector& D);

	/** 32 bit values where BitFlag[x] == (1<<x) */
	static  const uint32 BitFlag[32];

	/** 
	 * Returns a smooth Hermite interpolation between 0 and 1 for the value X (where X ranges between A and B)
	 * Clamped to 0 for X <= A and 1 for X >= B.
	 *
	 * @param A Minimum value of X
	 * @param B Maximum value of X
	 * @param X Parameter
	 *
	 * @return Smoothed value between 0 and 1
	 */
	static float SmoothStep(float A, float B, float X)
	{
		if (X < A)
		{
			return 0.0f;
		}
		else if (X >= B)
		{
			return 1.0f;
		}
		const float InterpFraction = (X - A) / (B - A);
		return InterpFraction * InterpFraction * (3.0f - 2.0f * InterpFraction);
	}
	
	/**
	 * Get a bit in memory created from bitflags (uint32 Value:1), used for EngineShowFlags,
	 * TestBitFieldFunctions() tests the implementation
	 */
	static inline bool ExtractBoolFromBitfield(uint8* Ptr, uint32 Index)
	{
		uint8* BytePtr = Ptr + Index / 8;
		uint8 Mask = 1 << (Index & 0x7);

		return (*BytePtr & Mask) != 0;
	}

	/**
	 * Set a bit in memory created from bitflags (uint32 Value:1), used for EngineShowFlags,
	 * TestBitFieldFunctions() tests the implementation
	 */
	static inline void SetBoolInBitField(uint8* Ptr, uint32 Index, bool bSet)
	{
		uint8* BytePtr = Ptr + Index / 8;
		uint8 Mask = 1 << (Index & 0x7);

		if(bSet)
		{
			*BytePtr |= Mask;
		}
		else
		{
			*BytePtr &= ~Mask;
		}
	}

	/**
	 * Handy to apply scaling in the editor
	 * @param Dst in and out
	 */
	static  void ApplyScaleToFloat(float& Dst, const FVector& DeltaScale, float Magnitude = 1.0f);
};
