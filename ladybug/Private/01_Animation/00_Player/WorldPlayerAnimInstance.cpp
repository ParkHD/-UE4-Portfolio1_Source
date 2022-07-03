// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/00_Player/WorldPlayerAnimInstance.h"
#include "10_WorldCharacter/WorldBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWorldPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	owner = Cast<AWorldBaseCharacter>(GetOwningActor());
}
void UWorldPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(owner != nullptr)
	{
		playerSpeed = owner->GetCharacterMovement()->Velocity.Size();
	}
}
