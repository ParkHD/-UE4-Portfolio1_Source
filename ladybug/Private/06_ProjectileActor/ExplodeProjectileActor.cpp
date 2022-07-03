// Fill out your copyright notice in the Description page of Project Settings.


#include "06_ProjectileActor/ExplodeProjectileActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "00_Character/BaseCharacter.h"
#include "00_Character/00_Player/Component/StatusComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


void AExplodeProjectileActor::OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(hitParticle != nullptr)
	{
		bool condition = true;
		ABaseCharacter* owner = Cast<ABaseCharacter>(GetOwner());
		if (OtherActor->IsA<ABaseCharacter>())
		{
			auto enemy = Cast<ABaseCharacter>(OtherActor);
			condition = bIgnoreMyTeam ? enemy->GetGenericTeamId() != owner->GetGenericTeamId() : true;
		}
		
		if(OtherActor != GetOwner() && condition)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitParticle, SweepResult.Location, FRotator::ZeroRotator, true);

			FVector start = SweepResult.Location;
			FVector end = start + SweepResult.Location.UpVector * radius / 4;
			TArray<TEnumAsByte<EObjectTypeQuery>> objects;
			objects.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel9));
			TArray<AActor*> ignoreActors;
			ignoreActors.Emplace(GetOwner());

			TArray<FHitResult> hits;
			if (UKismetSystemLibrary::SphereTraceMultiForObjects(
				GetWorld(),
				start,
				end,
				radius,
				objects,
				false,
				ignoreActors,
				EDrawDebugTrace::None,
				hits,
				true
			))
			{
				float ownerDamage = owner->GetStatusComponent()->GetStat().Damage;
				for (auto hit : hits)
				{
					if (owner->AddHitActors(hit.GetActor()))
					{
						EDamageType damageType = isSkill ? EDamageType::SKILL : EDamageType::NORMAL;
						Cast<ABaseCharacter>(hit.GetActor())->TakeDamageType(damageType,
							ownerDamage, FDamageEvent(), owner->GetController(), owner);


					}
				}
				owner->ClearHitActors();
			}
			Destroy();
		}
		
	}
}

