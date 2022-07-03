// Fill out your copyright notice in the Description page of Project Settings.


#include "99_GameMode/BattleGameMode.h"

#include "BrainComponent.h"
#include "00_Character/BaseCharacter.h"
#include "10_WorldCharacter/WorldBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "98_GameInstance/myGameInstance.h"
#include "00_Character/02_Component/ArmyComponent.h"
#include "08_Monster/Monster.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/CustomController.h"
#include "00_Character/01_Monster/MonsterAIController.h"
#include "99_GameMode/00_GameState/BattleGameState.h"

#include "Engine/TargetPoint.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"
#include "10_WorldCharacter/01_Monster/WorldMonsterCharacter.h"
void ABattleGameMode::StartPlay()
{
	Super::StartPlay();

	controller = Cast<ACustomController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	controller->SetInputMode(FInputModeGameOnly());
	battleGameState = GetGameState<ABattleGameState>();
	auto gameInstance = Cast<UmyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (gameInstance != nullptr)
	{
		TArray<class AActor*> temp;
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), temp);
		for (AActor* location : temp)
		{
			if (location->GetName().Equals(playerSpawnActor))
			{
				playerSpawnLocation = location;
			}
			else if (location->GetName().Equals(enemySpawnActor))
			{
				enemySpawnLocation = location;
			}
		}
		if (gameInstance->GetPlayerData().WorldCharacterClass != nullptr)
		{
			auto playerData = gameInstance->GetPlayerData();
			worldPlayer = GetWorld()->SpawnActor<AWorldPlayerCharacter>(playerData.WorldCharacterClass, playerSpawnLocation->GetActorLocation(), FRotator::ZeroRotator);
			worldPlayer->SetCharacterData(playerData);
			worldPlayer->SetActorHiddenInGame(true);

			battlePlayer = GetWorld()->SpawnActor<APlayerCharacter>(worldPlayer->GetCharacter(), playerSpawnLocation->GetActorLocation(), playerSpawnLocation->GetActorRotation());
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(battlePlayer);
			
			battlePlayer->SetWorldBaseCharacter(worldPlayer); // 나중에 본체에 접근해서 인벤이나 등등 가져오려고
			battlePlayer->SetGenericTeamId(worldPlayer->GetGenericTeamId());
			battlePlayer->SetCharacter(worldPlayer);

			battleGameState->AddMyArmy(battlePlayer);

			
			SpawnArmy(worldPlayer, playerSpawnLocation);
		}
		if (gameInstance->GetTargetData().WorldCharacterClass != nullptr)
		{
			auto monsterData = gameInstance->GetTargetData();
			auto baseCharacter = GetWorld()->SpawnActor<AWorldBaseCharacter>(monsterData.WorldCharacterClass, enemySpawnLocation->GetActorLocation(),FRotator::ZeroRotator);
			baseCharacter->SetCharacterData(monsterData);
			if(baseCharacter->GetController<AAIController>()->GetBrainComponent() != nullptr)
			{
				baseCharacter->GetController<AAIController>()->GetBrainComponent()->StopLogic("BattleMode");
			}
			baseCharacter->SetActorHiddenInGame(true);

			ABaseCharacter* enemy = GetWorld()->SpawnActor<ABaseCharacter>(baseCharacter->GetCharacter(), enemySpawnLocation->GetActorLocation(), enemySpawnLocation->GetActorRotation());
			enemy->SetGenericTeamId(baseCharacter->GetGenericTeamId());
			
			battleGameState->AddEnemyArmy(enemy);

			SpawnArmy(baseCharacter, enemySpawnLocation);

			FTimerHandle runAITimer;
			FTimerDelegate runAIDelegate = FTimerDelegate::CreateUObject(this, &ABattleGameMode::RunAI);
			GetWorld()->GetTimerManager().SetTimer(
				runAITimer,
				runAIDelegate,
				3.f,
				false);
		}
	}
}

void ABattleGameMode::SpawnArmy(class AWorldBaseCharacter* baseCharacter, class AActor* locationActor)
{
	if (baseCharacter->GetArmyComponent()->IsHaveArmy())
	{
		FVector spawnLocation = locationActor->GetActorLocation() - locationActor->GetActorForwardVector() * spawnInterval;
		int32 locationIndex = 0;
		for (UMonster* army : baseCharacter->GetArmyComponent()->GetArmyList())
		{
			if (army != nullptr)
			{
				for (int i = 0; i < army->GetCount(); i++)
				{
					// 한줄 다 채웠으면 뒤로 한칸 ( 한줄 7명 ) 
					if (locationIndex >= 7)
					{
						int32 temp = locationIndex / 2;
						spawnLocation -= locationActor->GetActorForwardVector() * spawnInterval;
						spawnLocation += locationActor->GetActorRightVector() * spawnInterval * temp;
						locationIndex = 0;
					}
					int32 spawnDir = locationIndex % 2;
					if (spawnDir == 0)
					{
						spawnLocation -= locationActor->GetActorRightVector() * spawnInterval * locationIndex;
					}
					else if (spawnDir == 1)
					{
						spawnLocation += locationActor->GetActorRightVector() * spawnInterval * locationIndex;
					}
					auto gameInstance = Cast<UmyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
					if(gameInstance != nullptr)
					{
						if (gameInstance->GetMonsterInfo(army->GetTagName())->monster_BP != nullptr)
						{
							AMonsterBaseCharacter* spawnCharacter = GetWorld()->SpawnActor<AMonsterBaseCharacter>(gameInstance->GetMonsterInfo(army->GetTagName())->monster_BP, spawnLocation, locationActor->GetActorRotation());

							spawnCharacter->SetGenericTeamId(baseCharacter->GetGenericTeamId());

							if (locationActor == playerSpawnLocation)
							{
								battleGameState->AddMyArmy(spawnCharacter);
							}
							else if (locationActor == enemySpawnLocation)
							{
								battleGameState->AddEnemyArmy(spawnCharacter);
							}
							locationIndex++;
						}
					}
				}
			}
		}
	}
}
void ABattleGameMode::RunAI()
{
	auto gamestate = Cast<ABattleGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if(gamestate != nullptr)
	{
		for(auto unit : gamestate->GetMyArmy())
		{
			if(unit->IsA<AMonsterBaseCharacter>())
			{
				auto monster = Cast<AMonsterBaseCharacter>(unit);
				monster->GetController<AMonsterAIController>()->RunBehaviorTree(monster->GetAIBehaviorTree());
			}
		}
		for (auto unit : gamestate->GetEnemyArmy())
		{
			if (unit->IsA<AMonsterBaseCharacter>())
			{
				auto monster = Cast<AMonsterBaseCharacter>(unit);
				monster->GetController<AMonsterAIController>()->RunBehaviorTree(monster->GetAIBehaviorTree());
				UE_LOG(LogTemp, Log, TEXT("runAI"));
			}
		}
	}
	
}
void ABattleGameMode::SetGameState(EGameState gamestate)
{
	switch (gamestate)
	{
	case EGameState::LOSE:
		break;
	case EGameState::VICTORY:
		auto gameInstance = Cast<UmyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (gameInstance != nullptr)
		{
			gameInstance->RemoveMonsterData(gameInstance->GetTargetData().CharacterIndex);
		}
		Cast<ACustomController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->OpenBattleResult();
		break;
	}
}



void ABattleGameMode::AddDeadMyArmy(class ABaseCharacter* unit)
{
	GetGameState<ABattleGameState>()->AddDeadMyArmy(unit);
}
void ABattleGameMode::AddDeadEnemyArmy(class ABaseCharacter* unit)
{
	GetGameState<ABattleGameState>()->AddDeadEnemy(unit);
}
void ABattleGameMode::SaveWorld()
{
	FSaveCharacterData playerData(worldPlayer);
	auto gameInstance = GetGameInstance<UmyGameInstance>();
	if (gameInstance != nullptr)
	{
		playerData.CharacterLocation = gameInstance->GetPlayerData().CharacterLocation;
		gameInstance->SetPlayerData(playerData);
	}
}

void ABattleGameMode::OpenWorldLevel()
{
	SaveWorld();
	RomoveTimer();
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("WorldLevel"));
}

void ABattleGameMode::RomoveTimer()
{
	auto gameState = GetGameState<ABattleGameState>();
	if(gameState != nullptr)
	{
		gameState->RemoveTimer();
	}
}