// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Task_TurnInPlace.generated.h"

/**
 * ���ڸ����� ȸ�� Task -> AnimInstance�� �̿��� ȸ��
 */
UCLASS()
class LADYBUG_API UTask_TurnInPlace : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_TurnInPlace();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere)
		struct FBlackboardKeySelector BlackBoardKey;

	UPROPERTY()
		class ABaseCharacter* owner;
	UPROPERTY()
		class ABaseCharacter* target;

	UPROPERTY(EditAnywhere)
		float allowableAngle = 0.f;			// ��밡���� Ÿ�ٰ��� ����
	UPROPERTY(EditAnywhere)
		float turnSpeed;					// ȸ�� ���� �ӵ�
public:
	FName GetSelectedBlackBoardKey() { return BlackBoardKey.SelectedKeyName; }
};
