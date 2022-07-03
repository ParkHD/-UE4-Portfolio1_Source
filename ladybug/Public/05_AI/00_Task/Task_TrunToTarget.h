// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "Task_TrunToTarget.generated.h"

/**
 * ����� �̻�� -> Task_TurnToTarget���� ���׷��̵�
 * Ÿ�� �������� ���� ȸ���ϴ� Task
 */
UCLASS()
class LADYBUG_API UTask_TrunToTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTask_TrunToTarget();
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
protected:
	UPROPERTY(EditAnywhere)
	struct FBlackboardKeySelector BlackBoardKey;	// �Է¹��� ������ ��

	UPROPERTY()
		class ABaseCharacter* owner;
	UPROPERTY()
	class ABaseCharacter* target;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* leftTurnAnim;				// �������� ȸ���ϴ� �ִϸ��̼�
	UPROPERTY(EditAnywhere)
	class UAnimMontage* rightTurnAnim;				// ���������� ȸ���ϴ� �ִϸ��̼�


	UPROPERTY(EditAnywhere)
		bool isInPlace = false;					// ��ġ�� �����Ǹ鼭 ȸ�� �Ұ��ΰ�?
	UPROPERTY(EditAnywhere)
		float lerpSpeed = 5.f;					// ȸ�� ���� �ӵ�
	UPROPERTY(EditAnywhere)
		float allowableAngle = 5.f;				// Ÿ�ٰ��� ���� ���� ��� ����
	
	UPROPERTY(EditAnywhere)
		float angleForPlayMontage = 60.f;		// ��Ÿ�ָ� �̿��Ͽ� Turn�� ���� ��(Ÿ�ٰ��� ������ �󸶳� ���̳��� ��Ÿ�ָ� ������ ���ΰ�)

	bool isTick = false;
public:
	FName GetSelectedBlackBoardKey() const;

	void Turn();	// ��Ÿ�ָ� �̿��� ȸ���Լ�
};
