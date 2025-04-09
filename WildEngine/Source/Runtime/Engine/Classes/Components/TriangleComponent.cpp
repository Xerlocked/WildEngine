#include "TriangleComponent.h"
#include "Renderer/URenderer.h"

UTriangleComponent::UTriangleComponent()
{
}
UTriangleComponent::UTriangleComponent(Renderer* InRenderer)
{
    Renderer = InRenderer;
    Initialize();
}
UTriangleComponent::UTriangleComponent(Renderer* InRenderer, const FVector& InLocation)
{
    Renderer = InRenderer;
    RelativeLocation = InLocation;
    Initialize();
}
UTriangleComponent::UTriangleComponent(const UTriangleComponent&)
{
}
UTriangleComponent::~UTriangleComponent()
{
}

UClass* UTriangleComponent::GetClass()
{
    static UClass TriangleClass("UTriangleComponent", UObject::GetClass());
    return &TriangleClass;
}

UClass* UTriangleComponent::GetInstanceClass() const
{
    return GetClass();
}

struct triangle3
{
    FVector a;
    FVector b;
    FVector c;
};

bool ray_intersects_triangle(const FVector& ray_origin,
    const FVector& ray_vector,
    const triangle3& triangle,
    FVector& hit_point)
{
    constexpr float epsilon = std::numeric_limits<float>::epsilon();

    // �ﰢ���� �� ���� ���
    FVector edge1 = triangle.b - triangle.a;
    FVector edge2 = triangle.c - triangle.a;

    // ���� ���Ϳ� edge2�� ����
    FVector ray_cross_e2 = ray_vector.Cross(edge2);
    float det = edge1.Dot(ray_cross_e2);

    if (det > -epsilon && det < epsilon)
        return false; // ������ �ﰢ���� ������

    float inv_det = 1.0f / det;
    FVector s = ray_origin - triangle.a;
    float u = inv_det * s.Dot(ray_cross_e2);

    // u�� [0,1] ���� ���� �ִ��� Ȯ��
    if (u < 0.0f || u > 1.0f)
        return false;

    FVector s_cross_e1 = s.Cross(edge1);
    float v = inv_det * ray_vector.Dot(s_cross_e1);

    // v�� [0,1] ���� ���� �ְ� u+v<=1 ���� Ȯ��
    if (v < 0.0f || (u + v) > 1.0f)
        return false;

    // t�� ����Ͽ� ������ �ﰢ���� �������� ����
    float t = inv_det * edge2.Dot(s_cross_e1);
    if (t > epsilon) // ������ ���ʿ��� ����
    {
        hit_point = ray_origin + ray_vector * t;
        return true;
    }
    return false;
}

bool UTriangleComponent::CheckRayIntersection(FVector RayOrigin, FVector RayDirection, FHitResult& OutHitResult)
{
    // ���� ������ �ﰢ�� ������ (�߽��� 0,0,0)
    FVector v0_local = FVector(0.0f, 1.0f, 0.0f);
    FVector v1_local = FVector(1.0f, -1.0f, 0.0f);
    FVector v2_local = FVector(-1.0f, -1.0f, 0.0f);

    // �� ��ȯ ��� ���� (������ -> ȸ�� -> �̵� ����)
    FMatrix Scaling = FMatrix::Scaling(RelativeScale3D.X, RelativeScale3D.Y, RelativeScale3D.Z);
    FMatrix Rotation = FMatrix::CreateRotationRollPitchYaw(RelativeRotation.X, RelativeRotation.Y, RelativeRotation.Z);
    FMatrix Translation = FMatrix::Translation(RelativeLocation.X, RelativeLocation.Y, RelativeLocation.Z);
    FMatrix ModelMatrix = Scaling * Rotation * Translation;

    // ���� �������� ��ȯ�� �ﰢ�� ������
    FVector v0_world = ModelMatrix * v0_local;
    FVector v1_world = ModelMatrix * v1_local;
    FVector v2_world = ModelMatrix * v2_local;

    triangle3 tri;
    tri.a = v0_world;
    tri.b = v1_world;
    tri.c = v2_world;

    // ���� �˻縦 �����մϴ�.
    FVector hitPoint;
    if (ray_intersects_triangle(RayOrigin, RayDirection, tri, hitPoint))
    {
        OutHitResult.bHit = true;
        OutHitResult.HitLocation = hitPoint;
        OutHitResult.Distance = (hitPoint - RayOrigin).Length();
        OutHitResult.HitObject = this;
        return true;
    }
    else
    {
        return false;
    }
}

void UTriangleComponent::Initialize()
{
    NumVertices = sizeof(triangle_vertices) / sizeof(FVertexType);
    VertexBuffer = Renderer->CreateVertexBuffer(triangle_vertices, sizeof(triangle_vertices));
}