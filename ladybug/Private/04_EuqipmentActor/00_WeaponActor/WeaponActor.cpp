// Fill out your copyright notice in the Description page of Project Settings.


#include "04_EuqipmentActor/00_WeaponActor/WeaponActor.h"
#include "00_Character/BaseCharacter.h"
#include "00_Character/00_Player/Component/StatusComponent.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "Kismet/GameplayStatics.h"

void AWeaponActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SkeletalMesh->SetGenerateOverlapEvents(true);
	SkeletalMesh->SetCollisionProfileName("NoCollision");

	OnActorBeginOverlap.AddUniqueDynamic(this, &AWeaponActor::OnActorBeginOverlapEvent);
}
void AWeaponActor::OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	ABaseCharacter* owner = Cast<ABaseCharacter>(GetParentActor());
	if (owner != nullptr && OtherActor != owner)
	{
		auto target = Cast<ABaseCharacter>(OtherActor);
		if (target != nullptr && target->GetGenericTeamId() != owner->GetGenericTeamId())
		{
			float damage = owner->GetStatusComponent()->GetStat().Damage;
			if(owner->AddHitActors(target))
			{
				FDamageEvent damageEvent;
				target->TakeDamageType(EDamageType::NORMAL, damage, damageEvent, owner->GetController(), owner);
				SkeletalMesh->SetCollisionProfileName("NoCollision");
			}
		}
	}
}