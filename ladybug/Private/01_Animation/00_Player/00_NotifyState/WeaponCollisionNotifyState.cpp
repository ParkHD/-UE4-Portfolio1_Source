// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/00_Player/00_NotifyState/WeaponCollisionNotifyState.h"
#include "00_Character/BaseCharacter.h"
#include "04_EuqipmentActor/00_WeaponActor/WeaponActor.h"

void UWeaponCollisionNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp != nullptr)
	{
		owner = Cast<ABaseCharacter>(MeshComp->GetOwner());

		if (owner != nullptr)
		{
			AWeaponActor* weapon = Cast<AWeaponActor>(owner->GetWeaponComponent()->GetChildActor());
			if (weapon != nullptr)
			{
				weapon->GetSkeletalMesh()->SetCollisionProfileName("Weapon");
			}
		}
	}
}

void UWeaponCollisionNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp != nullptr)
	{
		if (owner != nullptr)
		{
			AWeaponActor* weapon = Cast<AWeaponActor>(owner->GetWeaponComponent()->GetChildActor());
			if (weapon != nullptr)
			{
				weapon->GetSkeletalMesh()->SetCollisionProfileName("NoCollision");
			}
			owner->ClearHitActors();
		}
	}
}
