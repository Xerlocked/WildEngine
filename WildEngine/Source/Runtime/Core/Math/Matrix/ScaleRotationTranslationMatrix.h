﻿// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

/** Combined Scale rotation and translation matrix */
class FScaleRotationTranslationMatrix : public FMatrix
{
public:

    /** Constructor
    *
    * @param Scale scale to apply to matrix
    * @param Rot rotation
    * @param Origin translation to apply
    */
    FScaleRotationTranslationMatrix(const FVector& Scale, const FRotator& Rot, const FVector& Origin);
};

FORCEINLINE FScaleRotationTranslationMatrix::FScaleRotationTranslationMatrix(const FVector& Scale, const FRotator& Rot, const FVector& Origin)
{
    const float	SR	= FMath::Sin(Rot.Roll * PI / 180.f);
    const float	SP	= FMath::Sin(Rot.Pitch * PI / 180.f);
    const float	SY	= FMath::Sin(Rot.Yaw * PI / 180.f);
    const float	CR	= FMath::Cos(Rot.Roll * PI / 180.f);
    const float	CP	= FMath::Cos(Rot.Pitch * PI / 180.f);
    const float	CY	= FMath::Cos(Rot.Yaw * PI / 180.f);

    M[0][0]	= (CP * CY) * Scale.X;
    M[0][1]	= (CP * SY) * Scale.X;
    M[0][2]	= (SP) * Scale.X;
    M[0][3]	= 0.f;

    M[1][0]	= (SR * SP * CY - CR * SY) * Scale.Y;
    M[1][1]	= (SR * SP * SY + CR * CY) * Scale.Y;
    M[1][2]	= (- SR * CP) * Scale.Y;
    M[1][3]	= 0.f;

    M[2][0]	= ( -( CR * SP * CY + SR * SY ) ) * Scale.Z;
    M[2][1]	= (CY * SR - CR * SP * SY) * Scale.Z;
    M[2][2]	= (CR * CP) * Scale.Z;
    M[2][3]	= 0.f;

    M[3][0]	= Origin.X;
    M[3][1]	= Origin.Y;
    M[3][2]	= Origin.Z;
    M[3][3]	= 1.f;
}