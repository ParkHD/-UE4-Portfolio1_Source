// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "00_Character/00_Player/PlayerCharacter.h"

#include "PlayerAnimInstance.generated.h"

// �̵�����
UENUM(BlueprintType)
enum class EDir : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	FORWARD,	// ��	
	DOWN,		// ��
	LEFT,		// ����
	RIGHT		// ������
};

// Player�� BattleCharacter�� AnimInstance
UCLASS()
class LADYBUG_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnimInstance();

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
		class APlayerCharacter* player;
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float playerSpeed;			// �ӷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float moveDirection;		// �̵�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool isJumping = false;		// ���� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float playerTurn;			// ȸ������

	// Ȱ ����� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		EActionState ActionState = EActionState::NORMAL;	// ĳ������ ActionState
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		EAttackState AttackState = EAttackState::READY;		// ĳ������ AttackState
};
