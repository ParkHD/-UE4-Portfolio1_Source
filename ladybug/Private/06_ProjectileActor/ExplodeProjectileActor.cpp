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
		// Overlap이 자신의 팀은 무시할 것인지 or 팀 상관없이 다 overlap할 것인지
		bool condition = true;
		ABaseCharacter* owner = Cast<ABaseCharacter>(GetOwner());
		if (OtherActor->IsA<ABaseCharacter>())
		{
			auto enemy = Cast<ABaseCharacter>(OtherActor);
			condition = bIgnoreMyTeam ? enemy->GetGenericTeamId() != owner->GetGenericTeamId() : true;
		}
		
		if(OtherActor != GetOwner() && condition)
		{
			// 터지는 파티클 생성
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitParticle, SweepResult.Location, FRotator::ZeroRotator, true);

			// 대미지를 줄 범위 콜리전 설정
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
				// hit된 Actor들 대미지 주기
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

