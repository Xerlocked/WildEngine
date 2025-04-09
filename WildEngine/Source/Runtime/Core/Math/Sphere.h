﻿// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

/*=============================================================================
	Sphere.h: Declares the FSphere class.
=============================================================================*/

#pragma once


/**
 * Implements a basic sphere.
 */
class FSphere
{
public:

	/**
	 * Holds the sphere's center.
	 */
	FVector Center;

	/**
	 * Holds the sphere's radius.
	 */
	float W;


public:

	/**
	 * Default constructor.
	 */
	FSphere() { }

	/**
	 * Creates and initializes a new sphere.
	 *
	 * @param int32 Passing int32 sets up zeroed sphere.
	 */
	FSphere(int32)
		: Center(0, 0, 0)
		, W(0)
	{ }

	/**
	 * Creates and initializes a new sphere with the specified parameters.
	 *
	 * @param InV - Center of sphere.
	 * @param InW - Radius of sphere.
	 */
	FSphere(FVector InV, float InW)
		: Center(InV)
		, W(InW)
	{ }

	/**
	 * Constructor.
	 *
	 * @param Pts Pointer to list of points this sphere must contain.
	 * @param Count How many points are in the list.
	 */
	 FSphere(const FVector* Pts, int32 Count);


public:

	/**
	 * Check whether two spheres are the same within specified tolerance.
	 *
	 * @param Sphere The other sphere.
	 * @param Tolerance Error Tolerance.
	 *
	 * @return true if spheres are equal within specified tolerance, otherwise false.
	 */
	bool Equals(const FSphere& Sphere, float Tolerance = KINDA_SMALL_NUMBER) const
	{
		return Center.Equals(Sphere.Center, Tolerance) && FMath::Abs(W - Sphere.W) < Tolerance;
	}

	/**
	 * Check whether sphere is inside of another.
	 *
	 * @param Other The other sphere.
	 * @param Tolerance Error Tolerance.
	 *
	 * @return true if sphere is inside another, otherwise false.
	 */
	bool IsInside(const FSphere& Other, float Tolerance = KINDA_SMALL_NUMBER) const
	{
		if (W > Other.W - Tolerance)
		{
			return false;
		}

		return (Center - Other.Center).SizeSquared() <= FMath::Square(Other.W - Tolerance - W);
	}

	/**
	 * Get result of Transforming sphere by Matrix.
	 *
	 * @param M Matrix to transform by.
	 *
	 * @return Result of transformation.
	 */
	 FSphere TransformBy(const FMatrix& M) const;

	/**
	 * Get result of Transforming sphere with Transform.
	 *
	 * @param M Transform information.
	 *
	 * @return Result of transformation.
	 */
	 FSphere TransformBy(const FTransform& M) const;
};