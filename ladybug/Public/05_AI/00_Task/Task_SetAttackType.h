// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "02_Item/ItemTypes.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_SetAttackType.generated.h"

/**
 * AttackType(Melee, Range) 변경하는 Task -> 무기스왑에 사용
 */
UCLASS()
class LADYBUG_API UTask_SetAttackType : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere)
		EAttackType AttackState;
};
