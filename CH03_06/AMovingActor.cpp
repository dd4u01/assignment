#include "AMovingActor.h"

AAMovingActor::AAMovingActor()
{
    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;

    // �⺻�� �ʱ�ȭ
    MoveSpeed = 10.0f;
    MaxRange = 50.0f;
    MoveDirection = FVector(1.0f, 0.0f, 0.0f);
}

void AAMovingActor::BeginPlay()
{
	Super::BeginPlay();

    // ���� ��ġ�� ���� ��ġ�� ����
    StartLocation = GetActorLocation();
}

void AAMovingActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector CurrentLocation = GetActorLocation();
    FVector DeltaMove = MoveDirection * MoveSpeed * DeltaTime;
    FVector TentativeLocation = CurrentLocation + DeltaMove;

    // ���� ��ġ�κ����� ���Ϳ� �Ÿ� ���
    FVector FromStart = TentativeLocation - StartLocation;
    float DistanceFromStart = FromStart.Size();

    // ���� �̵� �� ��ġ�� �ִ� ������ �ʰ��� �� (�������� �ذ�)
    if (DistanceFromStart >= MaxRange)
    {
        // ���� ��ġ�κ��� ���� ������ ����ȭ�� ���� �ִ� ������ ���� ��� ��ġ�� ���
        TentativeLocation = StartLocation + FromStart.GetSafeNormal() * MaxRange;
        // �̵� ���� ����
        MoveDirection *= -1;
    }

    SetActorLocation(TentativeLocation);
}