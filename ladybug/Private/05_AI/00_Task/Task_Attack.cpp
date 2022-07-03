// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_Attack.h"
#include "00_Character/BaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"

UTask_Attack::UTask_Attack()
{
	bNotifyTick = true;
	NodeName = "NormalAttack";
}
EBTNodeResult::Type UTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	owner = OwnerComp.GetAIOwner()->GetPawn<ABaseCharacter>();
	if (owner == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	owner->GetMesh()->GetAnimInstance()->Montage_Play(owner->GetAttackMontage());
	owner->SetAttackState(EAttackState::COOLTIME);

	return EBTNodeResult::InProgress;
}
void UTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!owner->GetMesh()->GetAnimInstance()->Montage_IsPlaying(owner->GetAttackMontage()))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
