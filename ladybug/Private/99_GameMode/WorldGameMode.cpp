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
		// 커서 및 입력모드 설정 -> 마우스로 캐릭터 이동
		controller->SetInputMode(FInputModeGameAndUI());
		controller->SetShowMouseCursor(true);

		// 데이터 불러오기
		LoadWorld();
	}
}
void AWorldGameMode::OpenBattleLevel(class AWorldMonsterCharacter* BattleTarget)
{
	// 데이터 저장
	SaveWorld(BattleTarget);

	// 현재 내가 어느 지형에 위치했는지 확인 -> 눈위에 있으면 눈맵으로 이동, 초원이면 초원 맵으로 이동
	// 타겟의 아래 방향으로 Ray를 쏴서 SurfaceType을 확인한다.
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
			// 숲 전장으로 이동
			UGameplayStatics::OpenLevel(GetWorld(), "BattleLevel_Forest");
			break;
		}
		case EPhysicalSurface::SurfaceType2:
		{
			// 눈오는 전장으로 이동
			UGameplayStatics::OpenLevel(GetWorld(), "BattleLevel_Winter");
			break;
		}
		case EPhysicalSurface::SurfaceType3:
		{
			break;
		}
		default:
			// 기본값으로 숲 전장으로 이동
			UGameplayStatics::OpenLevel(GetWorld(), "BattleLevel_Forest");
			break;
		}
	}
	else
	{
		// 기본값으로 숲 전장으로 이동
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
		// WorldLevel에 있는 몬스터들 정보를 담은 List를 초기화한다.
		gameInstance->GetMonsterData().Empty();

		// Level에 있는 WorldCharacter들을 찾고 데이터들을 저장한다.
		TArray<AActor*> units;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWorldBaseCharacter::StaticClass(), units);
		for (auto unit : units)
		{
			// 몬스터라면
			if (unit->IsA<AWorldMonsterCharacter>())
			{
				for (int i = 0; i < 100; i++)
				{
					// 몬스터에 고유 인덱스를 할당하고 현재 몬스터의 위치 및 여러 데이터를 List에 저장한다. 
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
			// 플레이어 라면
			else if (unit->IsA<AWorldPlayerCharacter>())
			{
				// 플레이어의 위치 및 여러 데이터를 저장한다.
				auto playerUnit = Cast<AWorldPlayerCharacter>(unit);
				FSaveCharacterData unitData(playerUnit);
				unitData.CharacterLocation = playerUnit->GetActorLocation();
				gameInstance->SetPlayerData(unitData);
				gameInstance->lootItemList.Reset();
			}
		}
		// 현재 들어가는 마을의 TagName을 저장한다.
		gameInstance->SetVillageTagName(VillageTagName);
	}
}

void AWorldGameMode::SaveWorld(class AWorldMonsterCharacter* BattleTarget)
{
	auto gameInstance = Cast<UmyGameInstance>(GetGameInstance());
	if(gameInstance != nullptr)
	{
		// WorldLevel에 있는 몬스터들 정보를 담은 List를 초기화한다.
		gameInstance->GetMonsterData().Empty();

		// Level에 있는 WorldCharacter들을 찾고 데이터들을 저장한다.
		TArray<AActor*> units;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWorldBaseCharacter::StaticClass(), units);
		for (auto unit : units)
		{
			// 몬스터라면
			if (unit->IsA<AWorldMonsterCharacter>())
			{
				for(int i = 0; i < 100; i++)
				{
					// 몬스터에 고유 인덱스를 할당하고 현재 몬스터의 위치 및 여러 데이터를 List에 저장한다. 
					if(!gameInstance->GetMonsterData().Contains(i))
					{
						auto monsterUnit = Cast<AWorldMonsterCharacter>(unit);
						FSaveCharacterData unitData(i, monsterUnit);
						unitData.CharacterLocation = monsterUnit->GetActorLocation();

						gameInstance->AddMonsterData(unitData.CharacterIndex, unitData);

						// 전투하는 적은 따로 저장을 해준다.
						if (monsterUnit == BattleTarget)
						{
							gameInstance->SetTargetData(unitData);
						}
						break;
					}
				}
			}
			// 플레이어 라면
			else if (unit->IsA<AWorldPlayerCharacter>())
			{
				// 플레이어의 위치 및 여러 데이터를 저장한다.
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
		// 처음 게임 시작은 제외하려고
		if (!gameInstance->GetPlayerData().IsEmpty())
		{
			TArray<class AActor*> units;
			UGameplayStatics::GetAllActorsOfClass(this, AWorldBaseCharacter::StaticClass(), units);

			TArray<class AActor*> locations;
			UGameplayStatics::GetAllActorsOfClass(this, AMonsterSpawnActor::StaticClass(), locations);

			// 현재 Level에 있는 모든 WorldCharacter 삭제
			for (auto monster : units)
			{
				monster->Destroy();
			}

			// 저장되어 있는 몬스터 데이터들을 이용하여 WorldCharacter들을 소환해준다.
			for (auto monsterData : gameInstance->GetMonsterData())
			{
				// 저장되어 있는 정보를 이용하여 원래 있던 위치에 몬스터를 소환한다.
				auto worldMonster = GetWorld()->SpawnActor<AWorldMonsterCharacter>(monsterData.Value.WorldCharacterClass, monsterData.Value.CharacterLocation, FRotator::ZeroRotator);
				// 몬스터의 정보를 이용하여 데이터를 SetUp한다.
				worldMonster->SetCharacterData(monsterData.Value);

				// 몬스터를 관리하는 Actor에 넣어준다.
				for(auto location : locations)
				{
					auto locationActor = Cast<AMonsterSpawnActor>(location);
					if(worldMonster->GetSpawnLocationIndex() == locationActor->GetLocationIndex())
					{
						locationActor->AddMonster(worldMonster);
					}
				}
			}

			// 플레이어를 소환하고 컨트롤러를 할당한다.
			auto player = GetWorld()->SpawnActor<AWorldPlayerCharacter>(gameInstance->GetPlayerData().WorldCharacterClass, gameInstance->GetPlayerData().CharacterLocation, FRotator::ZeroRotator);
			controller->Possess(player);
			// 플레이어의 데이터를 SetUp한다.
			player->SetCharacterData(gameInstance->GetPlayerData());
		}
	}
}
