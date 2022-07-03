// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "00_Character/00_Player/PlayerCharacter.h"

#include "PlayerAnimInstance.generated.h"

// 이동방향
UENUM(BlueprintType)
enum class EDir : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	FORWARD,	// 앞	
	DOWN,		// 뒤
	LEFT,		// 왼쪽
	RIGHT		// 오른쪽
};

// Player의 BattleCharacter의 AnimInstance
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
		float playerSpeed;			// 속력
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float moveDirection;		// 이동방향
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		bool isJumping = false;		// 점프 중인지
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		float playerTurn;			// 회전방향

	// 활 사용을 위함
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		EActionState ActionState = EActionState::NORMAL;	// 캐릭터의 ActionState
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pawn, Meta = (AllowPrivateAccess = true))
		EAttackState AttackState = EAttackState::READY;		// 캐릭터의 AttackState
};
