// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/00_Player/PlayerAnimInstance.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{

}
// begin�� �ϸ� player�� �ʱ�ȭ�� �ȴ� begin�� �� �����ҋ� �ѹ��� �̶� �׷���
void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	player = Cast<APlayerCharacter>(GetOwningActor());
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (player != nullptr && player->InputComponent)
	{
		playerSpeed = player->GetVelocity().Size();
		moveDirection = player->GetMoveDirection();

		isJumping = player->GetCharacterMovement()->IsFalling(); 

		playerTurn = player->InputComponent->GetAxisValue("Turn");

		ActionState = player->GetActionState();
		AttackState = player->GetAttackState();
	}
}