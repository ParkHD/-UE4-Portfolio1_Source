// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/01_Monster/MonsterAnimInstance.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMonsterAnimInstance::NativeInitializeAnimation()
{
	owner = Cast<AMonsterBaseCharacter>(GetOwningActor());
}
void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (owner != nullptr)
	{
		moveSpeed = owner->GetCharacterMovement()->Velocity.Size();
		characterState = owner->GetCharacterMovement()->MovementMode;
		
		turnDir = owner->turnDir;
		
		actionState = owner->GetActionState();
		attackState = owner->GetAttackState();
	}
}