// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/01_Monster/WorldMonsterAnimInstance.h"
#include "10_WorldCharacter/WorldBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWorldMonsterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	owner = Cast<AWorldBaseCharacter>(GetOwningActor());
}
void UWorldMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (owner != nullptr)
	{
		Speed = owner->GetCharacterMovement()->Velocity.Size();
	}
}
