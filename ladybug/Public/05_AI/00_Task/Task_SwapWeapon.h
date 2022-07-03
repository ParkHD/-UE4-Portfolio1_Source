// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "02_Item/ItemTypes.h"

#include "Task_SwapWeapon.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UTask_SwapWeapon : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_SwapWeapon();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;
protected:
	UPROPERTY(EditAnywhere)
		EAttackType attackTypeToSwap;
};
