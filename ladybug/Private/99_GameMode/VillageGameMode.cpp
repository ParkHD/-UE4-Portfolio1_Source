// Fill out your copyright notice in the Description page of Project Settings.


#include "99_GameMode/VillageGameMode.h"

#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include "00_Character/00_Player/CustomController.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"
#include "98_GameInstance/myGameInstance.h"
#include "Engine/TargetPoint.h"

void AVillageGameMode::StartPlay()
{
	Super::StartPlay();

	controller = Cast<ACustomController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetInputMode(FInputModeGameOnly());
	auto gameInstance = Cast<UmyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gameInstance != nullptr)
	{
		// Level에 있는 모든 ATargetPoint Actor를 가져온다.
		TArray<class AActor*> temp;
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), temp);
		for (AActor* location : temp)
		{
			// 가져온 TargetPoint 중에서 각각 해당되는 TargetPoint를 찾는다.
			// 플레이어가 소환될 위치
			if (location->GetName().Equals(playerSpawnLocation))
			{
				auto playerData = gameInstance->GetPlayerData();
				if(!playerData.IsEmpty())
				{
					if (playerData.WorldCharacterClass != nullptr)
					{
						// 플레이어의 WorldCharacter를 소환하고 인스턴스에 저장한 데이터를 넣어준다.
						worldPlayer = GetWorld()->SpawnActor<AWorldPlayerCharacter>(playerData.WorldCharacterClass, location->GetActorLocation(), location->GetActorRotation());
						worldPlayer->SetCharacterData(playerData);
						worldPlayer->SetActorHiddenInGame(true);		// WorldCharacter를 Level에서 숨겨준다.

						// 플레이어의 BattleCharacter를 소환하고 컨트롤러를 할당한다.
						battlePlayer = GetWorld()->SpawnActor<APlayerCharacter>(worldPlayer->GetCharacter(), location->GetActorLocation(), location->GetActorRotation());
						controller->Possess(battlePlayer);

						battlePlayer->SetWorldBaseCharacter(worldPlayer); // 나중에 본체에 접근해서 인벤이나 등등 필요한 데이터를 가져오려고
						battlePlayer->SetGenericTeamId(worldPlayer->GetGenericTeamId());
					}
				}
			}
			// 유닛상점 NPC가 소환될 위치
			else if (location->GetName().Equals(unitShopNPCLocation))
			{
				if (!gameInstance->GetVillageTagName().IsNone())
				{
					// DataTabel에 있는 마을 정보를 이용하여 NPC를 SetUp한다.
					auto villageInfo = gameInstance->GetVillageInfo(gameInstance->GetVillageTagName());
					if (villageInfo != nullptr)
					{
						auto NPC = GetWorld()->SpawnActor<ANPCCharacter>(npcCharacter, location->GetActorLocation(), location->GetActorRotation());
						auto npcInfo = gameInstance->GetNPCInfo(villageInfo->village_NPCList[0].GetTagName());
						if (npcInfo != nullptr)
						{
							NPC->SetUp(*npcInfo);
						}
					}
				}
			}
			// 장비상점 NPC가 소환될 위치
			else if (location->GetName().Equals(EquipmentShopNPCLocation))
			{
				if (!gameInstance->GetVillageTagName().IsNone())
				{
					// DataTabel에 있는 마을 정보를 이용하여 NPC를 SetUp한다.
					auto villageInfo = gameInstance->GetVillageInfo(gameInstance->GetVillageTagName());
					if (villageInfo != nullptr)
					{
						auto NPC = GetWorld()->SpawnActor<ANPCCharacter>(npcCharacter, location->GetActorLocation(), location->GetActorRotation());
						auto npcInfo = gameInstance->GetNPCInfo(villageInfo->village_NPCList[1].GetTagName());
						if (npcInfo != nullptr)
						{
							NPC->SetUp(*npcInfo);
						}
					}
				}
			}
		}
	}
}
void AVillageGameMode::SaveWorld()
{
	// 플레이어의 정보를 GameInstance에 저장한다.
	FSaveCharacterData playerData(worldPlayer);
	auto gameInstance = GetGameInstance<UmyGameInstance>();
	if (gameInstance != nullptr)
	{
		playerData.CharacterLocation = gameInstance->GetPlayerData().CharacterLocation;
		gameInstance->SetPlayerData(playerData);
	}
}

void AVillageGameMode::OpenWorldLevel()
{
	SaveWorld();		// 데이터를 저장한다.
	// WorldLevel로 이동한다.
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("WorldLevel"));
}
