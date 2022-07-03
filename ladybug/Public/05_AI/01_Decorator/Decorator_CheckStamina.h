// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Decorator_CheckStamina.generated.h"

/**
 * 스태미너가 충분히 있는지 확인
 */
UCLASS()
class LADYBUG_API UDecorator_CheckStamina : public UBTDecorator
{
	GENERATED_BODY()
public:
	UDecorator_CheckStamina();
protected:
	UPROPERTY(EditAnywhere)
		FBlackboardKeySelector BlackBoardKey;

	// 비교할 스태미너 양
	UPROPERTY(EditAnywhere)
		float stamina = 0.f;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
public:
	FName GetSelectedBlackBoardKey() const { return BlackBoardKey.SelectedKeyName; }
};
