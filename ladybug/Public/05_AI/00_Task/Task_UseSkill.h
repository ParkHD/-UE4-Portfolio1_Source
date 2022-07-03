// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "GameplayTagContainer.h"

#include "Task_UseSkill.generated.h"

/**
 * 스킬을 Random또는 지정한 스킬 사용하는 Task
 */
UCLASS()
class LADYBUG_API UTask_UseSkill : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
protected:
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector BlackboardKey;			// 스킬을 사용할 대상

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bRand == false"))
		FGameplayTag skillTag;				// 지정해서 사용할 스킬
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bRand == true"))
		FGameplayTagContainer skillTags;	// 랜덤하게 사용할 스킬List
	UPROPERTY(EditAnywhere)
		bool bRand;							// 스킬을 랜덤하게 사용할 것인가?
public:
	FName GetBlackboardSelectedKeyName() { return BlackboardKey.SelectedKeyName; }
};
