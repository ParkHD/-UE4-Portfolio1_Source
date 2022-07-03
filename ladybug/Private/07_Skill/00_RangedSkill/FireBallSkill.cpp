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
			// 스킬 몽타주 실행
			skillOwner->GetMesh()->GetAnimInstance()->Montage_Play(GetSkillInfo()->skill_Montage);

			FTimerHandle spawnFireTimer;
			FTimerDelegate spawnFireDelegate = FTimerDelegate::CreateUObject(this, &UFireBallSkill::SpawnFireBall);

			// 일정시간후에 fireball을 소환한다 -> 애니메이션 모션 타이밍에 맞게 fireball소환하기 위함
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

				// Porjectile이 있는 액터면 Velo설정
				if (projectileActor != nullptr)
				{
					AMonsterAIController* controller = skillOwner->GetController<AMonsterAIController>();
					// Target 설정
					AActor* target = nullptr;
					// AI라면 블랙보드에서 Target을 가져온다.
					if (controller != nullptr)
					{
						target = Cast<AActor>(controller->GetBlackboardComponent()->GetValueAsObject("Target"));
					}

					// 발사 할 방향 구하기 = 타겟 방향
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
					// 타겟방향으로 발사
					projectileActor->GetProjectileComponent()->Velocity = lookAt * projectileSpeed;
				}
				else
				{
					// Porjectile이 없는 액터면 그냥 해당 위치에 소환
				}
			}
			
		}
	}
}