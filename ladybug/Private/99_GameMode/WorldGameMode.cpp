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
		// Ŀ�� �� �Է¸�� ���� -> ���콺�� ĳ���� �̵�
		controller->SetInputMode(FInputModeGameAndUI());
		controller->SetShowMouseCursor(true);

		// ������ �ҷ�����
		LoadWorld();
	}
}
void AWorldGameMode::OpenBattleLevel(class AWorldMonsterCharacter* BattleTarget)
{
	// ������ ����
	SaveWorld(BattleTarget);

	// ���� ���� ��� ������ ��ġ�ߴ��� Ȯ�� -> ������ ������ �������� �̵�, �ʿ��̸� �ʿ� ������ �̵�
	// Ÿ���� �Ʒ� �������� Ray�� ���� SurfaceType�� Ȯ���Ѵ�.
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
			// �� �������� �̵�
			UGameplayStatics::OpenLevel(GetWorld(), "BattleLevel_Forest");
			break;
		}
		case EPhysicalSurface::SurfaceType2:
		{
			// ������ �������� �̵�
			UGameplayStatics::OpenLevel(GetWorld(), "BattleLevel_Winter");
			break;
		}
		case EPhysicalSurface::SurfaceType3:
		{
			break;
		}
		default:
			// �⺻������ �� �������� �̵�
			UGameplayStatics::OpenLevel(GetWorld(), "BattleLevel_Forest");
			break;
		}
	}
	else
	{
		// �⺻������ �� �������� �̵�
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
		// WorldLevel�� �ִ� ���͵� ������ ���� List�� �ʱ�ȭ�Ѵ�.
		gameInstance->GetMonsterData().Empty();

		// Level�� �ִ� WorldCharacter���� ã�� �����͵��� �����Ѵ�.
		TArray<AActor*> units;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWorldBaseCharacter::StaticClass(), units);
		for (auto unit : units)
		{
			// ���Ͷ��
			if (unit->IsA<AWorldMonsterCharacter>())
			{
				for (int i = 0; i < 100; i++)
				{
					// ���Ϳ� ���� �ε����� �Ҵ��ϰ� ���� ������ ��ġ �� ���� �����͸� List�� �����Ѵ�. 
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
			// �÷��̾� ���
			else if (unit->IsA<AWorldPlayerCharacter>())
			{
				// �÷��̾��� ��ġ �� ���� �����͸� �����Ѵ�.
				auto playerUnit = Cast<AWorldPlayerCharacter>(unit);
				FSaveCharacterData unitData(playerUnit);
				unitData.CharacterLocation = playerUnit->GetActorLocation();
				gameInstance->SetPlayerData(unitData);
				gameInstance->lootItemList.Reset();
			}
		}
		// ���� ���� ������ TagName�� �����Ѵ�.
		gameInstance->SetVillageTagName(VillageTagName);
	}
}

void AWorldGameMode::SaveWorld(class AWorldMonsterCharacter* BattleTarget)
{
	auto gameInstance = Cast<UmyGameInstance>(GetGameInstance());
	if(gameInstance != nullptr)
	{
		// WorldLevel�� �ִ� ���͵� ������ ���� List�� �ʱ�ȭ�Ѵ�.
		gameInstance->GetMonsterData().Empty();

		// Level�� �ִ� WorldCharacter���� ã�� �����͵��� �����Ѵ�.
		TArray<AActor*> units;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWorldBaseCharacter::StaticClass(), units);
		for (auto unit : units)
		{
			// ���Ͷ��
			if (unit->IsA<AWorldMonsterCharacter>())
			{
				for(int i = 0; i < 100; i++)
				{
					// ���Ϳ� ���� �ε����� �Ҵ��ϰ� ���� ������ ��ġ �� ���� �����͸� List�� �����Ѵ�. 
					if(!gameInstance->GetMonsterData().Contains(i))
					{
						auto monsterUnit = Cast<AWorldMonsterCharacter>(unit);
						FSaveCharacterData unitData(i, monsterUnit);
						unitData.CharacterLocation = monsterUnit->GetActorLocation();

						gameInstance->AddMonsterData(unitData.CharacterIndex, unitData);

						// �����ϴ� ���� ���� ������ ���ش�.
						if (monsterUnit == BattleTarget)
						{
							gameInstance->SetTargetData(unitData);
						}
						break;
					}
				}
			}
			// �÷��̾� ���
			else if (unit->IsA<AWorldPlayerCharacter>())
			{
				// �÷��̾��� ��ġ �� ���� �����͸� �����Ѵ�.
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
		// ó�� ���� ������ �����Ϸ���
		if (!gameInstance->GetPlayerData().IsEmpty())
		{
			TArray<class AActor*> units;
			UGameplayStatics::GetAllActorsOfClass(this, AWorldBaseCharacter::StaticClass(), units);

			TArray<class AActor*> locations;
			UGameplayStatics::GetAllActorsOfClass(this, AMonsterSpawnActor::StaticClass(), locations);

			// ���� Level�� �ִ� ��� WorldCharacter ����
			for (auto monster : units)
			{
				monster->Destroy();
			}

			// ����Ǿ� �ִ� ���� �����͵��� �̿��Ͽ� WorldCharacter���� ��ȯ���ش�.
			for (auto monsterData : gameInstance->GetMonsterData())
			{
				// ����Ǿ� �ִ� ������ �̿��Ͽ� ���� �ִ� ��ġ�� ���͸� ��ȯ�Ѵ�.
				auto worldMonster = GetWorld()->SpawnActor<AWorldMonsterCharacter>(monsterData.Value.WorldCharacterClass, monsterData.Value.CharacterLocation, FRotator::ZeroRotator);
				// ������ ������ �̿��Ͽ� �����͸� SetUp�Ѵ�.
				worldMonster->SetCharacterData(monsterData.Value);

				// ���͸� �����ϴ� Actor�� �־��ش�.
				for(auto location : locations)
				{
					auto locationActor = Cast<AMonsterSpawnActor>(location);
					if(worldMonster->GetSpawnLocationIndex() == locationActor->GetLocationIndex())
					{
						locationActor->AddMonster(worldMonster);
					}
				}
			}

			// �÷��̾ ��ȯ�ϰ� ��Ʈ�ѷ��� �Ҵ��Ѵ�.
			auto player = GetWorld()->SpawnActor<AWorldPlayerCharacter>(gameInstance->GetPlayerData().WorldCharacterClass, gameInstance->GetPlayerData().CharacterLocation, FRotator::ZeroRotator);
			controller->Possess(player);
			// �÷��̾��� �����͸� SetUp�Ѵ�.
			player->SetCharacterData(gameInstance->GetPlayerData());
		}
	}
}
