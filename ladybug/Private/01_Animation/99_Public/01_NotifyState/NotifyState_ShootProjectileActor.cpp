// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/99_Public/01_NotifyState/NotifyState_ShootProjectileActor.h"
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
void UNotifyState_ShootProjectileActor::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp != nullptr)
	{
		owner = MeshComp->GetOwner<ABaseCharacter>();
		if (owner != nullptr)
		{
			FVector spawnLocation;
			FRotator spawnRotator;
			if (spawnSocketName.IsNone())
			{
				spawnLocation = owner->GetActorLocation() + owner->GetActorForwardVector() * 150.f;
				spawnRotator = owner->GetActorRotation() + spawnRotation;
			}
			else
			{
				spawnLocation = MeshComp->GetSocketLocation(spawnSocketName);
				spawnRotator = MeshComp->GetSocketRotation(spawnSocketName);
			}
			projectileActor = owner->GetWorld()->SpawnActor<AProjectileActor>(ActorToSpawn);
			if (spawnSocketName.IsNone())
			{
				projectileActor->SetActorLocation(spawnLocation);
				projectileActor->SetActorRotation(spawnRotator);
			}
			else
			{
				projectileActor->AttachToComponent(MeshComp, FAttachmentTransformRules::KeepRelativeTransform, spawnSocketName);
			}
			projectileActor->SetOwner(owner);
			// 스킬 대미지 계산 및 적용
			auto skillInfo = owner->GetSkillComponent()->GetSkillInfo(skill_Tag);
			if (skillInfo != nullptr)
			{
				float ownerDamage = owner->GetStatusComponent()->GetStat().Damage;
				float skillDamage = ownerDamage * skillInfo->skill_Damage / 100;
				projectileActor->SetSkillDamage(skillDamage);
			}
			
		}
	}
}

void UNotifyState_ShootProjectileActor::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UNotifyState_ShootProjectileActor::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if(owner != nullptr)
	{
		FVector projectileDir;
		if (spawnSocketName.IsNone())
		{
			projectileDir = owner->GetActorForwardVector();
		}
		else
		{
			projectileDir = GetShotDir(owner);
			projectileActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		}
		projectileActor->TurnOnCollision(true);
		projectileActor->GetProjectileComponent()->Velocity = projectileDir * projectileSpeed;
	}
	
}

FVector UNotifyState_ShootProjectileActor::GetShotDir(ABaseCharacter* characterOwner)
{
	FVector shotDir;
	if (characterOwner->IsA<APlayerCharacter>())
	{
		FVector start = Cast<APlayerCharacter>(characterOwner)->GetCameraComponent()->GetComponentLocation();
		FVector end = start + characterOwner->GetControlRotation().Vector() * 100000.f;

		TArray<TEnumAsByte<EObjectTypeQuery>> objects;
		objects.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel9));
		objects.Emplace(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));

		FHitResult hit;
		if (UKismetSystemLibrary::LineTraceSingleForObjects(
			characterOwner->GetWorld(),
			start,
			end,
			objects,
			false,
			TArray<AActor*>(),
			EDrawDebugTrace::ForDuration,
			hit,
			true))
		{
			FVector startLocation = characterOwner->GetMesh()->GetSocketLocation(spawnSocketName);
			FVector targetLocation = hit.Location;
			shotDir = (targetLocation - startLocation);
		}
		else
		{
			FVector startLocation = characterOwner->GetMesh()->GetSocketLocation(spawnSocketName);
			FVector targetLocation = end;
			shotDir = (targetLocation - startLocation);
		}
		shotDir = shotDir.GetUnsafeNormal();
	}
	else if (characterOwner->IsA<AMonsterBaseCharacter>())
	{
		auto monController = characterOwner->GetController<AMonsterAIController>();
		if (monController != nullptr)
		{
			auto target = monController->GetBlackboardComponent()->GetValueAsObject("Target");
			if (target != nullptr)
			{
				shotDir = Cast<AActor>(target)->GetActorLocation() - characterOwner->GetMesh()->GetSocketLocation(spawnSocketName);
				UE_LOG(LogTemp, Log, TEXT("00"));
				shotDir = shotDir.GetUnsafeNormal();
			}
			else
			{
				shotDir = characterOwner->GetActorForwardVector();
				shotDir = shotDir.GetUnsafeNormal();

			}
		}
	}
	return shotDir;
}
