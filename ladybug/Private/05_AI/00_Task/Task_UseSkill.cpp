// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/00_Task/Task_UseSkill.h"
#include "00_Character/BaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"
#include "00_Character/02_Component/SkillComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTask_UseSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	ABaseCharacter* owner = Cast<ABaseCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (owner != nullptr)
	{
		// 사용할 스킬 랜덤하게 구하고 스킬 사용
		if(bRand)
		{
			int32 index = FMath::RandRange(0, skillTags.Num() - 1);
			owner->GetSkillComponent()->UseSkill(skillTags.GetByIndex(index));
			return EBTNodeResult::Succeeded;
		}
		else
		{
			// 지정한 스킬 사용
			if (owner->GetSkillComponent()->IsContainSkill(skillTag))
			{
				owner->GetSkillComponent()->UseSkill(skillTag);

				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}