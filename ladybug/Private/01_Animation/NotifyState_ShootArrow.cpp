// Fill out your copyright notice in the Description page of Project Settings.

#include "01_Animation/NotifyState_ShootArrow.h"

#include "00_Character/00_Player/CustomController.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/Component/EquipmentComponent.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "06_ProjectileActor/ProjectileActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "00_Character/01_Monster/MonsterAIController.h"
#include "00_Character/01_Monster/01_HumanType/HumanCharacter.h"
#include "02_Item/00_Equipment/Weapon.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void UNotifyState_ShootArrow::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp != nullptr)
	{
		owner = MeshComp->GetOwner<ABaseCharacter>();
		
		
	}
}

void UNotifyState_ShootArrow::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UNotifyState_ShootArrow::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	TSubclassOf<AProjectileActor> spawnArrow;
	if (owner != nullptr)
	{
		
		if (owner->IsA<APlayerCharacter>())
		{
			if(Cast<APlayerCharacter>(owner)->GetEquipmentComponent()->GetEquippedSubWeapon() != nullptr)
			{
				spawnArrow = Cast<APlayerCharacter>(owner)->GetEquipmentComponent()->GetEquippedSubWeapon()
					->GetItemInfo<FWeaponInformation>()->projectileActor;
			}

			FVector start = Cast<APlayerCharacter>(owner)->GetCameraComponent()->GetComponentLocation();
			FVector end = start + owner->GetControlRotation().Vector() * 100000.f;

			TArray<TEnumAsByte<EObjectTypeQuery>> objects;
			objects.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel9));
			objects.Emplace(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
			TArray<AActor*> ignoreObjects;
			ignoreObjects.Emplace(owner);
			FHitResult hit;
			if (UKismetSystemLibrary::LineTraceSingleForObjects(
				owner->GetWorld(),
				start,
				end,
				objects,
				false,
				ignoreObjects,
				EDrawDebugTrace::None,
				hit,
				true))
			{
				FVector startLocation = MeshComp->GetSocketLocation(SpawnSocketName);
				FVector targetLocation = hit.Location;
				shootDir = (targetLocation - startLocation);
			}
			else
			{
				FVector startLocation = MeshComp->GetSocketLocation(SpawnSocketName);
				FVector targetLocation = end;
				shootDir = (targetLocation - startLocation);
			}
			float accuracy = Cast<APlayerCharacter>(owner)->GetController<ACustomController>()->GetAimWidgetSize().X;
			UE_LOG(LogTemp, Log, TEXT("%f"), accuracy);
			shootDir.Y = shootDir.Y + FMath::FRandRange(-accuracy/2, accuracy/2);
			shootDir.Z = shootDir.Z + FMath::FRandRange(-accuracy/2, accuracy/2);

			shootDir = shootDir.GetUnsafeNormal();
		}
		else if (owner->IsA<AHumanCharacter>())
		{
			if (Cast<AHumanCharacter>(owner)->GetEquipmentComponent()->GetEquippedSubWeapon() != nullptr)
			{
				spawnArrow = Cast<AHumanCharacter>(owner)->GetEquipmentComponent()->GetEquippedSubWeapon()
					->GetItemInfo<FWeaponInformation>()->projectileActor;
			}

			auto monController = owner->GetController<AMonsterAIController>();
			if (monController != nullptr)
			{
				auto target = monController->GetBlackboardComponent()->GetValueAsObject("Target");
				if (target != nullptr)
				{
					shootDir = Cast<AActor>(target)->GetActorLocation() - MeshComp->GetSocketLocation(SpawnSocketName);

					shootDir.Y = shootDir.Y + FMath::FRandRange(-Accuracy, Accuracy);
					shootDir.Z = shootDir.Z + FMath::FRandRange(-Accuracy, Accuracy);

					shootDir = shootDir.GetUnsafeNormal();
				}
			}
		}
		

		owner->GetShieldComponent()->GetChildActor()->SetActorHiddenInGame(true);

		auto projectileActor = owner->GetWorld()->SpawnActor<AProjectileActor>(spawnArrow, MeshComp->GetSocketLocation(SpawnSocketName), shootDir.Rotation());
		projectileActor->SetOwner(owner);
		projectileActor->SetSkillDamage(owner->GetStatusComponent()->GetStat().Damage);
		projectileActor->TurnOnCollision(true);
		projectileActor->GetProjectileComponent()->Velocity = shootDir * ProjectileSpeed;
	}
}
