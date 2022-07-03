// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "Task_TrunToTarget.generated.h"

/**
 * 
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
	struct FBlackboardKeySelector BlackBoardKey;

	UPROPERTY()
		class ABaseCharacter* owner;
	UPROPERTY()
	class ABaseCharacter* target;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* leftTurnAnim;
	UPROPERTY(EditAnywhere)
	class UAnimMontage* rightTurnAnim;


	UPROPERTY(EditAnywhere)
		bool isInPlace = false;
	UPROPERTY(EditAnywhere)
	float lerpSpeed = 5.f;
	UPROPERTY(EditAnywhere)
	float allowableAngle = 5.f;

	// 몽타주를 이용하여 Turn할 기준 값
	UPROPERTY(EditAnywhere)
	float angleForPlayMontage = 60.f;

	bool isTick = false;
public:
	FName GetSelectedBlackBoardKey() const;

	void Turn();
};
