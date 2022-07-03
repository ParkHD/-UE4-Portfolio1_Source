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
		// Level에 있는 모든 ATargetPoint Actor를 가져온다.
		TArray<class AActor*> temp;
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), temp);
		// 가져온 TargetPoint 중에서 각각 해당되는 TargetPoint를 찾는다.
		for (AActor* location : temp)
		{
			// 플레이어가 스폰될 위치를 저장한다.
			if (location->GetName().Equals(playerSpawnActor))
			{
				playerSpawnLocation = location;
			}
			// 적이 스폰될 위치를 저장한다.
			else if (location->GetName().Equals(enemySpawnActor))
			{
				enemySpawnLocation = location;
			}
		}
		
		if (gameInstance->GetPlayerData().WorldCharacterClass != nullptr)
		{
			// 플레이어의 WorldCharacter를 소환하고 인스턴스에 저장한 데이터를 넣어준다.
			auto playerData = gameInstance->GetPlayerData();
			worldPlayer = GetWorld()->SpawnActor<AWorldPlayerCharacter>(playerData.WorldCharacterClass, playerSpawnLocation->GetActorLocation(), FRotator::ZeroRotator);
			worldPlayer->SetCharacterData(playerData);
			worldPlayer->SetActorHiddenInGame(true);	// 게임에서 숨겨서 전투에 영향이 안 가도록 한다.

			// 플레이어의 BattleCharacter를 소환하고 컨트롤러를 할당한다.
			battlePlayer = GetWorld()->SpawnActor<APlayerCharacter>(worldPlayer->GetCharacter(), playerSpawnLocation->GetActorLocation(), playerSpawnLocation->GetActorRotation());
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(battlePlayer);
			
			battlePlayer->SetWorldBaseCharacter(worldPlayer);   // 나중에 본체에 접근해서 인벤이나 등등 필요한 데이터를 가져오려고
			battlePlayer->SetGenericTeamId(worldPlayer->GetGenericTeamId());
			battlePlayer->SetCharacter(worldPlayer);			// WorldCharacter(본체)에 데이터를 이용하여 BattleCharacter를 설정한다.

			battleGameState->AddMyArmy(battlePlayer);			// 플레이어를 GameState에 있는 아군List에 추가한다.

			SpawnArmy(worldPlayer, playerSpawnLocation);		// 플레이어의 부대를 소환한다.
		}
		if (gameInstance->GetTargetData().WorldCharacterClass != nullptr)
		{
			// 적의 WorldCharacter를 소환하고 인스턴스에 저장한 데이터를 넣어준다.
			auto monsterData = gameInstance->GetTargetData();
			auto baseCharacter = GetWorld()->SpawnActor<AWorldBaseCharacter>(monsterData.WorldCharacterClass, enemySpawnLocation->GetActorLocation(),FRotator::ZeroRotator);
			baseCharacter->SetCharacterData(monsterData);

			// 게임에서 숨겨서 전투에 영향이 안 가도록 한다.
			if(baseCharacter->GetController<AAIController>()->GetBrainComponent() != nullptr)
			{
				baseCharacter->GetController<AAIController>()->GetBrainComponent()->StopLogic("BattleMode");
			}
			baseCharacter->SetActorHiddenInGame(true);	

			// 적의 BattleCharacter를 소환하고 컨트롤러를 할당한다.
			ABaseCharacter* enemy = GetWorld()->SpawnActor<ABaseCharacter>(baseCharacter->GetCharacter(), enemySpawnLocation->GetActorLocation(), enemySpawnLocation->GetActorRotation());
			enemy->SetGenericTeamId(baseCharacter->GetGenericTeamId());
			
			battleGameState->AddEnemyArmy(enemy);			// 적을 GameState에 있는 적군List에 추가한다.

			SpawnArmy(baseCharacter, enemySpawnLocation);	// 적군의 부대를 소환한다.

			// 소환을 다하고 일정 시간 후에 AI들의 BehaviorTree를 실행시킨다.
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
					// 왼쪽 오른쪽 번갈아가면서 스폰 위치 탐색
					if (locationIndex >= 7)
					{
						int32 temp = locationIndex / 2;
						spawnLocation -= locationActor->GetActorForwardVector() * spawnInterval;
						spawnLocation += locationActor->GetActorRightVector() * spawnInterval * temp;
						locationIndex = 0;
					}
					int32 spawnDir = locationIndex % 2;		// 왼쪽 오른쪽
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
							// 유닛 스폰
							AMonsterBaseCharacter* spawnCharacter = GetWorld()->SpawnActor<AMonsterBaseCharacter>(gameInstance->GetMonsterInfo(army->GetTagName())->monster_BP, spawnLocation, locationActor->GetActorRotation());
							spawnCharacter->SetGenericTeamId(baseCharacter->GetGenericTeamId());

							// GameState의 부대List에 추가
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
		// GameState에 있는 적군과 아군의 AI인 BehaviorTree실행한다.
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
			}
		}
	}
	
}
void ABattleGameMode::SetGameState(EGameState gamestate)
{
	// 전투결과
	switch (gamestate)
	{
	case EGameState::LOSE:
		break;
	case EGameState::VICTORY:
		// 전투에서 승리하면 GameInstance에 저장한 WorldLevel의 몬스터List중에서 상대한 적을 삭제해서 WorldLevel에서 삭제한다.
		auto gameInstance = Cast<UmyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (gameInstance != nullptr)
		{
			gameInstance->RemoveMonsterData(gameInstance->GetTargetData().CharacterIndex);
		}
		// 전투결과 창을 연다.
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
	// 플레이어의 정보를 GameInstance에 저장한다.
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
	SaveWorld();	// 데이터를 저장한다.
	RomoveTimer();	// 현재 돌아가고 있는 타이머를 삭제한다.
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("WorldLevel"));	// WorldLevel로 이동
}

void ABattleGameMode::RomoveTimer()
{
	// 유닛들이 사용하고 있는 타이머를 제거한다.
	auto gameState = GetGameState<ABattleGameState>();
	if(gameState != nullptr)
	{
		gameState->RemoveTimer();
	}
}