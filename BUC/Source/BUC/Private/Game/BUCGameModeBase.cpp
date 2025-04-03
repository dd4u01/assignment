#include "Game/BUCGameModeBase.h"
#include "Player/BUCPlayerController.h"
#include "EngineUtils.h"
#include "Player/BUCPlayerState.h"

FString ABUCGameModeBase::GenerateSecretNumber()
{

	TArray<int32> Numbers;

	/*
	  랜덤 숫자 채택
	  1. 1~9까지의 숫자가 들어있는 배열 생성
	  2. 무작위 숫자 채택.
		 1) i ~ 배열의 끝까지 중 무작위로 인덱스를 하나 선택해 i번째와 스왑.
		 2) 스왑 후 i의 값에 +1
		 3) 정답 갯수만큼 반복

	  3. n개의 숫자를 정답으로 저장
	 */

	 // 1~9 사이 숫자 추가
	for (int32 i = 1; i < 10; i++)
	{
		Numbers.Add(i);
	}

	for (int32 i = 0; i < 3; ++i)
	{
		int32 RandomIndex = FMath::RandRange(i, Numbers.Num() - 1);
		Numbers.Swap(i, RandomIndex);
	}

	FString Results;
	// Answer에 처음 3개 저장 (키: 숫자, 값: 위치)
	Results.Empty();
	FString Log;
	for (int32 i = 0; i < 3; i++)
	{
		int32 Index = FMath::RandRange(0, Numbers.Num() - 1);
		Results.Append(FString::FromInt(Numbers[Index]));
		Log += FString::FromInt(Numbers[i]);
	}

	// 디버깅용 정답 프린트
	UE_LOG(LogTemp, Warning, TEXT("정답은 %s 입니다."), *Log);

	return Results;
}

bool ABUCGameModeBase::IsGuessNumberString(const FString& InNumberString)
{
	bool bCanPlay = false;

	do {

		if (InNumberString.Len() != 3)
		{
			break;
		}

		bool bIsUnique = true;
		TSet<TCHAR> UniqueDigits;
		for (TCHAR C : InNumberString)
		{
			if (FChar::IsDigit(C) == false || C == '0')
			{
				bIsUnique = false;
				break;
			}

			UniqueDigits.Add(C);
		}

		if (bIsUnique == false)
		{
			break;
		}

		bCanPlay = true;

	} while (false);

	return bCanPlay;
}

FString ABUCGameModeBase::JudgeResult(const FString& InSecretNumberString, const FString& InGuessNumberString)
{
	int32 StrikeCount = 0, BallCount = 0;

	for (int32 i = 0; i < 3; ++i)
	{
		if (InSecretNumberString[i] == InGuessNumberString[i])
		{
			StrikeCount++;
		}
		else
		{
			FString PlayerGuessChar = FString::Printf(TEXT("%c"), InGuessNumberString[i]);
			if (InSecretNumberString.Contains(PlayerGuessChar))
			{
				BallCount++;
			}
		}
	}

	if (StrikeCount == 0 && BallCount == 0)
	{
		return TEXT("OUT");
	}

	return FString::Printf(TEXT("%dS%dB"), StrikeCount, BallCount);
}

void ABUCGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SecretNumberString = GenerateSecretNumber();
}

void ABUCGameModeBase::PrintChatMessageString(ABUCPlayerController* InChattingPlayerController, const FString& InChatMessageString)
{
	FString ChatMessageString = InChatMessageString;
	int Index = InChatMessageString.Len() - 3;
	FString GuessNumberString = InChatMessageString.RightChop(Index);
	if (IsGuessNumberString(GuessNumberString) == true)
	{
		FString JudgeResultString = JudgeResult(SecretNumberString, GuessNumberString);
		for (TActorIterator<ABUCPlayerController> It(GetWorld()); It; ++It)
		{
			ABUCPlayerController* BUCPlayerController = *It;
			if (IsValid(BUCPlayerController) == true)
			{
				FString CombinedMessageString = InChatMessageString + TEXT(" -> ") + JudgeResultString;
				BUCPlayerController->ClientRPCPrintChatMessageString(CombinedMessageString);

				int32 StrikeCount = FCString::Atoi(*JudgeResultString.Left(1));
				JudgeGame(InChattingPlayerController, StrikeCount);
			}
		}

		IncreaseGuessCount(InChattingPlayerController);
	}
	else
	{
		for (TActorIterator<ABUCPlayerController> It(GetWorld()); It; ++It)
		{
			ABUCPlayerController* BUCPlayerController = *It;
			if (IsValid(BUCPlayerController) == true)
			{
				BUCPlayerController->ClientRPCPrintChatMessageString(InChatMessageString);
			}
		}
	}
}

void ABUCGameModeBase::IncreaseGuessCount(ABUCPlayerController* InChattingPlayerController)
{
	ABUCPlayerState* BUCPS = InChattingPlayerController->GetPlayerState<ABUCPlayerState>();
	if (IsValid(BUCPS) == true)
	{
		BUCPS->CurrentGuessCount++;
	}
}

void ABUCGameModeBase::ResetGame()
{
	SecretNumberString = GenerateSecretNumber();

	for (const auto& CXPlayerController : AllPlayerControllers)
	{
		ABUCPlayerState* BUCPS = CXPlayerController->GetPlayerState<ABUCPlayerState>();
		if (IsValid(BUCPS) == true)
		{
			BUCPS->CurrentGuessCount = 0;
		}
	}
}

void ABUCGameModeBase::JudgeGame(ABUCPlayerController* InChattingPlayerController, int InStrikeCount)
{
	if (3 == InStrikeCount)
	{
		ABUCPlayerState* BUCPS = InChattingPlayerController->GetPlayerState<ABUCPlayerState>();
		for (const auto& BUCPlayerController : AllPlayerControllers)
		{
			if (IsValid(BUCPS) == true)
			{
				FString CombinedMessageString = BUCPS->PlayerNameString + TEXT(" has won the game.");
				BUCPlayerController->NotificationText = FText::FromString(CombinedMessageString);

				ResetGame();
			}
		}
	}
	else
	{
		bool bIsDraw = true;
		for (const auto& BUCPlayerController : AllPlayerControllers)
		{
			ABUCPlayerState* BUCPS = BUCPlayerController->GetPlayerState<ABUCPlayerState>();
			if (IsValid(BUCPS) == true)
			{
				if (BUCPS->CurrentGuessCount < BUCPS->MaxGuessCount)
				{
					bIsDraw = false;
					break;
				}
			}
		}

		if (true == bIsDraw)
		{
			for (const auto& BUCPlayerController : AllPlayerControllers)
			{
				BUCPlayerController->NotificationText = FText::FromString(TEXT("Draw..."));

				ResetGame();
			}
		}
	}
}
