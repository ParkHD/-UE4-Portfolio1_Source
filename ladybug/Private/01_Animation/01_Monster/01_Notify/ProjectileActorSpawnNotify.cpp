// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/01_Monster/01_Notify/ProjectileActorSpawnNotify.h"
#include "06_ProjectileActor/ProjectileActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "00_Character/BaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UProjectileActorSpawnNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp != nullptr)
	{
		if (actorToSpawn != nullptr)
		{
			ABaseCharacter* owner = Cast<ABaseCharacter>(MeshComp->GetOwner());
			if (owner != nullptr)
			{
				AActor* actor = MeshComp->GetWorld()->SpawnActor<AActor>(actorToSpawn, MeshComp->GetSocketLocation(spawnSocketName), FRotator::ZeroRotator);
				actor->SetOwner(MeshComp->GetOwner());

				AProjectileActor* projectileActor = Cast<AProjectileActor>(actor);

				// Porjectile이 있는 액터면 Velo설정
				if (projectileActor != nullptr)
				{
					AMonsterAIController* controller = owner->GetController<AMonsterAIController>();
					// 소환 Target(위치) 설정
					AActor* target = nullptr;
					// AI라면 블랙보드에서 Target을 가져온다.
					if (controller != nullptr)
					{
						target = Cast<AActor>(controller->GetBlackboardComponent()->GetValueAsObject("Target"));
					}

					FVector lookAt;
					if (target != nullptr)
					{
						lookAt = target->GetActorLocation() - MeshComp->GetSocketLocation(spawnSocketName);
						projectileActor->SetActorRotation(lookAt.Rotation());
					}
					else
					{
						lookAt = MeshComp->GetSocketLocation(spawnSocketName).ForwardVector;
					}
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