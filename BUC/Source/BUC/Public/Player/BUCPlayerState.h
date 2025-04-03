#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BUCPlayerState.generated.h"

UCLASS()
class BUC_API ABUCPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated)
	FString PlayerNameString;

	ABUCPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	// 정답 시도 횟수 관리용
	UPROPERTY(Replicated)
	int32 CurrentGuessCount;
	UPROPERTY(Replicated)
	int32 MaxGuessCount;

	FString GetPlayerInfoString();
};
