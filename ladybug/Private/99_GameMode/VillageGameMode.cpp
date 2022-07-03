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
		// Level�� �ִ� ��� ATargetPoint Actor�� �����´�.
		TArray<class AActor*> temp;
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), temp);
		for (AActor* location : temp)
		{
			// ������ TargetPoint �߿��� ���� �ش�Ǵ� TargetPoint�� ã�´�.
			// �÷��̾ ��ȯ�� ��ġ
			if (location->GetName().Equals(playerSpawnLocation))
			{
				auto playerData = gameInstance->GetPlayerData();
				if(!playerData.IsEmpty())
				{
					if (playerData.WorldCharacterClass != nullptr)
					{
						// �÷��̾��� WorldCharacter�� ��ȯ�ϰ� �ν��Ͻ��� ������ �����͸� �־��ش�.
						worldPlayer = GetWorld()->SpawnActor<AWorldPlayerCharacter>(playerData.WorldCharacterClass, location->GetActorLocation(), location->GetActorRotation());
						worldPlayer->SetCharacterData(playerData);
						worldPlayer->SetActorHiddenInGame(true);		// WorldCharacter�� Level���� �����ش�.

						// �÷��̾��� BattleCharacter�� ��ȯ�ϰ� ��Ʈ�ѷ��� �Ҵ��Ѵ�.
						battlePlayer = GetWorld()->SpawnActor<APlayerCharacter>(worldPlayer->GetCharacter(), location->GetActorLocation(), location->GetActorRotation());
						controller->Possess(battlePlayer);

						battlePlayer->SetWorldBaseCharacter(worldPlayer); // ���߿� ��ü�� �����ؼ� �κ��̳� ��� �ʿ��� �����͸� ����������
						battlePlayer->SetGenericTeamId(worldPlayer->GetGenericTeamId());
					}
				}
			}
			// ���ֻ��� NPC�� ��ȯ�� ��ġ
			else if (location->GetName().Equals(unitShopNPCLocation))
			{
				if (!gameInstance->GetVillageTagName().IsNone())
				{
					// DataTabel�� �ִ� ���� ������ �̿��Ͽ� NPC�� SetUp�Ѵ�.
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
			// ������ NPC�� ��ȯ�� ��ġ
			else if (location->GetName().Equals(EquipmentShopNPCLocation))
			{
				if (!gameInstance->GetVillageTagName().IsNone())
				{
					// DataTabel�� �ִ� ���� ������ �̿��Ͽ� NPC�� SetUp�Ѵ�.
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
	// �÷��̾��� ������ GameInstance�� �����Ѵ�.
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
	SaveWorld();		// �����͸� �����Ѵ�.
	// WorldLevel�� �̵��Ѵ�.
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("WorldLevel"));
}
