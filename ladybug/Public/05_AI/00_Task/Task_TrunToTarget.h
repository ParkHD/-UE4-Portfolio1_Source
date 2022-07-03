// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "Task_TrunToTarget.generated.h"

/**
 * 현재는 미사용 -> Task_TurnToTarget으로 업그레이드
 * 타겟 방향으로 몸을 회전하는 Task
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
	struct FBlackboardKeySelector BlackBoardKey;	// 입력받을 블랙보드 값

	UPROPERTY()
		class ABaseCharacter* owner;
	UPROPERTY()
	class ABaseCharacter* target;

	UPROPERTY(EditAnywhere)
	class UAnimMontage* leftTurnAnim;				// 왼쪽으로 회전하는 애니메이션
	UPROPERTY(EditAnywhere)
	class UAnimMontage* rightTurnAnim;				// 오른쪽으로 회전하는 애니메이션


	UPROPERTY(EditAnywhere)
		bool isInPlace = false;					// 위치는 고정되면서 회전 할것인가?
	UPROPERTY(EditAnywhere)
		float lerpSpeed = 5.f;					// 회전 보간 속도
	UPROPERTY(EditAnywhere)
		float allowableAngle = 5.f;				// 타겟과의 각도 오차 허용 범위
	
	UPROPERTY(EditAnywhere)
		float angleForPlayMontage = 60.f;		// 몽타주를 이용하여 Turn할 기준 값(타겟과의 각도가 얼마나 차이나면 몽타주를 실핼할 것인가)

	bool isTick = false;
public:
	FName GetSelectedBlackBoardKey() const;

	void Turn();	// 몽타주를 이용한 회전함수
};
