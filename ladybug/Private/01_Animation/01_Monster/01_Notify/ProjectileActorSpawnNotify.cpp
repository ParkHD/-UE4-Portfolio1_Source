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

				// Porjectile�� �ִ� ���͸� Velo����
				if (projectileActor != nullptr)
				{
					AMonsterAIController* controller = owner->GetController<AMonsterAIController>();
					// ��ȯ Target(��ġ) ����
					AActor* target = nullptr;
					// AI��� �����忡�� Target�� �����´�.
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
					// Porjectile�� ���� ���͸� �׳� �ش� ��ġ�� ��ȯ
				}
			}
		}
	}
}