// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ComboAttackNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UComboAttackNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UComboAttackNotifyState();
protected:
	virtual void BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload) override;
	virtual void BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime) override;
	virtual void BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload) override;
protected:
	class APlayerCharacter* owner;
	UPROPERTY(EditAnywhere)
		FName sectionName;

};
