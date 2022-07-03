// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/00_Player/01_Notify/Notify_SpawnProjectileActor.h"

#include "00_Character/BaseCharacter.h"
#include "00_Character/00_Player/CustomController.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/Component/StatusComponent.h"
#include "00_Character/01_Monster/MonsterAIController.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "00_Character/02_Component/SkillComponent.h"
#include "06_ProjectileActor/ProjectileActor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void UNotify_SpawnProjectileActor::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp != nullptr)
	{
		auto owner = MeshComp->GetOwner<ABaseCharacter>();
		if(owner != nullptr)
		{
			FVector spawnLocation;	// ������ ��ġ
			FRotator spawnRotator;	// ������ ȸ����
			FVector projectileDir;	// �߻� �� ����

			// ���ϳ����� ���ٸ� ĳ������ �����Ÿ� ������ ������ ��ġ ����
			if(spawnSocketName.IsNone())
			{
				// ĳ������ �����Ÿ� ������ ����
				spawnLocation = owner->GetActorLocation() + owner->GetActorForwardVector() * 150.f;
				spawnRotator = owner->GetActorRotation() + spawnRotation;
				projectileDir = owner->GetActorForwardVector();		// ĳ������ Forward�������� �߻�
			}
			// ���ϳ����� �ִٸ� ������ �������� ������ ��ġ ����
			else
			{
				// �Է¹��� ������ ��ġ�� ����
				spawnLocation = MeshComp->GetSocketLocation(spawnSocketName);
				projectileDir = GetShotDir(owner);			// �߻� �� ���� ���ϱ�
				spawnRotator = projectileDir.Rotation();
			}

			// ProjectileActor ��ȯ �� owner����
			auto projectileActor = owner->GetWorld()->SpawnActor<AProjectileActor>(ActorToSpawn, spawnLocation, spawnRotator);
			projectileActor->SetOwner(owner);

			// ProjectileActor�� ����� ��� �� ����
			auto skillInfo = owner->GetSkillComponent()->GetSkillInfo(skill_Tag);
			if(skillInfo != nullptr)
			{
				float ownerDamage = owner->GetStatusComponent()->GetStat().Damage;
				float skillDamage = ownerDamage * skillInfo->skill_Damage / 100;
				projectileActor->SetSkillDamage(skillDamage);
			}
			projectileActor->TurnOnCollision(true);			// Actor �ݸ��� Ȱ��ȭ
			projectileActor->GetProjectileComponent()->Velocity = projectileDir * projectileSpeed;	// �߻�
		}
	}
}

FVector UNotify_SpawnProjectileActor::GetShotDir(ABaseCharacter* owner)
{
	FVector shotDir;
	// owner�� player��� ī�޶� �ٶ󺸰� �ִ� �������� Ray�� ���� Hit�� Actor�� �������� ���� ���� 
	if (owner->IsA<APlayerCharacter>())
	{
		// ī�޶� ���� ���⿡�� ~ (�ʳ������� ����)
		FVector start = Cast<APlayerCharacter>(owner)->GetCameraComponent()->GetComponentLocation();
		FVector end = start + owner->GetControlRotation().Vector() * 100000.f;

		// WorldStatic�� BattleCharacter�� Hit�ǵ��� ����
		TArray<TEnumAsByte<EObjectTypeQuery>> objects;
		objects.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel9));
		objects.Emplace(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));

		FHitResult hit;
		if (UKismetSystemLibrary::LineTraceSingleForObjects(
			owner->GetWorld(),
			start,
			end,
			objects,
			false,
			TArray<AActor*>(),
			EDrawDebugTrace::None,
			hit,
			true))
		{
			// Hit�� Actor�������� �߻�
			FVector startLocation = owner->GetMesh()->GetSocketLocation(spawnSocketName);
			FVector targetLocation = hit.Location;
			shotDir = (targetLocation - startLocation);
		}
		else
		{
			FVector startLocation = owner->GetMesh()->GetSocketLocation(spawnSocketName);
			FVector targetLocation = end;
			shotDir = (targetLocation - startLocation);
		}

		// ������ �븻����
		shotDir = shotDir.GetUnsafeNormal();
	}
	// owner�� AI��� �����忡�� Ÿ���� �������� ������ ����
	else if (owner->IsA<AMonsterBaseCharacter>())
	{
		auto monController = owner->GetController<AMonsterAIController>();
		if (monController != nullptr)
		{
			auto target = monController->GetBlackboardComponent()->GetValueAsObject("Target");
			if (target != nullptr)
			{
				// Ÿ����ġ�� �߻�
				shotDir = Cast<AActor>(target)->GetActorLocation() - owner->GetMesh()->GetSocketLocation(spawnSocketName);
				shotDir = shotDir.GetUnsafeNormal();
			}
		}
	}
	return shotDir;
}
