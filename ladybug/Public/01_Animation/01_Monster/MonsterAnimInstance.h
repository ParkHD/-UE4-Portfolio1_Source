// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "00_Character/BaseCharacter.h"
#include "MonsterAnimInstance.generated.h"

// AI의 BattleCharacter의 AnimInstance
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
		float moveSpeed;		// 이동 속도
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		float moveDir;			// 이동 방향

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		ETurnDir turnDir;		// 회전 방향

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		TEnumAsByte<EMovementMode> characterState;	// 캐릭터의 MoveMode : fly구분

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		EActionState actionState;	// 캐릭터의 ActionState
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		EAttackState attackState;	// 캐릭터의 AttackState
};
