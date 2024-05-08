// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"


void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD = CreateWidget(this, HUDClass);
	if (HUD != nullptr)
	{
		HUD->AddToViewport();
	}
}

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	// BP_ShooterPlayerController에서 LoseScreenClass로 WBP_LoseScreen을 선택 (None일 경우 nullptr을 반환.)
	// LoseScreenClass를 UUserWidget으로 만들고 해당 객체의 주소를 반환
	// AddToViewport 함수를 통해 AShooterPlayerController의 뷰포트에 해당 화면을 띄운다.
	
	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen != nullptr)
		{
			HUD->RemoveFromViewport();
			WinScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen != nullptr)
		{
			HUD->RemoveFromViewport();
			LoseScreen->AddToViewport();
		}
	}
	
	

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);
	UE_LOG(LogTemp, Warning, TEXT("Game Ended!"));
}