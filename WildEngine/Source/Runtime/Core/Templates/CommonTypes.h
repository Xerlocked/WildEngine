#pragma once
#include "Math/Vector.h"
#include "Components/SceneComponent.h"

struct FVertexType
{
    float x, y, z;    // Position
    float r, g, b, a; // Color
};

enum class EPrimitiveType
{
    Cube,
    Sphere,
    Triangle
};

enum class EGizmoType
{
    Translation,
    Rotation,
    Scale
};

struct FHitResult
{
    bool bHit;
    float Distance;
    FVector HitLocation;
    USceneComponent* HitObject;

    FHitResult() : bHit(false), Distance(FLT_MAX), HitLocation(), HitObject(nullptr) {}
};