#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BUCPlayerController.generated.h"

class UBUCUserInput;
class UUserWidget;

UCLASS()
class BUC_API ABUCPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ABUCPlayerController();

	virtual void BeginPlay() override;

	void SetChatMessageString(const FString& InChatMessageString);

	void PrintChatMessageString(const FString& InChatMessageString);

	UFUNCTION(Client, Reliable)
	void ClientRPCPrintChatMessageString(const FString& InChatMessageString);

	UFUNCTION(Server, Reliable)
	void ServerRPCPrintChatMessageString(const FString& InChatMessageString);

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(Replicated, BlueprintReadOnly)
	FText NotificationText;

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBUCUserInput> UserInputWidgetClass;

	UPROPERTY()
	TObjectPtr<UBUCUserInput> UserInputWidgetInstance;

	FString ChatMessageString;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> NotificationTextWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> NotificationTextWidgetInstance;
};
