// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_Block.generated.h"

/*
 * 방어하는 Task 
 */
UCLASS()
class LADYBUG_API UTask_Block : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_Block();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)override;
protected:
	class ABaseCharacter* owner;

	UPROPERTY(EditAnywhere)
		bool bRandom = false;		// 방어를 유지하는 시간을 랜덤으로 할것인가?
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bRandom == false"))
		float blockTime = 0.f;		// 방어를 유지하는 시간

	float time = 0.f;	// 타이머 계산
};
