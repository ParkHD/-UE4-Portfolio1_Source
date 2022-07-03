// Fill out your copyright notice in the Description page of Project Settings.


#include "99_GameMode/WorldGameMode.h"

#include "00_Character/02_Component/ArmyComponent.h"
#include "10_WorldCharacter/00_Player/WorldPlayerController.h"
#include "10_WorldCharacter/WorldBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "98_GameInstance/myGameInstance.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"
#include "10_WorldCharacter/01_Monster/WorldMonsterCharacter.h"
#include "02_Item/Item.h"
#include "10_WorldCharacter/99_World/MonsterSpawnActor.h"


void AWorldGameMode::StartPlay()
{
	Super::StartPlay();
	controller = Cast<AWorldPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(controller != nullptr)
	{
		controller->SetInputMode(FInputModeGameAndUI());
		controller->SetShowMouseCursor(true);

		LoadWorld();
	}
}
void AWorldGameMode::OpenBattleLevel(class AWorldMonsterCharacter* BattleTarget)
{
	SaveWorld(BattleTarget);
	FVector start = BattleTarget->GetActorLocation();
	FVector end = start - BattleTarget->GetActorUpVector() * 300.f;
	TArray<TEnumAsByte<EObjectTypeQuery>> objects;
	objects.Emplace(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	TArray<AActor*> ignoreActors;
	FHitResult Hit;
	ignoreActors.Emplace(BattleTarget);
	if(UKismetSystemLibrary::LineTraceSingleForObjects(
		GetWorld(),
		start,
		end,
		objects,
		false,
		ignoreActors,
		EDrawDebugTrace::ForOneFrame,
		Hit,
		true))
	{
		switch (UGameplayStatics::GetSurfaceType(Hit))
		{
		case EPhysicalSurface::SurfaceType1:
		{

			UGameplayStatics::OpenLevel(GetWorld(), "BattleLevel_Forest");
			break;
		}
		case EPhysicalSurface::SurfaceType2:
		{

			UGameplayStatics::OpenLevel(GetWorld(), "BattleLevel_Winter");
			break;
		}
		case EPhysicalSurface::SurfaceType3:
		{
			
			break;
		}
		default:
			UGameplayStatics::OpenLevel(GetWorld(), "BattleLevel_Forest");
			break;
		}
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), "BattleLevel_Forest");
	}
}

void AWorldGameMode::OpenVillageLevel(FName VillageTagName)
{
	SaveWorld(VillageTagName);
	UGameplayStatics::OpenLevel(GetWorld(), "VillageLevel");
}

void AWorldGameMode::SaveWorld(FName VillageTagName)
{
	auto gameInstance = Cast<UmyGameInstance>(GetGameInstance());
	if (gameInstance != nullptr)
	{
		gameInstance->GetMonsterData().Empty();

		TArray<AActor*> units;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWorldBaseCharacter::StaticClass(), units);
		for (auto unit : units)
		{
			if (unit->IsA<AWorldMonsterCharacter>())
			{
				for (int i = 0; i < 100; i++)
				{
					if (!gameInstance->GetMonsterData().Contains(i))
					{
						auto monsterUnit = Cast<AWorldMonsterCharacter>(unit);
						FSaveCharacterData unitData(i, monsterUnit);
						unitData.CharacterLocation = monsterUnit->GetActorLocation();

						gameInstance->AddMonsterData(unitData.CharacterIndex, unitData);
						break;
					}
				}
			}
			else if (unit->IsA<AWorldPlayerCharacter>())
			{
				auto playerUnit = Cast<AWorldPlayerCharacter>(unit);
				FSaveCharacterData unitData(playerUnit);
				unitData.CharacterLocation = playerUnit->GetActorLocation();
				gameInstance->SetPlayerData(unitData);
				gameInstance->lootItemList.Reset();
				//UKismetSystemLibrary::PrintString(GetWorld(), *gameInstance->GetPlayerData().WorldCharacterClass->GetName(), true, true, FLinearColor::Green, 2.f);

			}
		}
		gameInstance->SetVillageTagName(VillageTagName);
	}
}

void AWorldGameMode::SaveWorld(class AWorldMonsterCharacter* BattleTarget)
{
	auto gameInstance = Cast<UmyGameInstance>(GetGameInstance());
	if(gameInstance != nullptr)
	{
		gameInstance->GetMonsterData().Empty();

		TArray<AActor*> units;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWorldBaseCharacter::StaticClass(), units);
		for (auto unit : units)
		{
			if (unit->IsA<AWorldMonsterCharacter>())
			{
				for(int i = 0; i < 100; i++)
				{
					if(!gameInstance->GetMonsterData().Contains(i))
					{
						auto monsterUnit = Cast<AWorldMonsterCharacter>(unit);
						FSaveCharacterData unitData(i, monsterUnit);
						unitData.CharacterLocation = monsterUnit->GetActorLocation();

						gameInstance->AddMonsterData(unitData.CharacterIndex, unitData);

						if (monsterUnit == BattleTarget)
						{
							gameInstance->SetTargetData(unitData);
						}
						break;
					}
				}
			}
			else if (unit->IsA<AWorldPlayerCharacter>())
			{
				auto playerUnit = Cast<AWorldPlayerCharacter>(unit);
				FSaveCharacterData unitData(playerUnit);
				unitData.CharacterLocation = playerUnit->GetActorLocation();
				gameInstance->SetPlayerData(unitData);
				gameInstance->lootItemList.Reset();
			}
		}
	}
}

void AWorldGameMode::LoadWorld()
{
	auto gameInstance = Cast<UmyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gameInstance != nullptr)
	{
		// 처음 시작은 제외하려고
		if (!gameInstance->GetPlayerData().IsEmpty())
		{
			TArray<class AActor*> units;
			UGameplayStatics::GetAllActorsOfClass(this, AWorldBaseCharacter::StaticClass(), units);

			TArray<class AActor*> locations;
			UGameplayStatics::GetAllActorsOfClass(this, AMonsterSpawnActor::StaticClass(), locations);

			for (auto monster : units)
			{
				monster->Destroy();
			}

			for (auto monsterData : gameInstance->GetMonsterData())
			{
				auto worldMonster = GetWorld()->SpawnActor<AWorldMonsterCharacter>(monsterData.Value.WorldCharacterClass, monsterData.Value.CharacterLocation, FRotator::ZeroRotator);
				worldMonster->SetCharacterData(monsterData.Value);
				for(auto location : locations)
				{
					auto locationActor = Cast<AMonsterSpawnActor>(location);
					if(worldMonster->GetSpawnLocationIndex() == locationActor->GetLocationIndex())
					{
						locationActor->AddMonster(worldMonster);
					}
				}
			}

			auto player = GetWorld()->SpawnActor<AWorldPlayerCharacter>(gameInstance->GetPlayerData().WorldCharacterClass, gameInstance->GetPlayerData().CharacterLocation, FRotator::ZeroRotator);

			controller->Possess(player);
			player->SetCharacterData(gameInstance->GetPlayerData());
		}
	}
}
