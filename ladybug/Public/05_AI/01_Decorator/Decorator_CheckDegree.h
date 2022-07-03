// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Decorator_CheckDegree.generated.h"

/**
 * 타겟과의 각도를 구한다.
 */
UCLASS()
class LADYBUG_API UDecorator_CheckDegree : public UBTDecorator
{
	GENERATED_BODY()
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual FString GetStaticDescription() const override;
protected:
	UPROPERTY(EditAnywhere)
		struct FBlackboardKeySelector BlackBoardKey;
	UPROPERTY(EditAnywhere)
		float attackRange;		// 공격범위(각도)

public:
	FName GetSelectedBlackboardKey() const;
};
