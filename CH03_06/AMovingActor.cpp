#include "AMovingActor.h"

AAMovingActor::AAMovingActor()
{
    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;

    // 기본값 초기화
    MoveSpeed = 10.0f;
    MaxRange = 50.0f;
    MoveDirection = FVector(1.0f, 0.0f, 0.0f);
}

void AAMovingActor::BeginPlay()
{
	Super::BeginPlay();

    // 시작 위치를 현재 위치로 저장
    StartLocation = GetActorLocation();
}

void AAMovingActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FVector CurrentLocation = GetActorLocation();
    FVector DeltaMove = MoveDirection * MoveSpeed * DeltaTime;
    FVector TentativeLocation = CurrentLocation + DeltaMove;

    // 시작 위치로부터의 벡터와 거리 계산
    FVector FromStart = TentativeLocation - StartLocation;
    float DistanceFromStart = FromStart.Size();

    // 만약 이동 후 위치가 최대 범위를 초과할 때 (오버슈팅 해결)
    if (DistanceFromStart >= MaxRange)
    {
        // 시작 위치로부터 방향 벡터의 정규화된 값에 최대 범위를 곱해 경계 위치를 계산
        TentativeLocation = StartLocation + FromStart.GetSafeNormal() * MaxRange;
        // 이동 방향 반전
        MoveDirection *= -1;
    }

    SetActorLocation(TentativeLocation);
}