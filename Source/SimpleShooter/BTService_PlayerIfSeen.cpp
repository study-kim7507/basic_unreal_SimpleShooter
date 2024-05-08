// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"

// ������
UBTService_PlayerIfSeen::UBTService_PlayerIfSeen()
{
	NodeName = TEXT("Update Player If Seen");
}

void UBTService_PlayerIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn == nullptr) return;

	// AI Pawn�� ������ AIController�� ��ȯ
	if (OwnerComp.GetAIOwner() == nullptr) return;
	
	if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	}
}