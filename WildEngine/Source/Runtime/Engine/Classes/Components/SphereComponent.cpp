#include "SphereComponent.h"
#include "Renderer/URenderer.h"

USphereComponent::USphereComponent()
{
}
USphereComponent::USphereComponent(Renderer* InRenderer)
{
    Renderer = InRenderer;
    Initialize();
}

USphereComponent::USphereComponent(Renderer* InRenderer, const FVector& InLocation)
{
    Renderer = InRenderer;
    RelativeLocation = InLocation;
    Initialize();
}
USphereComponent::USphereComponent(const USphereComponent&)
{
}
USphereComponent::~USphereComponent()
{
    // �ʿ��� ��� ���ҽ� ���� �ڵ� �߰�
}

UClass* USphereComponent::GetClass()
{
    static UClass SphereClass("USphereComponent", UObject::GetClass());
    return &SphereClass;
}

UClass* USphereComponent::GetInstanceClass() const
{
    return GetClass();
}

bool USphereComponent::CheckRayIntersection(FVector RayOrigin, FVector RayDirection, FHitResult& OutHitResult)
{
    FVector SphereCenter = RelativeLocation; // ���� ���� ��ǥ
    float SphereRadius = RelativeScale3D.X; // ���� ������

    FVector L = SphereCenter - RayOrigin;
    float tca = L.Dot(RayDirection);
    float d2 = L.Dot(L) - tca * tca;
    float radius2 = SphereRadius * SphereRadius;

    if (d2 > radius2)
        return false; // �浹 ����

    float thc = sqrt(radius2 - d2);
    float t0 = tca - thc;
    float t1 = tca + thc;

    if (t0 < 0 && t1 < 0)
        return false;

    OutHitResult.bHit = true;
    OutHitResult.Distance = (t0 < 0) ? t1 : t0;
    OutHitResult.HitLocation = RayOrigin + RayDirection * OutHitResult.Distance;
    OutHitResult.HitObject = this;

    return true;
}
void USphereComponent::Initialize()
{
    NumVertices = sizeof(sphere_vertices) / sizeof(FVertexType);
    VertexBuffer = Renderer->CreateVertexBuffer(sphere_vertices, sizeof(sphere_vertices));
}