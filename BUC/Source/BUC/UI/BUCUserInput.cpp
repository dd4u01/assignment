#include "UI/BUCUserInput.h"
#include "Components/EditableTextBox.h"
#include "Player/BUCPlayerController.h"

void UBUCUserInput::NativeConstruct()
{
	Super::NativeConstruct();

	if (EditableTextBox_UserInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == false)
	{
		EditableTextBox_UserInput->OnTextCommitted.AddDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UBUCUserInput::NativeDestruct()
{
	Super::NativeDestruct();

	if (EditableTextBox_UserInput->OnTextCommitted.IsAlreadyBound(this, &ThisClass::OnChatInputTextCommitted) == true)
	{
		EditableTextBox_UserInput->OnTextCommitted.RemoveDynamic(this, &ThisClass::OnChatInputTextCommitted);
	}
}

void UBUCUserInput::OnChatInputTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter)
	{
		APlayerController* OwningPlayerController = GetOwningPlayer();
		if (IsValid(OwningPlayerController) == true)
		{
			ABUCPlayerController* OwningCXPlayerController = Cast<ABUCPlayerController>(OwningPlayerController);
			if (IsValid(OwningCXPlayerController) == true)
			{
				OwningCXPlayerController->SetChatMessageString(Text.ToString());

				EditableTextBox_UserInput->SetText(FText());
			}
		}
	}
}