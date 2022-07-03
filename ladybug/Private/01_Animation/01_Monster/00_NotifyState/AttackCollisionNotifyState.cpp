// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/01_Monster/00_NotifyState/AttackCollisionNotifyState.h"
#include "Kismet/GameplayStatics.h"
#include "00_Character/BaseCharacter.h"
#include "00_Character/00_Player/Component/StatusComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAttackCollisionNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp != nullptr)
	{
		owner = Cast<ABaseCharacter>(MeshComp->GetOwner());
		if(owner != nullptr)
		{
			// 공격을 했으므로 공격 CoolTime돌기
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
		// 만약 입력받은 끝점이 없다면 start를 기준으로 일정 거리 이상 앞을 end로 잡는다.
		if (endSocketName.IsNone())
		{
			end = start + owner->GetActorForwardVector() * collisionHeight;
		}
		TArray<FHitResult> hits;
		FCollisionQueryParams Params;
		TArray<TEnumAsByte<EObjectTypeQuery>> objects;		
		objects.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel9));	// BattleCharacter

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

				// 타겟이 적 인지 확인
				if (target != nullptr && target->GetGenericTeamId() != owner->GetGenericTeamId())
				{
					bool condition = bMultiAttack ? hitActor.Num() <= 1 : !hitActor.Contains(target);
					if (condition)
					{
						hitActor.Emplace(target);
						// 대미지 설정
						float damage = owner->GetStatusComponent()->GetStat().Damage;
						// 기본공격인지 스킬 공격인지 구분
						EDamageType damageType = isSkill ? EDamageType::SKILL : EDamageType::NORMAL;
						FDamageEvent damageEvent;
						target->TakeDamageType(damageType, damage, damageEvent, owner->GetController(), owner, isBreakBlock);

						// 피격된 대상을 넉백 시킨다.
						FVector KnockBackDir = (target->GetActorLocation() - owner->GetActorLocation()).GetSafeNormal();
						target->LaunchCharacter(KnockBackDir * 1500, true, true);
					}
				}
			}
		}
	}
}

void UAttackCollisionNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	// hitActor 초기화
	if (owner != nullptr)
	{
		hitActor.Empty();
	}
}
