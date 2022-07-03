// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Decorator_CheckDistance.generated.h"

/**
 * 타겟과의 거리 계산
 */
UCLASS()
class LADYBUG_API UDecorator_CheckDistance : public UBTDecorator
{
	GENERATED_BODY()
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	virtual FString GetStaticDescription() const override;
protected:
	UPROPERTY(EditAnywhere)
	struct FBlackboardKeySelector BlackBoardKey;
	UPROPERTY(EditAnywhere)
	float attackRange;			// 허용 거리

public:
	FName GetSelectedBlackboardKey() const;
};
