// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_Block.h"
#include "00_Character/BaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"

UTask_Block::UTask_Block()
{
	bNotifyTick = true;
	NodeName = "Block";
}
EBTNodeResult::Type UTask_Block::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	owner = OwnerComp.GetAIOwner()->GetPawn<ABaseCharacter>();
	if (owner == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	owner->SetActionState(EActionState::BLOCK);

	if (bRandom)
	{
		blockTime = FMath::FRandRange(1.f, 4.f);
	}
	time = 0.f;

	return EBTNodeResult::InProgress;
}
void UTask_Block::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	time += DeltaSeconds;
	UE_LOG(LogTemp, Log, TEXT("%f"), time);
	if (time >= blockTime)
	{
		owner->SetActionState(EActionState::NORMAL);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}

}