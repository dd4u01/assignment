// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatingActor.h"

ARotatingActor::ARotatingActor()
{
    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMeshComp->SetupAttachment(SceneRoot);

    PrimaryActorTick.bCanEverTick = true;
    RotationSpeed = 10.0f;

}

void ARotatingActor::BeginPlay()
{
	Super::BeginPlay();
	
    SetActorRotation(FRotator(0.0f, 90.0f, 0.0f));
}

void ARotatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!FMath::IsNearlyZero(RotationSpeed))
    {
        AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
    }
}

void ARotatingActor::ResetActorPosition()
{
    SetActorLocation(FVector::ZeroVector);
}

float ARotatingActor::GetRotationSpeed() const
{
    return RotationSpeed;
}