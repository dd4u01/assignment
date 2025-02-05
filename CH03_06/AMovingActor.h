// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AMovingActor.generated.h"

UCLASS()
class SPARTAPROJECT1_API AAMovingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAMovingActor();

protected:
	
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Item|Components")
	USceneComponent* SceneRoot;

	UPROPERTY(EditAnyWhere, BluePrintReadWrite, Category = "Item|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Moving Actor")
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Moving Actor")
	FVector MoveDirection;  // ex) (1, 0, 0) , (0, 1, 0)

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Moving Actor")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Moving Actor")
	float MaxRange;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	/*UFUNCTION(BluePrintCallable, Category = "AMovingActor|Actions")
	void ResetActorPosition();*/

};
