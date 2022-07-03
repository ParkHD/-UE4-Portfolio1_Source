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
			FVector spawnLocation;	// 스폰할 위치
			FRotator spawnRotator;	// 스폰할 회전값
			FVector projectileDir;	// 발사 할 방향

			// 소켓네임이 없다면 캐릭터의 일정거리 앞으로 생성할 위치 설정
			if(spawnSocketName.IsNone())
			{
				// 캐릭터의 일정거리 앞으로 생성
				spawnLocation = owner->GetActorLocation() + owner->GetActorForwardVector() * 150.f;
				spawnRotator = owner->GetActorRotation() + spawnRotation;
				projectileDir = owner->GetActorForwardVector();		// 캐릭터의 Forward방향으로 발사
			}
			// 소켓네임이 있다면 소켓을 기준으로 생성할 위치 설정
			else
			{
				// 입력받은 소켓의 위치로 생성
				spawnLocation = MeshComp->GetSocketLocation(spawnSocketName);
				projectileDir = GetShotDir(owner);			// 발사 할 방향 구하기
				spawnRotator = projectileDir.Rotation();
			}

			// ProjectileActor 소환 및 owner설정
			auto projectileActor = owner->GetWorld()->SpawnActor<AProjectileActor>(ActorToSpawn, spawnLocation, spawnRotator);
			projectileActor->SetOwner(owner);

			// ProjectileActor의 대미지 계산 및 적용
			auto skillInfo = owner->GetSkillComponent()->GetSkillInfo(skill_Tag);
			if(skillInfo != nullptr)
			{
				float ownerDamage = owner->GetStatusComponent()->GetStat().Damage;
				float skillDamage = ownerDamage * skillInfo->skill_Damage / 100;
				projectileActor->SetSkillDamage(skillDamage);
			}
			projectileActor->TurnOnCollision(true);			// Actor 콜리전 활성화
			projectileActor->GetProjectileComponent()->Velocity = projectileDir * projectileSpeed;	// 발사
		}
	}
}

FVector UNotify_SpawnProjectileActor::GetShotDir(ABaseCharacter* owner)
{
	FVector shotDir;
	// owner가 player라면 카메라가 바라보고 있는 방향으로 Ray를 쏴서 Hit된 Actor를 기준으로 방향 설정 
	if (owner->IsA<APlayerCharacter>())
	{
		// 카메라가 보는 방향에서 ~ (맵끝까지의 방향)
		FVector start = Cast<APlayerCharacter>(owner)->GetCameraComponent()->GetComponentLocation();
		FVector end = start + owner->GetControlRotation().Vector() * 100000.f;

		// WorldStatic과 BattleCharacter가 Hit되도록 설정
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
			// Hit된 Actor방향으로 발사
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

		// 방향의 노말벡터
		shotDir = shotDir.GetUnsafeNormal();
	}
	// owner가 AI라면 블랙보드에서 타겟을 기준으로 방향을 설정
	else if (owner->IsA<AMonsterBaseCharacter>())
	{
		auto monController = owner->GetController<AMonsterAIController>();
		if (monController != nullptr)
		{
			auto target = monController->GetBlackboardComponent()->GetValueAsObject("Target");
			if (target != nullptr)
			{
				// 타겟위치로 발사
				shotDir = Cast<AActor>(target)->GetActorLocation() - owner->GetMesh()->GetSocketLocation(spawnSocketName);
				shotDir = shotDir.GetUnsafeNormal();
			}
		}
	}
	return shotDir;
}
