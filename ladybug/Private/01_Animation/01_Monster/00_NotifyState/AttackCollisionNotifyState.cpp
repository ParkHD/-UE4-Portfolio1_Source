// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/01_Monster/00_NotifyState/AttackCollisionNotifyState.h"
#include "Kismet/GameplayStatics.h"
#include "00_Character/BaseCharacter.h"
#include "00_Character/00_Player/Component/StatusComponent.h"

void UAttackCollisionNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp != nullptr)
	{
		owner = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if(owner != nullptr)
		{
			owner->SetAttackState(EAttackState::COOLTIME);
		}
	}
}
void UAttackCollisionNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	if (owner != nullptr)
	{
		FVector start = MeshComp->GetSocketLocation(startSocketName);
		FVector end = MeshComp->GetSocketLocation(endSocketName);
		if (endSocketName.IsNone())
		{
			end = start + owner->GetActorForwardVector() * collisionHeight;
		}
		TArray<FHitResult> hits;
		FCollisionQueryParams Params;
		TArray<TEnumAsByte<EObjectTypeQuery>> objects;		
		objects.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel9));

		if (UKismetSystemLibrary::SphereTraceMultiForObjects(
			owner,
			start,
			end,
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
					bool condition = bMultiAttack ? hitActor.Num() <= 1 : !hitActor.Contains(target);
					if (condition)
					{
						hitActor.Emplace(target);
						float damage = owner->GetStatusComponent()->GetStat().Damage;
						EDamageType damageType = isSkill ? EDamageType::SKILL : EDamageType::NORMAL;
						FDamageEvent damageEvent;
						target->TakeDamageType(damageType, damage, damageEvent, owner->GetController(), owner, isBreakBlock);
					}
				}
			}
		}
	}
}

void UAttackCollisionNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (owner != nullptr)
	{
		hitActor.Empty();
	}
}
