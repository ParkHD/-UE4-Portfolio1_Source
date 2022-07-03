// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "00_Character/BaseCharacter.h"
#include "MonsterAnimInstance.generated.h"

// AI�� BattleCharacter�� AnimInstance
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
		float moveSpeed;		// �̵� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		float moveDir;			// �̵� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		ETurnDir turnDir;		// ȸ�� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		TEnumAsByte<EMovementMode> characterState;	// ĳ������ MoveMode : fly����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		EActionState actionState;	// ĳ������ ActionState
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn)
		EAttackState attackState;	// ĳ������ AttackState
};
