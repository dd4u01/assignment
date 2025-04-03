#include "Player/BUCPlayerController.h"
#include "UI/BUCUserInput.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Game/BUCGameModeBase.h"
#include "Net/UnrealNetwork.h"
#include "Player/BUCPlayerState.h"

ABUCPlayerController::ABUCPlayerController()
{
	bReplicates = true;
}

void ABUCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 클라이언트(플레이어)에 따른 UI 중복 호출 방지
	// Owning Client 판별을 위해 isLocalController() 함수 호출
	if (IsLocalController() == false)
	{
		return;
	}

	FInputModeUIOnly InputModeUIOnly;
	SetInputMode(InputModeUIOnly);

	if (IsValid(UserInputWidgetClass) == true)
	{
		UserInputWidgetInstance = CreateWidget<UBUCUserInput>(this, UserInputWidgetClass);
		if (IsValid(UserInputWidgetInstance) == true)
		{
			UserInputWidgetInstance->AddToViewport();
		}
	}

	if (IsValid(NotificationTextWidgetClass) == true)
	{
		NotificationTextWidgetInstance = CreateWidget<UUserWidget>(this, NotificationTextWidgetClass);
		if (IsValid(NotificationTextWidgetInstance) == true)
		{
			NotificationTextWidgetInstance->AddToViewport();
		}
	}
}

void ABUCPlayerController::SetChatMessageString(const FString& InChatMessageString)
{
	ChatMessageString = InChatMessageString;

	if (IsLocalController() == true)
	{
		ABUCPlayerState* BUCPS = GetPlayerState<ABUCPlayerState>();
		if (IsValid(BUCPS) == true)
		{
			FString CombinedMessageString = BUCPS->GetPlayerInfoString() + TEXT(": ") + InChatMessageString;

			ServerRPCPrintChatMessageString(CombinedMessageString);
		}
	}
}

void ABUCPlayerController::PrintChatMessageString(const FString& InChatMessageString)
{
	UKismetSystemLibrary::PrintString(this, ChatMessageString, true, true, FLinearColor::Red, 5.0f);
}

void ABUCPlayerController::ClientRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{
	PrintChatMessageString(InChatMessageString);
}

void ABUCPlayerController::ServerRPCPrintChatMessageString_Implementation(const FString& InChatMessageString)
{

	AGameModeBase* GM = UGameplayStatics::GetGameMode(this);
	if (IsValid(GM) == true)
	{
		ABUCGameModeBase* BUCGM = Cast<ABUCGameModeBase>(GM);
		if (IsValid(BUCGM) == true)
		{
			BUCGM->PrintChatMessageString(this, InChatMessageString);
		}
	}
}

void ABUCPlayerController::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, NotificationText);
}