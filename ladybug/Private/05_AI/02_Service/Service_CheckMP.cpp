// Fill out your copyright notice in the Description page of Project Settings.


#include "05_AI/02_Service/Service_CheckMP.h"
#include "10_WorldCharacter/01_Monster/WorldMonsterCharacter.h"
#include "10_WorldCharacter/01_Monster/WorldMonAIController.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
UService_CheckMP::UService_CheckMP()
{
	bNotifyTick = true;
}


void UService_CheckMP::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	auto target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(Target.SelectedKeyName);

	if (target != nullptr)
	{
		if (OwnerComp.GetAIOwner()->GetPawn()->IsA<AMonsterBaseCharacter>())
		{

			auto worldOwner = OwnerComp.GetAIOwner()->GetPawn<AMonsterBaseCharacter>();
			if (worldOwner != nullptr)
			{
				//OwnerComp.GetBlackboardComponent()->SetValueAsFloat("MP", distance);
			}
		}
	}
}