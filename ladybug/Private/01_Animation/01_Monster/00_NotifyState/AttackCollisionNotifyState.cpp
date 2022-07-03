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
			// ������ �����Ƿ� ���� CoolTime����
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
		// ���� �Է¹��� ������ ���ٸ� start�� �������� ���� �Ÿ� �̻� ���� end�� ��´�.
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

				// Ÿ���� �� ���� Ȯ��
				if (target != nullptr && target->GetGenericTeamId() != owner->GetGenericTeamId())
				{
					bool condition = bMultiAttack ? hitActor.Num() <= 1 : !hitActor.Contains(target);
					if (condition)
					{
						hitActor.Emplace(target);
						// ����� ����
						float damage = owner->GetStatusComponent()->GetStat().Damage;
						// �⺻�������� ��ų �������� ����
						EDamageType damageType = isSkill ? EDamageType::SKILL : EDamageType::NORMAL;
						FDamageEvent damageEvent;
						target->TakeDamageType(damageType, damage, damageEvent, owner->GetController(), owner, isBreakBlock);

						// �ǰݵ� ����� �˹� ��Ų��.
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

	// hitActor �ʱ�ȭ
	if (owner != nullptr)
	{
		hitActor.Empty();
	}
}
