// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WorldMonsterAnimInstance.generated.h"

// AI's WorldCharacter's AnimInstance
UCLASS()
class LADYBUG_API UWorldMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	virtual void NativeInitializeAnimation()override;
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;

protected:
	UPROPERTY()
		class AWorldBaseCharacter* owner;	// owner

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float Speed;		// 이동 속도
};
