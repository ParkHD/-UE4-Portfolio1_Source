// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/AddForceNotifyState.h"
#include "00_Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAddForceNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp != nullptr)
	{
		owner = Cast<ABaseCharacter>(MeshComp->GetOwner());
	}
}

void UAddForceNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (owner != nullptr)
	{
		// 입력한 방향에 따라 캐릭터 이동
		switch (forceDir)
		{
		case EForceDir::UP:
			owner->GetCharacterMovement()->AddImpulse(owner->GetActorUpVector() * force, true);
			break;
		case EForceDir::DOWN:
			owner->GetCharacterMovement()->AddImpulse(-owner->GetActorUpVector() * force, true);
			break;
		case EForceDir::LEFT:
			owner->GetCharacterMovement()->AddImpulse(-owner->GetActorRightVector() * force, true);
			break;
		case EForceDir::RIGHT:
			owner->GetCharacterMovement()->AddImpulse(owner->GetActorRightVector() * force, true);
			break;
		case EForceDir::FORWARD:
			owner->GetCharacterMovement()->AddImpulse(owner->GetActorForwardVector() * force, true);
			break;
		case EForceDir::BACKWARD:
			owner->GetCharacterMovement()->AddImpulse(-owner->GetActorForwardVector() * force, true);
			break;
		}
	}
}
void UAddForceNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

}