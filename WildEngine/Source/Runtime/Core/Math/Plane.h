// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

/**
 * FPlane.
 * Stores the coeffecients as Ax+By+Cz=D.
 * Note that this is different than many other Plane classes that use Ax+By+Cz+D=0.
 */
alignas(16) class FPlane : public FVector
{
public:
	// Variables.
	float W;

	/** Constructor.*/
	FORCEINLINE FPlane();

	/**
	 * Copy Constructor.
	 *
	 * @param P Plane to copy from.
	 */
	FORCEINLINE FPlane( const FPlane& P );

	/**
	 * Constructor.
	 *
	 * @param V 4D vector to set up plane.
	 */
	FORCEINLINE FPlane( const FVector4& V );

	/**
	 * Constructor.
	 *
	 * @param InX X Coordinate.
	 * @param InY Y Coordinate.
	 * @param InZ Z Coordinate.
	 * @param InW W Coordinate.
	 */
	FORCEINLINE FPlane( float InX, float InY, float InZ, float InW );

	/**
	 * Constructor.
	 *
	 * @param InNormal Plane Normal Vector.
	 * @param InW Plane W Coordinate.
	 */
	FORCEINLINE FPlane( FVector InNormal, float InW );

	/**
	 * Constructor.
	 *
	 * @param InBase Base point in plane.
	 * @param InNormal Plane Normal Vector.
	 */
	FORCEINLINE FPlane( FVector InBase, const FVector &InNormal );

	/**
	 * Constructor.
	 *
	 * @param A First point in the plane.
	 * @param B Second point in the plane.
	 * @param C Third point in the plane.
	 */
	FPlane( FVector A, FVector B, FVector C );

	// Functions.

	/**
	 * Calculates distance between plane and a point.
	 *
	 * @param P The other point.
	 *
	 * @return >0: point is in front of the plane, <0: behind, =0: on the plane */
	FORCEINLINE float PlaneDot( const FVector &P ) const;

	/**
	 * Get a flipped version of the plane.
	 *
	 * @return A flipped version of the plane.
	 */
	FPlane Flip() const;

	/**
	 * Get the result of transforming the plane by a Matrix.
	 *
	 * @param M The matrix to transform plane with.
	 *
	 * @return The result of transform.
	 */
	FPlane TransformBy( const FMatrix& M ) const;

	/**
	 * You can optionally pass in the matrices transpose-adjoint, which save it recalculating it.
	 * MSM: If we are going to save the transpose-adjoint we should also save the more expensive
	 * determinant.
	 *
	 * @param M The Matrix to transform plane with.
	 * @param DetM Determinant of Matrix.
	 * @param TA Transpose-adjoint of Matrix.
	 *
	 * @return The result of transform.
	 */
	FPlane TransformByUsingAdjointT( const FMatrix& M, float DetM, const FMatrix& TA ) const;

	/**
	 * Check if two planes are identical.
	 *
	 * @param V The other plane.
	 *
	 * @return true if planes are identical, otherwise false.
	 */
	bool operator==( const FPlane& V ) const;

	/**
	 * Check if two planes are different.
	 *
	 * @param V The other plane.
	 *
	 * @return true if planes are different, otherwise false.
	 */
	bool operator!=( const FPlane& V ) const;

	/**
	 * Checks whether two planes are equal within specified tolerance.
	 *
	 * @param V The other plane.
	 * @param Tolerance Error Tolerance.
	 *
	 * @return true if the two planes are equal within specified tolerance, otherwise false.
	 */
	bool Equals(const FPlane& V, float Tolerance=KINDA_SMALL_NUMBER) const;

	/**
	 * Calculates dot product of two planes.
	 *
	 * @param V The other plane.
	 *
	 * @return The dot product.
	 */
	FORCEINLINE float operator|( const FPlane& V ) const;

	/**
	 * Gets result of adding a plane to this.
	 *
	 * @param V The other plane.
	 *
	 * @return The result of adding a plane to this.
	 */
	FPlane operator+( const FPlane& V ) const;

	/**
	 * Gets result of subtracting a plane from this.
	 *
	 * @param V The other plane.
	 *
	 * @return The result of subtracting a plane from this.
	 */
	FPlane operator-( const FPlane& V ) const;

	/**
	 * Gets result of dividing a plane.
	 *
	 * @param Scale What to divide by.
	 *
	 * @return The result of division.
	 */
	FPlane operator/( float Scale ) const;

	/**
	 * Gets result of scaling a plane.
	 *
	 * @param Scale The scaling factor.
	 *
	 * @return The result of scaling.
	 */
	FPlane operator*( float Scale ) const;

	/**
	 * Gets result of multiplying a plane with this.
	 *
	 * @param V The other plane.
	 *
	 * @return The result of multiplying a plane with this.
	 */
	FPlane operator*( const FPlane& V ) const;

	/**
	 * Add another plane to this.
	 *
	 * @param V The other plane.
	 *
	 * @return Copy of plane after addition.
	 */
	FPlane operator+=( const FPlane& V );

	/**
	 * Subtract another plane from this.
	 *
	 * @param V The other plane.
	 *
	 * @return Copy of plane after subtraction.
	 */
	FPlane operator-=( const FPlane& V );

	/**
	 * Scale this plane.
	 *
	 * @param Scale The scaling factor.
	 *
	 * @return Copy of plane after scaling.
	 */
	FPlane operator*=( float Scale );

	/**
	 * Multiply another plane with this.
	 *
	 * @param V The other plane.
	 *
	 * @return Copy of plane after multiplication.
	 */
	FPlane operator*=( const FPlane& V );

	/**
	 * Divide this plane.
	 *
	 * @param V What to divide by.
	 *
	 * @return Copy of plane after division.
	 */
	FPlane operator/=( float V );
	
};

FORCEINLINE FPlane::FPlane()
{}

FORCEINLINE FPlane::FPlane( const FPlane& P )
	:	FVector(P)
	,	W(P.W)
{}

FORCEINLINE FPlane::FPlane( const FVector4& V )
	:	FVector(V)
	,	W(V.W)
{}

FORCEINLINE FPlane::FPlane( float InX, float InY, float InZ, float InW )
	:	FVector(InX,InY,InZ)
	,	W(InW)
{}

FORCEINLINE FPlane::FPlane( FVector InNormal, float InW )
	:	FVector(InNormal), W(InW)
{}

FORCEINLINE FPlane::FPlane( FVector InBase, const FVector &InNormal )
	:	FVector(InNormal)
	,	W(InBase | InNormal)
{}

FORCEINLINE FPlane::FPlane( FVector A, FVector B, FVector C )
	:	FVector( ((B-A)^(C-A)).SafeNormal() )
	,	W( A | ((B-A)^(C-A)).SafeNormal() )
{}

FORCEINLINE float FPlane::PlaneDot( const FVector &P ) const
{
	return X*P.X + Y*P.Y + Z*P.Z - W;
}

FORCEINLINE FPlane FPlane::Flip() const
{
	return {-X,-Y,-Z,-W};
}

FORCEINLINE bool FPlane::operator==( const FPlane& V ) const
{
	return X==V.X && Y==V.Y && Z==V.Z && W==V.W;
}

FORCEINLINE bool FPlane::operator!=( const FPlane& V ) const
{
	return X!=V.X || Y!=V.Y || Z!=V.Z || W!=V.W;
}

FORCEINLINE bool FPlane::Equals(const FPlane& V, float Tolerance) const
{
	return FMath::Abs(X-V.X) < Tolerance && FMath::Abs(Y-V.Y) < Tolerance && FMath::Abs(Z-V.Z) < Tolerance && FMath::Abs(W-V.W) < Tolerance;
}

FORCEINLINE float FPlane::operator|( const FPlane& V ) const
{
	return X*V.X + Y*V.Y + Z*V.Z + W*V.W;
}

FORCEINLINE FPlane FPlane::operator+( const FPlane& V ) const
{
	return {X + V.X, Y + V.Y, Z + V.Z, W + V.W};
}

FORCEINLINE FPlane FPlane::operator-( const FPlane& V ) const
{
	return {X - V.X, Y - V.Y, Z - V.Z, W - V.W};
}

FORCEINLINE FPlane FPlane::operator/( float Scale ) const
{
	const float RScale = 1.f/Scale;
	return {X * RScale, Y * RScale, Z * RScale, W * RScale};
}

FORCEINLINE FPlane FPlane::operator*( float Scale ) const
{
	return {X * Scale, Y * Scale, Z * Scale, W * Scale};
}

FORCEINLINE FPlane FPlane::operator*( const FPlane& V ) const
{
	return {X*V.X,Y*V.Y,Z*V.Z,W*V.W};
}

FORCEINLINE FPlane FPlane::operator+=( const FPlane& V )
{
	X += V.X; Y += V.Y; Z += V.Z; W += V.W;
	return *this;
}

FORCEINLINE FPlane FPlane::operator-=( const FPlane& V )
{
	X -= V.X; Y -= V.Y; Z -= V.Z; W -= V.W;
	return *this;
}

FORCEINLINE FPlane FPlane::operator*=( float Scale )
{
	X *= Scale; Y *= Scale; Z *= Scale; W *= Scale;
	return *this;
}

FORCEINLINE FPlane FPlane::operator*=( const FPlane& V )
{
	X *= V.X; Y *= V.Y; Z *= V.Z; W *= V.W;
	return *this;
}

FORCEINLINE FPlane FPlane::operator/=( float V )
{
	const float RV = 1.f/V;
	X *= RV; Y *= RV; Z *= RV; W *= RV;
	return *this;
}