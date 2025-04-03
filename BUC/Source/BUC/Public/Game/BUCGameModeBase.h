#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BUCGameModeBase.generated.h"

class ABUCPlayerController;

UCLASS()
class BUC_API ABUCGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	// 난수 생성
	FString GenerateSecretNumber();

	bool IsGuessNumberString(const FString& InNumberString);

	FString JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString);

	virtual void BeginPlay() override;

	void PrintChatMessageString(ABUCPlayerController* InChattingPlayerController, const FString& InChatMessageString);

	// 정답 시도 횟수
	void IncreaseGuessCount(ABUCPlayerController* InChattingPlayerController);

	void ResetGame();

	void JudgeGame(ABUCPlayerController* InChattingPlayerController, int InStrikeCount);

protected:
	FString SecretNumberString;

	TArray<TObjectPtr<ABUCPlayerController>> AllPlayerControllers;
};
