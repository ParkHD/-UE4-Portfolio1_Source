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
		// owner가 player라면 카메라가 바라보고 있는 방향으로 Ray를 쏴서 Hit된 Actor가 있는 곳으로 방향 설정 
		if (owner->IsA<APlayerCharacter>())
		{
			if(Cast<APlayerCharacter>(owner)->GetEquipmentComponent()->GetEquippedSubWeapon() != nullptr)
			{
				spawnArrow = Cast<APlayerCharacter>(owner)->GetEquipmentComponent()->GetEquippedSubWeapon()
					->GetItemInfo<FWeaponInformation>()->projectileActor;
			}

			// 화살 방향 설정 -> Hit된 Actor가 있는 곳으로 방향 설정 
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

			// 정확도 조정 -> AimWidget 크기 안에 랜덤으로 위치 설정
			float accuracy = Cast<APlayerCharacter>(owner)->GetController<ACustomController>()->GetAimWidgetSize().X;
			shootDir.Y = shootDir.Y + FMath::FRandRange(-accuracy/2, accuracy/2);
			shootDir.Z = shootDir.Z + FMath::FRandRange(-accuracy/2, accuracy/2);

			shootDir = shootDir.GetUnsafeNormal();
		}
		// owner가 AI라면 블랙보드에서 타겟을 기준으로 방향을 설정
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
					// 정확도 조정
					shootDir = Cast<AActor>(target)->GetActorLocation() - MeshComp->GetSocketLocation(SpawnSocketName);

					shootDir.Y = shootDir.Y + FMath::FRandRange(-Accuracy, Accuracy);
					shootDir.Z = shootDir.Z + FMath::FRandRange(-Accuracy, Accuracy);

					shootDir = shootDir.GetUnsafeNormal();
				}
			}
		}

		// 화살이 발사 되면 보조무기인 화살 숨기기
		owner->GetShieldComponent()->GetChildActor()->SetActorHiddenInGame(true);

		// 화살 생성
		auto projectileActor = owner->GetWorld()->SpawnActor<AProjectileActor>(spawnArrow, MeshComp->GetSocketLocation(SpawnSocketName), shootDir.Rotation());
		projectileActor->SetOwner(owner);
		projectileActor->SetSkillDamage(owner->GetStatusComponent()->GetStat().Damage);		// 대미지 설정
		projectileActor->TurnOnCollision(true);												// 콜리전 활성화
		projectileActor->GetProjectileComponent()->Velocity = shootDir * ProjectileSpeed;	// 화살 발사
	}
}
