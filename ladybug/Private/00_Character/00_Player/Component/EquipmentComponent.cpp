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

	for(auto weaponBP : weaponBPList)
	{
		AddWeaponList(weaponBP.GetDefaultObject());
	}

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
		while (true)
		{
			curWeaponIndex = isUp ? curWeaponIndex + 1 : curWeaponIndex - 1;
			curWeaponIndex = (curWeaponIndex + 4) % 4;
			if (weaponList[curWeaponIndex] != nullptr)
			{
				if (weaponList[curWeaponIndex]->GetItemInfo<FWeaponInformation>()->isMainWeapon)
				{
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
			OnUpdateEquiment.Broadcast(this);
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
		if(!owningPlayer->GetInventoryComponent()->IsFull())
		{
			owningPlayer->GetInventoryComponent()->AddItem(weaponList[index]);
			weaponList[index] = nullptr;
			OnUpdateEquiment.Broadcast(this);
		}
	}
}



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
	
	
}

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
	UnEquipCape();

	Cape = armor;
	if (Cape != nullptr)
	{
		auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
		if (owningPlayer != nullptr)
		{
			if (!owningPlayer->GetInventoryComponent()->IsFull())
			{
				owningPlayer->GetStatusComponent()->AddStat(Cape->GetStat());
				OnUpdateEquiment.Broadcast(this);
				OnChangeEquipment.Broadcast(GetOwner<AWorldPlayerCharacter>()->GetStatusComponent());
			}
		}
	}
}

void UEquipmentComponent::EquipCloth(UArmor* armor)
{
	UnEquipCloth();

	Cloth = armor;
	if (Cloth != nullptr)
	{
		auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
		if (owningPlayer != nullptr)
		{
			if (!owningPlayer->GetInventoryComponent()->IsFull())
			{
				owningPlayer->GetStatusComponent()->AddStat(Cloth->GetStat());
				OnUpdateEquiment.Broadcast(this);
				OnChangeEquipment.Broadcast(GetOwner<AWorldPlayerCharacter>()->GetStatusComponent());
			}
		}
	}
}

void UEquipmentComponent::EquipGlove(UArmor* armor)
{
	UnEquipGlove();

	Glove = armor;
	if (Glove != nullptr)
	{
		auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
		if (owningPlayer != nullptr)
		{
			if (!owningPlayer->GetInventoryComponent()->IsFull())
			{
				owningPlayer->GetStatusComponent()->AddStat(Glove->GetStat());
				OnUpdateEquiment.Broadcast(this);
				OnChangeEquipment.Broadcast(GetOwner<AWorldPlayerCharacter>()->GetStatusComponent());
			}
		}
	}
}

void UEquipmentComponent::EquipShoes(UArmor* armor)
{
	UnEquipShoes();

	Shoes = armor;
	if (Shoes != nullptr)
	{
		auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
		if (owningPlayer != nullptr)
		{
			if (!owningPlayer->GetInventoryComponent()->IsFull())
			{
				owningPlayer->GetStatusComponent()->AddStat(Shoes->GetStat());
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
	if (Cape != nullptr)
	{
		auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
		if (owningPlayer != nullptr)
		{
			if (!owningPlayer->GetInventoryComponent()->IsFull())
			{
				owningPlayer->GetStatusComponent()->MinusStat(Cape->GetStat());
				owningPlayer->GetInventoryComponent()->AddItem(Cape);
				Cape = nullptr;
				OnChangeEquipment.Broadcast(GetOwner<AWorldPlayerCharacter>()->GetStatusComponent());
				OnUpdateEquiment.Broadcast(this);
			}
		}
	}
}

void UEquipmentComponent::UnEquipCloth()
{
	if (Cloth != nullptr)
	{
		auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
		if (owningPlayer != nullptr)
		{
			if (!owningPlayer->GetInventoryComponent()->IsFull())
			{
				owningPlayer->GetStatusComponent()->MinusStat(Cloth->GetStat());
				owningPlayer->GetInventoryComponent()->AddItem(Cloth);
				Cloth = nullptr;
				OnChangeEquipment.Broadcast(GetOwner<AWorldPlayerCharacter>()->GetStatusComponent());
				OnUpdateEquiment.Broadcast(this);
			}
		}
	}
}

void UEquipmentComponent::UnEquipGlove()
{
	if (Glove != nullptr)
	{
		auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
		if (owningPlayer != nullptr)
		{
			if (!owningPlayer->GetInventoryComponent()->IsFull())
			{
				owningPlayer->GetStatusComponent()->MinusStat(Glove->GetStat());
				owningPlayer->GetInventoryComponent()->AddItem(Glove);
				Glove = nullptr;
				OnChangeEquipment.Broadcast(GetOwner<AWorldPlayerCharacter>()->GetStatusComponent());
				OnUpdateEquiment.Broadcast(this);
			}
		}
	}
}

void UEquipmentComponent::UnEquipShoes()
{
	if (Shoes != nullptr)
	{
		auto owningPlayer = GetOwner<AWorldPlayerCharacter>();
		if (owningPlayer != nullptr)
		{
			if (!owningPlayer->GetInventoryComponent()->IsFull())
			{
				owningPlayer->GetStatusComponent()->MinusStat(Shoes->GetStat());
				owningPlayer->GetInventoryComponent()->AddItem(Shoes);
				Shoes = nullptr;
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
			Cast<AEquipmentActor>(supWeaponChildActor)->GetSkeletalMesh()->SetSkeletalMesh(info->equipmentMesh);

			if (info->WeaponType == EWeaponType::ARROW)
			{
				supWeaponChildActor->SetActorHiddenInGame(true);
			}

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
			if (player != nullptr)
			{
				player->GetMesh()->SetAnimClass(weaponInfo->weaponAnimationBP->GetAnimBlueprintGeneratedClass());
				player->SetAttackMontage(weaponInfo->attackMontage);
				player->SetHitMontage(weaponInfo->hitMontage);
				player->GetStatusComponent()->AddStat(weapon->GetStat());

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
					character->SetHitMontage(weaponInfo->hitMontage);

					weaponComp->AttachToComponent(character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, weaponInfo->equipSocketName);
				}
			}

			for (auto subWeapon : weaponList)
			{
				if(subWeapon != nullptr)
				{
					auto subWeaponInfo = subWeapon->GetItemInfo<FWeaponInformation>();
					if (subWeaponInfo != nullptr)
					{
						if (!subWeaponInfo->isMainWeapon)
						{
							if (weaponInfo->WeaponType == EWeaponType::ONEHAND)
							{

								if (subWeaponInfo->WeaponType == EWeaponType::SHIELD)
								{

									EquipSupWeapon(subWeapon);
									break;
								}
							}
							else if (weaponInfo->WeaponType == EWeaponType::BOW)
							{
								if (subWeaponInfo->WeaponType == EWeaponType::ARROW)
								{
									EquipSupWeapon(subWeapon);
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
		GetOwner<ABaseCharacter>()->GetStatusComponent()->MinusStat(equippedWeapon->GetStat());
	}
	equippedWeapon = nullptr;
	equippedSupWeapon = nullptr;

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
