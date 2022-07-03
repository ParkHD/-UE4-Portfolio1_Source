// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/CollisionRangeNotifyState.h"
#include "Kismet/GameplayStatics.h"
#include "00_Character/BaseCharacter.h"
#include "00_Character/00_Player/Component/StatusComponent.h"
#include "00_Character/02_Component/SkillComponent.h"

void UCollisionRangeNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp != nullptr)
	{
		owner = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if (owner != nullptr)
		{
			startLocation = owner->GetActorLocation();
			startRotator = owner->GetActorRotation();
			angle = -range;
		}
	}

}
void UCollisionRangeNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	if (owner != nullptr)
	{
		FRotator tempRotator = startRotator;
		tempRotator.Yaw = angle;
		FRotator dirRotator = tempRotator + startRotator;
		
		FVector endLocation = dirRotator.Vector()* 400.f + owner->GetActorLocation();


		TArray<FHitResult> hits;
		FCollisionQueryParams Params;
		TArray<TEnumAsByte<EObjectTypeQuery>> objects;
		objects.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel9));
		if (UKismetSystemLibrary::SphereTraceMultiForObjects(
			owner,
			owner->GetActorLocation(),
			endLocation,
			collisionRadius,
			objects,
			false,
			TArray<AActor*>(),
			EDrawDebugTrace::None,
			hits,
			true))
		{
			for (FHitResult hit : hits)
			{
				ABaseCharacter* target = Cast<ABaseCharacter>(hit.GetActor());

				if (target != nullptr && target->GetGenericTeamId() != owner->GetGenericTeamId())
				{
					if (owner->AddHitActors(target))
					{
						FDamageEvent damageEvent;
						// 스킬 대미지 계산 및 적용
						auto skillInfo = owner->GetSkillComponent()->GetSkillInfo(skill_Tag);
						if (skillInfo != nullptr)
						{
							float ownerDamage = owner->GetStatusComponent()->GetStat().Damage;
							float skillDamage = ownerDamage * skillInfo->skill_Damage / 100;
							target->TakeDamageType(EDamageType::SKILL, skillDamage, damageEvent, target->GetController(), target);
						}
					}
				}
			}
		}

		angle = FMath::FInterpTo(angle, range, FrameDeltaTime, interpSpeed);
		//UE_LOG(LogTemp, Log, TEXT("angle : %f"), angle);
	}
}

void UCollisionRangeNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (owner != nullptr)
	{
		owner->ClearHitActors();
	}
}

