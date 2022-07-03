// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "00_Character/BaseCharacter.h"

#include "MonsterAnimInstance.generated.h"

/**
 * 
 */



UCLASS()
class LADYBUG_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	class AMonsterBaseCharacter* owner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	float moveSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
	float moveDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		ETurnDir turnDir;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		TEnumAsByte<EMovementMode> characterState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		EActionState actionState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		EAttackState attackState;
};
