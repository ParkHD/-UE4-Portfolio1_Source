// Fill out your copyright notice in the Description page of Project Settings.

#include "00_Character/01_Monster/01_HumanType/HumanCharacter.h"
#include "00_Character/00_Player/Component/EquipmentComponent.h"
#include "00_Character/01_Monster/MonsterAIController.h"
#include "02_Item/00_Equipment/Weapon.h"
#include "02_Item/00_Equipment/Shield.h"
#include "BehaviorTree/BlackboardComponent.h"

AHumanCharacter::AHumanCharacter()
{
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));

	if (defaultAnimationBP != nullptr)
	{
		GetMesh()->SetAnimInstanceClass(defaultAnimationBP->GetAnimBlueprintGeneratedClass());
	}
}

void AHumanCharacter::BeginPlay()
{
	Super::BeginPlay();
}
void AHumanCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
void AHumanCharacter::SetAttackMontage(class UAnimMontage* montage)
{
	attackMontage = montage;
}
void AHumanCharacter::SetHitMontage(class UAnimMontage* montage)
{
	hitMontage = montage;
}
void AHumanCharacter::SetActionState(EActionState actionState)
{
	Super::SetActionState(actionState);

	AMonsterAIController* controller = GetController<AMonsterAIController>();

	switch (actionState)
	{
	case EActionState::NORMAL:
		// 활 무기를 사용 중일 때 보조무기인 화살 숨기기
		if (EquipmentComponent->GetEquippedWeapon()->GetItemInfo<FWeaponInformation>()->WeaponType == EWeaponType::BOW)
		{
			if (ShieldChildActorComponent->GetChildActor() != nullptr)
			{
				ShieldChildActorComponent->GetChildActor()->SetActorHiddenInGame(true);
			}
		}
		break;
	case EActionState::ATTACK:
		// 활 무기를 사용 하여 공격중일 떄 보조무기인 화살 Visible 활성화
		if (EquipmentComponent->GetEquippedWeapon()->GetItemInfo<FWeaponInformation>()->WeaponType == EWeaponType::BOW)
		{
			if (ShieldChildActorComponent->GetChildActor() != nullptr)
			{
				ShieldChildActorComponent->GetChildActor()->SetActorHiddenInGame(false);
			}
		}
		break;
	case EActionState::BLOCK:
		break;


	default:
		break;
	}
}
