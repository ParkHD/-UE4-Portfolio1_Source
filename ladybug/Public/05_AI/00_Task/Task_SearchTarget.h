// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_SearchTarget.generated.h"

/**
 * �������� ���� �ڽ��� �������� ���� �����̿� �ִ� �� Ž�� Task
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
