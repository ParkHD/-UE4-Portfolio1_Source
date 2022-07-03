// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/BaseCharacter.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_SetAttackState.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UTask_SetAttackState : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bRand == false"))
		EAttackState AIAttackState;

};
