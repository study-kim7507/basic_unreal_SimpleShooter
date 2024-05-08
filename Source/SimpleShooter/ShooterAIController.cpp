// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		GetBlackboardComponent()->SetValueAsVector(TEXT("Start Location"), GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*
	// C++���� ������ ���� AI�� ������ �����̺�� Ʈ������ ���� -> Ŀ���� �½�ũ, Ŀ���� ����
	if (PlayerPawn != nullptr)
	{
		if (LineOfSightTo(PlayerPawn))
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerPawn Location"), PlayerPawn->GetActorLocation());
			GetBlackboardComponent()->SetValueAsVector(TEXT("LastPlayerPawn Location"), PlayerPawn->GetActorLocation());
			// SetFocus(PlayerPawn);
			// MoveToActor(PlayerPawn, AcceptanceRadius);
		}
		else
		{
			// ClearValue�� ���ؼ� �����̺�� Ʈ���� ���ڷ����Ϳ��� ���и� ��ȯ�ϸ�
			// LastPlayerPawn Location���� �̵��ϵ���.
			GetBlackboardComponent()->ClearValue(TEXT("PlayerPawn Location"));
			// ClearFocus(EAIFocusPriority::Gameplay);
			// StopMovement();
		}
	}
	*/
}

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}

	// ���� ������ ��Ʈ�ѷ��� ������ �� ������ ���������� ��Ʈ�ѷ��� �����ų� ��������
	return true;
}