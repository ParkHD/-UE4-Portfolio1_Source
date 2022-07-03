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
			angle = -range;			// 콜리전이 생성될 시작 각도
		}
	}

}
void UCollisionRangeNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	if (owner != nullptr)
	{
		// collision의 EndLocation 구하기
		FRotator tempRotator = startRotator;
		tempRotator.Yaw = angle;
		FRotator dirRotator = tempRotator + startRotator;	// 캐릭터기준으로 회전값 z축을 angle각도 회전시켰을 때 Rotator
		FVector endLocation = dirRotator.Vector()* 400.f + owner->GetActorLocation();

		// 현재 angle각도에 콜리전 생성
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
						auto skillInfo = owner->GetSkillComponent()->GetSkillInfo(skill_Tag);
						if (skillInfo != nullptr)
						{
							// 대미지 계산
							float ownerDamage = owner->GetStatusComponent()->GetStat().Damage;
							float skillDamage = ownerDamage * skillInfo->skill_Damage / 100;
							// Hit된 Actor에 대미지 적용
							target->TakeDamageType(EDamageType::SKILL, skillDamage, damageEvent, target->GetController(), target);
						}
					}
				}
			}
		}

		// angle 업데이트
		angle = FMath::FInterpTo(angle, range, FrameDeltaTime, interpSpeed);
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

