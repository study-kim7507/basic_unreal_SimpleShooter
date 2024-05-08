// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		// ���� ���� ĳ���Ͱ� PlayerController�� ������ ĳ���Ͷ��, �й��� ����.
		EndGame(false);
	}

	// PawnKilled�� ȣ��Ǿ��� ��, ���� ���� ��� AShooterAIController�� IsDead�Լ��� ���ؼ�
	// ��Ʈ�ѷ��� Posses�� ĳ���Ͱ� �׾����� Ȯ��.
	
	for (AShooterAIController* AIController : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!AIController->IsDead())
		{
			// �ϳ��� ���� ���� ĳ���Ͱ� ������, ������ ������ �ȵ�.
			return;
		}
	}

	// ���� ���� ĳ���Ͱ� PlayerController�� Posses�� ĳ���Ͱ� �ƴϰ�,
	// ��� AShooterAIController�� ������ ĳ���Ͱ� �׾��ٸ� ������ �÷��̾ �̱�ɷ� ������.
	EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		// bIsPlayerWinner�� false�� ���, AI���� �й��� ���̹Ƿ� bIsWinner�� false�� �� ����.
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}