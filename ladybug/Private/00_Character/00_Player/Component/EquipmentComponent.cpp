// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/Component/EquipmentComponent.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "04_EuqipmentActor/00_WeaponActor/WeaponActor.h"
#include "02_Item/00_Equipment/Weapon.h"
#include "04_EuqipmentActor/01_ShieldActor/ShieldActor.h"
#include "02_Item/00_Equipment/Shield.h"

#include "00_Character/BaseCharacter.h"
#include "00_Character/00_Player/Component/InventoryComponent.h"
#include "00_Character/01_Monster/01_HumanType/HumanCharacter.h"
#include "00_Character/02_Component/SkillComponent.h"
#include "02_Item/00_Equipment/00_Armor/Armor.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	weaponList.Init(nullptr, 4);
	// ...
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// AI전용
	// 에디터에서 받은 무기List 넣기
	for(auto weaponBP : weaponBPList)
	{
		AddWeaponList(weaponBP.GetDefaultObject());
	}
	// 무기 장착
	for(int i = 0;i<weaponList.Num();i++)
	{
		if (weaponList[i] != nullptr)
		{
			EquipWeapon(i);
			break;
		}
	}

}
void UEquipmentComponent::InitializeComponent()
{
	Super::InitializeComponent();

}

// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



void UEquipmentComponent::SwapWeaponUp(bool isUp)
{
	if(!IsWeaponListEmpty())
	{
		// 마우스 휠 방향에 따라 장착 할 무기 인덱스 변동 및 장착
		while (true)
		{
			curWeaponIndex = isUp ? curWeaponIndex + 1 : curWeaponIndex - 1;
			curWeaponIndex = (curWeaponIndex + 4) % 4;
			if (weaponList[curWeaponIndex] != nullptr)
			{
				// 메인 무기인지 확인
				if (weaponList[curWeaponIndex]->GetItemInfo<FWeaponInformation>()->isMainWeapon)
				{
					// 무기 장착
					EquipWeapon(curWeaponIndex);
					break;
				}
			}
		}
	}
}
bool UEquipmentComponent::IsWeaponListEmpty()
{
	for(auto weapon : weaponList)
	{
		if(weapon != nullptr)
		{
			return false;
		}
	}
	return true;
}
void UEquipmentComponent::AddWeaponList(UWeapon* weapon)
{
	for(int i = 0;i<weaponList.Num();i++)
	{
		if(weaponList[i] == nullptr)
		{
			weaponList[i] = weapon;
			OnUpdateEquiment.Broadcast(this);		// 무기 List 넣고 위젯 업데이트
			break;
		}
	}
}
bool UEquipmentComponent::IsWeaponListFull()
{
	for(auto weapon : weaponList)
	{
		if(weapon == nullptr)
		{
			return false;
		}
	}
	return true;
}

void UEquipmentComponent::RemoveWeaponList(int32 index)
{
	auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
	if(owningPlayer != nullptr)
	{
		// 무기 해제 전에 인벤토리가 가득찼는지 확인
		if(!owningPlayer->GetInventoryComponent()->IsFull())
		{
			// 무기 인벤토리로 이동
			owningPlayer->GetInventoryComponent()->AddItem(weaponList[index]);
			weaponList[index] = nullptr;
			OnUpdateEquiment.Broadcast(this);		// 위젯 업데이트
		}
	}
}


/*
void UEquipmentComponent::EquipWeapon(UWeapon* weapon)
{
	auto weaponInfo = weapon->GetItemInfo<FWeaponInformation>();
	if(weaponInfo != nullptr)
	{
		if(weaponInfo->isMainWeapon)
		{
			equippedWeapon = weapon;

			class UChildActorComponent* weaponComp = GetOwner<ABaseCharacter>()->GetWeaponComponent();
			auto weaponChildActor = weaponComp->GetChildActor();
			if (weaponChildActor == nullptr)
			{
				weaponComp->SetChildActorClass(AWeaponActor::StaticClass());
			}
			weaponChildActor = weaponComp->GetChildActor();
			Cast<AWeaponActor>(weaponChildActor)->GetSkeletalMesh()->SetSkeletalMesh(weapon->GetItemInfo<FWeaponInformation>()->equipmentMesh);
			APlayerCharacter* player = Cast<APlayerCharacter>(GetOwner());
			if (weaponInfo != nullptr)
			{
				if (player != nullptr)
				{
					player->GetMesh()->SetAnimClass(weaponInfo->weaponAnimationBP->GetAnimBlueprintGeneratedClass());
					player->SetAttackMontage(weaponInfo->attackMontage);
					weaponComp->AttachToComponent(player->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, weaponInfo->equipSocketName);
					for (auto skill : weaponInfo->Weapon_Skills)
					{
						player->GetSkillComponent()->AddSkill(skill.GetDefaultObject());
					}
				}
				else
				{
					AHumanCharacter* character = Cast<AHumanCharacter>(GetOwner());
					if (character != nullptr)
					{
						character->GetMesh()->SetAnimClass(weaponInfo->weaponAnimationBP->GetAnimBlueprintGeneratedClass());
						character->SetAttackMontage(weaponInfo->attackMontage);
						weaponComp->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, weaponInfo->equipSocketName);
					}
				}
			}
		}
	}
}*/

void UEquipmentComponent::UpdateWidget()
{
	if(weaponList.Num()>0)
	{
		if(weaponList[0] != nullptr)
		{
			auto weaponInfo = weaponList[0]->GetItemInfo<FWeaponInformation>();
			if (weaponInfo != nullptr)
			{
				OnChangeWeapon.Broadcast(*weaponInfo);
			}
		}
	}
}

void UEquipmentComponent::EquipMeleeWeapon()
{
	for(int i = 0;i<weaponList.Num(); i++)
	{
		if (weaponList[i] != nullptr)
		{
			auto weaponInfo = weaponList[i]->GetItemInfo<FWeaponInformation>();
			if (weaponInfo != nullptr)
			{
				// 무기 List중에서 메인무기이면서 근거리 무기를 찾는다.
				if (weaponInfo->isMainWeapon)
				{
					if (weaponInfo->AttackType == EAttackType::Melee)
					{
						EquipWeapon(i);
					}
				}
			}
		}
	}
}

void UEquipmentComponent::EquipRangeWeapon()
{
	for (int i = 0; i < weaponList.Num(); i++)
	{
		if (weaponList[i] != nullptr)
		{
			auto weaponInfo = weaponList[i]->GetItemInfo<FWeaponInformation>();
			if (weaponInfo != nullptr)
			{
				// 무기 List중에서 메인무기이면서 원거리 무기를 찾는다.
				if (weaponInfo->isMainWeapon)
				{
					if (weaponInfo->AttackType == EAttackType::Range)
					{
						EquipWeapon(i);
					}
				}
			}
		}
	}
}

void UEquipmentComponent::EquipHelmet(UArmor* armor)
{
	if(armor != nullptr)
	{
		// 방어구를 해제 성공 or 장착한 방어구가 없을 때
		if (UnEquipHelmet() || Helmet == nullptr)
		{
			// 방어구 장착
			Helmet = armor;
			
			auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
			if (owningPlayer != nullptr)
			{
				// 스텟 변동
				owningPlayer->GetStatusComponent()->AddStat(Helmet->GetStat());
				// 스텟UI 및 장비창UI 업데이트
				OnUpdateEquiment.Broadcast(this);
				OnChangeEquipment.Broadcast(GetOwner<AWorldPlayerCharacter>()->GetStatusComponent());
			}
		}
	}
}

void UEquipmentComponent::EquipCape(UArmor* armor)
{
	// 방어구 해제
	UnEquipCape();

	// 방어구 장착
	Cape = armor;
	if (Cape != nullptr)
	{
		auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
		if (owningPlayer != nullptr)
		{
			if (!owningPlayer->GetInventoryComponent()->IsFull())
			{
				// 스텟 변동
				owningPlayer->GetStatusComponent()->AddStat(Cape->GetStat());
				// 스텟UI 및 장비창UI 업데이트
				OnUpdateEquiment.Broadcast(this);
				OnChangeEquipment.Broadcast(GetOwner<AWorldPlayerCharacter>()->GetStatusComponent());
			}
		}
	}
}

void UEquipmentComponent::EquipCloth(UArmor* armor)
{
	// 방어구 해제
	UnEquipCloth();

	// 방어구 장착
	Cloth = armor;
	if (Cloth != nullptr)
	{
		auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
		if (owningPlayer != nullptr)
		{
			if (!owningPlayer->GetInventoryComponent()->IsFull())
			{
				// 스텟 변동
				owningPlayer->GetStatusComponent()->AddStat(Cloth->GetStat());
				// 스텟UI 및 장비창UI 업데이트
				OnUpdateEquiment.Broadcast(this);
				OnChangeEquipment.Broadcast(GetOwner<AWorldPlayerCharacter>()->GetStatusComponent());
			}
		}
	}
}

void UEquipmentComponent::EquipGlove(UArmor* armor)
{
	// 방어구 해제
	UnEquipGlove();

	// 방어구 장착
	Glove = armor;
	if (Glove != nullptr)
	{
		auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
		if (owningPlayer != nullptr)
		{
			if (!owningPlayer->GetInventoryComponent()->IsFull())
			{
				// 스텟 변동
				owningPlayer->GetStatusComponent()->AddStat(Glove->GetStat());
				// 스텟UI 및 장비창UI 업데이트
				OnUpdateEquiment.Broadcast(this);
				OnChangeEquipment.Broadcast(GetOwner<AWorldPlayerCharacter>()->GetStatusComponent());
			}
		}
	}
}

void UEquipmentComponent::EquipShoes(UArmor* armor)
{
	// 방어구 해제
	UnEquipShoes();

	// 방어구 장착
	Shoes = armor;
	if (Shoes != nullptr)
	{
		auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
		if (owningPlayer != nullptr)
		{
			if (!owningPlayer->GetInventoryComponent()->IsFull())
			{
				// 스텟 변동
				owningPlayer->GetStatusComponent()->AddStat(Shoes->GetStat());
				// 스텟UI 및 장비창UI 업데이트
				OnUpdateEquiment.Broadcast(this);
				OnChangeEquipment.Broadcast(GetOwner<AWorldPlayerCharacter>()->GetStatusComponent());
			}
		}
	}
}

bool UEquipmentComponent::UnEquipHelmet()
{
	// 장비 해제해 성공했다면 true를 리턴 해준다
	if(Helmet != nullptr)
	{
		auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
		if (owningPlayer != nullptr)
		{
			// 인벤토리가 꽉찼다면 장비를 해제할 수 없다
			if (!owningPlayer->GetInventoryComponent()->IsFull())
			{
				// 장비 장착에 따른 스텟 업데이트
				owningPlayer->GetStatusComponent()->MinusStat(Helmet->GetStat());
				owningPlayer->GetInventoryComponent()->AddItem(Helmet);
				Helmet = nullptr;
				// 스텟UI 및 장비창UI 업데이트
				OnUpdateEquiment.Broadcast(this);
				OnChangeEquipment.Broadcast(GetOwner<AWorldPlayerCharacter>()->GetStatusComponent());
				return true;
			}
		}
	}
	return false;
}

void UEquipmentComponent::UnEquipCape()
{
	// 장비 해제해 성공했다면 true를 리턴 해준다
	if (Cape != nullptr)
	{
		auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
		if (owningPlayer != nullptr)
		{
			// 인벤토리가 꽉찼다면 장비를 해제할 수 없다
			if (!owningPlayer->GetInventoryComponent()->IsFull())
			{
				// 장비 장착에 따른 스텟 업데이트
				owningPlayer->GetStatusComponent()->MinusStat(Cape->GetStat());
				owningPlayer->GetInventoryComponent()->AddItem(Cape);
				Cape = nullptr;
				// 스텟UI 및 장비창UI 업데이트
				OnChangeEquipment.Broadcast(GetOwner<AWorldPlayerCharacter>()->GetStatusComponent());
				OnUpdateEquiment.Broadcast(this);
			}
		}
	}
}

void UEquipmentComponent::UnEquipCloth()
{
	// 장비 해제해 성공했다면 true를 리턴 해준다
	if (Cloth != nullptr)
	{
		auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
		if (owningPlayer != nullptr)
		{
			// 인벤토리가 꽉찼다면 장비를 해제할 수 없다
			if (!owningPlayer->GetInventoryComponent()->IsFull())
			{
				// 장비 장착에 따른 스텟 업데이트
				owningPlayer->GetStatusComponent()->MinusStat(Cloth->GetStat());
				owningPlayer->GetInventoryComponent()->AddItem(Cloth);
				Cloth = nullptr;
				// 스텟UI 및 장비창UI 업데이트
				OnChangeEquipment.Broadcast(GetOwner<AWorldPlayerCharacter>()->GetStatusComponent());
				OnUpdateEquiment.Broadcast(this);
			}
		}
	}
}

void UEquipmentComponent::UnEquipGlove()
{
	// 장비 해제해 성공했다면 true를 리턴 해준다
	if (Glove != nullptr)
	{
		auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
		if (owningPlayer != nullptr)
		{
			// 인벤토리가 꽉찼다면 장비를 해제할 수 없다
			if (!owningPlayer->GetInventoryComponent()->IsFull())
			{
				// 장비 장착에 따른 스텟 업데이트
				owningPlayer->GetStatusComponent()->MinusStat(Glove->GetStat());
				owningPlayer->GetInventoryComponent()->AddItem(Glove);
				Glove = nullptr;
				// 스텟UI 및 장비창UI 업데이트
				OnChangeEquipment.Broadcast(GetOwner<AWorldPlayerCharacter>()->GetStatusComponent());
				OnUpdateEquiment.Broadcast(this);
			}
		}
	}
}

void UEquipmentComponent::UnEquipShoes()
{
	// 장비 해제해 성공했다면 true를 리턴 해준다
	if (Shoes != nullptr)
	{
		auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
		if (owningPlayer != nullptr)
		{
			// 인벤토리가 꽉찼다면 장비를 해제할 수 없다
			if (!owningPlayer->GetInventoryComponent()->IsFull())
			{
				// 장비 장착에 따른 스텟 업데이트
				owningPlayer->GetStatusComponent()->MinusStat(Shoes->GetStat());
				owningPlayer->GetInventoryComponent()->AddItem(Shoes);
				Shoes = nullptr;
				// 스텟UI 및 장비창UI 업데이트
				OnChangeEquipment.Broadcast(GetOwner<AWorldPlayerCharacter>()->GetStatusComponent());
				OnUpdateEquiment.Broadcast(this);
			}
		}
	}
}

void UEquipmentComponent::EquipSupWeapon(class UWeapon* SupWeapon)
{
	equippedSupWeapon = SupWeapon;

	class UChildActorComponent* SupWeaponComp = GetOwner<ABaseCharacter>()->GetShieldComponent();
	auto info = SupWeapon->GetItemInfo<FWeaponInformation>();
	if (info != nullptr)
	{
		// 보조무기 종류에 따라 class 설정
		if(info->WeaponType == EWeaponType::ARROW)
		{
			SupWeaponComp->SetChildActorClass(AWeaponActor::StaticClass());
		}
		else if(info->WeaponType == EWeaponType::SHIELD)
		{
			SupWeaponComp->SetChildActorClass(AShieldActor::StaticClass());
		}

		if(SupWeaponComp->GetChildActor() != nullptr)
		{
			auto supWeaponChildActor = SupWeaponComp->GetChildActor();
			// 보조무기 SkeletalMesh설정
			Cast<AEquipmentActor>(supWeaponChildActor)->GetSkeletalMesh()->SetSkeletalMesh(info->equipmentMesh);

			// 화살 종류이면 Actor Visible을 꺼준다 -> 화살을 쏠 때만 켜줄 것
			if (info->WeaponType == EWeaponType::ARROW)
				supWeaponChildActor->SetActorHiddenInGame(true);

			// 무기 종류에 따라 Socket위치 설정
			ABaseCharacter* character = Cast<ABaseCharacter>(GetOwner());
			if (character != nullptr)
			{
				SupWeaponComp->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, info->equipSocketName);
			}
		}
	}

}


void UEquipmentComponent::EquipWeapon(int32 weaponIndex)
{
	UnEquipWeapon();

	auto weapon = weaponList[weaponIndex];
	if(weapon != nullptr)
	{
		equippedWeapon = weapon;

		class UChildActorComponent* weaponComp = GetOwner<ABaseCharacter>()->GetWeaponComponent();
		auto weaponChildActor = weaponComp->GetChildActor();
		if (weaponChildActor == nullptr)
		{
			weaponComp->SetChildActorClass(AWeaponActor::StaticClass());
		}
		weaponChildActor = weaponComp->GetChildActor();
		Cast<AWeaponActor>(weaponChildActor)->GetSkeletalMesh()->SetSkeletalMesh(weapon->GetItemInfo<FWeaponInformation>()->equipmentMesh);

		APlayerCharacter* player = Cast<APlayerCharacter>(GetOwner());
		auto weaponInfo = weapon->GetItemInfo<FWeaponInformation>();
		if (weaponInfo != nullptr)
		{
			// 플레이어 일 때 
			if (player != nullptr)
			{
				// 무기에 따른 애니메이션 설정
				player->GetMesh()->SetAnimClass(weaponInfo->weaponAnimationBP->GetAnimBlueprintGeneratedClass());
				player->SetAttackMontage(weaponInfo->attackMontage);
				player->SetHitMontage(weaponInfo->hitMontage);

				// 스텟 변동
				player->GetStatusComponent()->AddStat(weapon->GetStat());

				// 무기에 따른 소켓설정
				weaponComp->AttachToComponent(player->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, weaponInfo->equipSocketName);

				// 무기에 따른 스킬 설정
				for (auto skill : weaponInfo->Weapon_Skills)
				{
					player->GetSkillComponent()->AddSkill(skill.GetDefaultObject());
				}
			}
			// AI일 때
			else
			{
				AHumanCharacter* character = Cast<AHumanCharacter>(GetOwner());
				if (character != nullptr)
				{
					// 애니메이션 설정
					character->GetMesh()->SetAnimClass(weaponInfo->weaponAnimationBP->GetAnimBlueprintGeneratedClass());
					character->SetAttackMontage(weaponInfo->attackMontage);
					character->SetHitMontage(weaponInfo->hitMontage);

					// 소켓 설정
					weaponComp->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, weaponInfo->equipSocketName);
				}
			}

			// 주무기에 맞는 보조무기 찾아서 장착
			for (auto subWeapon : weaponList)
			{
				if(subWeapon != nullptr)
				{
					auto subWeaponInfo = subWeapon->GetItemInfo<FWeaponInformation>();
					if (subWeaponInfo != nullptr)
					{
						if (!subWeaponInfo->isMainWeapon)
						{
							// 무기List중에 주무기에 맞는 보조 무기 찾기
							if (weaponInfo->WeaponType == EWeaponType::ONEHAND)
							{
								if (subWeaponInfo->WeaponType == EWeaponType::SHIELD)
								{
									EquipSupWeapon(subWeapon);	// 보조무기 장착
									break;
								}
							}
							else if (weaponInfo->WeaponType == EWeaponType::BOW)
							{
								if (subWeaponInfo->WeaponType == EWeaponType::ARROW)
								{
									EquipSupWeapon(subWeapon);	// 보조무기 장착
									break;
								}
							}
						}
					}
				}
			}
			OnChangeWeapon.Broadcast(*weaponInfo);
		}
	}
}

void UEquipmentComponent::UnEquipWeapon()
{
	if(equippedWeapon != nullptr)
	{
		// 스텟 변동
		GetOwner<ABaseCharacter>()->GetStatusComponent()->MinusStat(equippedWeapon->GetStat());
	}
	equippedWeapon = nullptr;
	equippedSupWeapon = nullptr;

	// 메인무기 및 보조무기 ChildActorComponent 초기화
	class UChildActorComponent* weaponComp = GetOwner<ABaseCharacter>()->GetWeaponComponent();
	auto weaponChildActor = weaponComp->GetChildActor();
	if (weaponChildActor != nullptr)
	{
		weaponComp->SetChildActorClass(nullptr);
	}
	class UChildActorComponent* supweaponComp = GetOwner<ABaseCharacter>()->GetShieldComponent();
	auto supweaponChildActor = supweaponComp->GetChildActor();
	if (supweaponChildActor != nullptr)
	{
		supweaponComp->SetChildActorClass(nullptr);
	}

	// 스킬 초기화
	APlayerCharacter* player = Cast<APlayerCharacter>(GetOwner());
	if(player != nullptr)
	{
		player->GetSkillComponent()->RemoveAllSkill();
	}
}


void UEquipmentComponent::SetEquipComponentData(FEquipComponentSave EquipCompData)
{
	Helmet = EquipCompData.ArmorList[0];
	Cape = EquipCompData.ArmorList[1];
	Cloth = EquipCompData.ArmorList[2];
	Glove = EquipCompData.ArmorList[3];
	Shoes = EquipCompData.ArmorList[4];

	weaponList = EquipCompData.WeaponList;

	OnUpdateEquiment.Broadcast(this);
}

void UEquipmentComponent::SetBattleCharacter(UEquipmentComponent* EquipComp)
{
	if (GetOwner()->IsA<APlayerCharacter>())
	{
		auto battleCharcter = Cast<APlayerCharacter>(GetOwner());
		
		weaponList = EquipComp->GetWeaponList();
		if(EquipComp->GetHelmet() != nullptr)
		{
			battleCharcter->GetHelmetMesh()->SetSkeletalMesh(EquipComp->GetHelmet()->GetItemInfo<FArmorInformation>()->equipmentMesh);
		}
		if (EquipComp->GetCape() != nullptr)
		{
			battleCharcter->GetCapeMesh()->SetSkeletalMesh(EquipComp->GetCape()->GetItemInfo<FArmorInformation>()->equipmentMesh);
		}
		if (EquipComp->GetCloth() != nullptr)
		{
			battleCharcter->GetClothMesh()->SetSkeletalMesh(EquipComp->GetCloth()->GetItemInfo<FArmorInformation>()->equipmentMesh);
		}
	}
}
