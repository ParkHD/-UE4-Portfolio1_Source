// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "00_Character/00_Player/PlayerCharacter.h"

#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
 // 에디터에서 조작가능
UENUM(BlueprintType)
enum class EDir : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	FORWARD,
	DOWN,	
	LEFT,	
	RIGHT	
};

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
		float playerSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float moveDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool isJumping = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float playerTurn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		EActionState ActionState = EActionState::NORMAL;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		EAttackState AttackState = EAttackState::READY;
};
