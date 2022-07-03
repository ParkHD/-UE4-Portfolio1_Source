// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "00_Character/BaseCharacter.h"
#include "Task_SetActionState.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UTask_SetActionState : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bRand == false"))
		EActionState AIActionState;
	UPROPERTY(EditAnywhere)
		bool bRand = false;
};
