// Fill out your copyright notice in the Description page of Project Settings.


#include "07_Skill/00_RangedSkill/FireBallSkill.h"
#include "06_ProjectileActor/ProjectileActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "00_Character/BaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


void UFireBallSkill::ActivateSkill()
{
	Super::ActivateSkill();

	if (fireBall != nullptr)
	{
		if (skillOwner != nullptr)
		{
			// ��ų ��Ÿ�� ����
			skillOwner->GetMesh()->GetAnimInstance()->Montage_Play(GetSkillInfo()->skill_Montage);

			FTimerHandle spawnFireTimer;
			FTimerDelegate spawnFireDelegate = FTimerDelegate::CreateUObject(this, &UFireBallSkill::SpawnFireBall);

			// �����ð��Ŀ� fireball�� ��ȯ�Ѵ� -> �ִϸ��̼� ��� Ÿ�ֿ̹� �°� fireball��ȯ�ϱ� ����
			skillOwner->GetWorld()->GetTimerManager().SetTimer(spawnFireTimer,
				spawnFireDelegate,
				spawnTime,
				false);
		}
	}
}

void UFireBallSkill::SpawnFireBall()
{
	if (fireBall != nullptr)
	{
		if (skillOwner != nullptr)
		{
			AActor* actor = skillOwner->GetWorld()->SpawnActor<AActor>(fireBall, skillOwner->GetMesh()->GetSocketLocation(spawnSocketName), FRotator::ZeroRotator);

			if (actor != nullptr)
			{
				actor->SetOwner(skillOwner);

				AProjectileActor* projectileActor = Cast<AProjectileActor>(actor);

				// Porjectile�� �ִ� ���͸� Velo����
				if (projectileActor != nullptr)
				{
					AMonsterAIController* controller = skillOwner->GetController<AMonsterAIController>();
					// Target ����
					AActor* target = nullptr;
					// AI��� �����忡�� Target�� �����´�.
					if (controller != nullptr)
					{
						target = Cast<AActor>(controller->GetBlackboardComponent()->GetValueAsObject("Target"));
					}

					// �߻� �� ���� ���ϱ� = Ÿ�� ����
					FVector lookAt;
					if (target != nullptr)
					{
						lookAt = target->GetActorLocation() - skillOwner->GetMesh()->GetSocketLocation(spawnSocketName);
						projectileActor->SetActorRotation(lookAt.Rotation());
					}
					else
					{
						lookAt = skillOwner->GetMesh()->GetSocketLocation(spawnSocketName).ForwardVector;
					}
					// Ÿ�ٹ������� �߻�
					projectileActor->GetProjectileComponent()->Velocity = lookAt * projectileSpeed;
				}
				else
				{
					// Porjectile�� ���� ���͸� �׳� �ش� ��ġ�� ��ȯ
				}
			}
			
		}
	}
}