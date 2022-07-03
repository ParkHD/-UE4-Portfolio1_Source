// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_TagetOff.generated.h"

/**
 * 블랙보드 값인 Target값 및 Target과의 거리값을 초기화한다.
 */
UCLASS()
class LADYBUG_API UTask_TagetOff : public UBTTaskNode
{
	GENERATED_BODY()

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
