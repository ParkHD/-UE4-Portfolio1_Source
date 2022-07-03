// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "WorldPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UWorldPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
protected:
	virtual void NativeInitializeAnimation()override;
	virtual void NativeUpdateAnimation(float DeltaSeconds)override;


protected:
	UPROPERTY()
		class AWorldBaseCharacter* owner;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float playerSpeed;
};
