// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_SearchTarget.generated.h"

/**
 * 전투에서 현재 자신을 기준으로 가장 가까이에 있는 적 탐색 Task
 */
UCLASS()
class LADYBUG_API UTask_SearchTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_SearchTarget();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

};
