// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "02_Item/ItemTypes.h"

#include "Task_SwapWeapon.generated.h"

/**
 * 무기를 스왑하는 Task
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
		EAttackType attackTypeToSwap;	// 어떤 무기타입으로 스왑할 것인지(근거리, 원거리)
};
