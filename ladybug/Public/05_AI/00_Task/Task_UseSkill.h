// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GameplayTagContainer.h"

#include "Task_UseSkill.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UTask_UseSkill : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
protected:
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector BlackboardKey;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bRand == false"))
		FGameplayTag skillTag;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bRand == true"))
		FGameplayTagContainer skillTags;
	UPROPERTY(EditAnywhere)
		bool bRand;
public:
	FName GetBlackboardSelectedKeyName() { return BlackboardKey.SelectedKeyName; }
};
