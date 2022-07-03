// Fill out your copyright notice in the Description page of Project Settings.

#include "99_GameMode/00_GameState/BattleGameState.h"
#include "99_GameMode/BattleGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "98_GameInstance/myGameInstance.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "00_Character/02_Component/SkillComponent.h"
#include "02_Item/Item.h"
#include "02_Item/00_Equipment/Equipment.h"
#include "02_Item/00_Equipment/Weapon.h"
#include "02_Item/00_Equipment/00_Armor/Armor.h"

void ABattleGameState::AddDeadMyArmy(class ABaseCharacter* unit)
{
	deadMyArmy.Emplace(unit);
	myArmy.Remove(unit);
	if(myArmy.Num() <= 0)
	{
		Cast<ABattleGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->SetGameState(EGameState::LOSE);
	}
}
void ABattleGameState::AddDeadEnemy(class ABaseCharacter* unit)
{
	deadEnemy.Emplace(unit);
	enemyArmy.Remove(unit);

	auto gameInstance = GetGameInstance<UmyGameInstance>();
	const auto info = gameInstance->GetMonsterInfo(Cast<AMonsterBaseCharacter>(unit)->GetMonsterTag());
	if(info != nullptr)
	{
		for (auto item : info->monster_Dropitem)
		{
			float randValue = FMath::RandRange(1.f, 10.f);
			
			if(randValue <= item.dropPercentage)
			{
				auto itemClass = item.dropItem;
				UItem* lootItem = NewObject<UItem>();
				if (itemClass.GetDefaultObject()->IsA<UWeapon>())
				{
					lootItem = NewObject<UWeapon>(gameInstance, NAME_None, RF_NoFlags, itemClass.GetDefaultObject(), true);
				}
				else if (itemClass.GetDefaultObject()->IsA<UArmor>())
				{
					lootItem = NewObject<UArmor>(gameInstance, NAME_None, RF_NoFlags, itemClass.GetDefaultObject(), true);
				}
				else
				{
					lootItem = NewObject<UItem>(gameInstance, NAME_None, RF_NoFlags, itemClass.GetDefaultObject(), true);
				}
				lootItem->ItemStatSetUp();
				gameInstance->lootItemList.Emplace(lootItem);
			}
			
		}
	}
	
	if (enemyArmy.Num() <= 0)
	{
		auto gameMode = Cast<ABattleGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		gameMode->SetGameState(EGameState::VICTORY);
	}
}

void ABattleGameState::RemoveTimer()
{
	for (auto unit : myArmy)
	{
		unit->GetSkillComponent()->RemoveSkillTimer();
	}
	for (auto unit : enemyArmy)
	{
		unit->GetSkillComponent()->RemoveSkillTimer();

	}
	for (auto unit : deadMyArmy)
	{
		unit->GetSkillComponent()->RemoveSkillTimer();

	}
	for (auto unit : deadEnemy)
	{
		unit->GetSkillComponent()->RemoveSkillTimer();

	}
}
