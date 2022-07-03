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
		// Level�� �ִ� ��� ATargetPoint Actor�� �����´�.
		TArray<class AActor*> temp;
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), temp);
		// ������ TargetPoint �߿��� ���� �ش�Ǵ� TargetPoint�� ã�´�.
		for (AActor* location : temp)
		{
			// �÷��̾ ������ ��ġ�� �����Ѵ�.
			if (location->GetName().Equals(playerSpawnActor))
			{
				playerSpawnLocation = location;
			}
			// ���� ������ ��ġ�� �����Ѵ�.
			else if (location->GetName().Equals(enemySpawnActor))
			{
				enemySpawnLocation = location;
			}
		}
		
		if (gameInstance->GetPlayerData().WorldCharacterClass != nullptr)
		{
			// �÷��̾��� WorldCharacter�� ��ȯ�ϰ� �ν��Ͻ��� ������ �����͸� �־��ش�.
			auto playerData = gameInstance->GetPlayerData();
			worldPlayer = GetWorld()->SpawnActor<AWorldPlayerCharacter>(playerData.WorldCharacterClass, playerSpawnLocation->GetActorLocation(), FRotator::ZeroRotator);
			worldPlayer->SetCharacterData(playerData);
			worldPlayer->SetActorHiddenInGame(true);	// ���ӿ��� ���ܼ� ������ ������ �� ������ �Ѵ�.

			// �÷��̾��� BattleCharacter�� ��ȯ�ϰ� ��Ʈ�ѷ��� �Ҵ��Ѵ�.
			battlePlayer = GetWorld()->SpawnActor<APlayerCharacter>(worldPlayer->GetCharacter(), playerSpawnLocation->GetActorLocation(), playerSpawnLocation->GetActorRotation());
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->Possess(battlePlayer);
			
			battlePlayer->SetWorldBaseCharacter(worldPlayer);   // ���߿� ��ü�� �����ؼ� �κ��̳� ��� �ʿ��� �����͸� ����������
			battlePlayer->SetGenericTeamId(worldPlayer->GetGenericTeamId());
			battlePlayer->SetCharacter(worldPlayer);			// WorldCharacter(��ü)�� �����͸� �̿��Ͽ� BattleCharacter�� �����Ѵ�.

			battleGameState->AddMyArmy(battlePlayer);			// �÷��̾ GameState�� �ִ� �Ʊ�List�� �߰��Ѵ�.

			SpawnArmy(worldPlayer, playerSpawnLocation);		// �÷��̾��� �δ븦 ��ȯ�Ѵ�.
		}
		if (gameInstance->GetTargetData().WorldCharacterClass != nullptr)
		{
			// ���� WorldCharacter�� ��ȯ�ϰ� �ν��Ͻ��� ������ �����͸� �־��ش�.
			auto monsterData = gameInstance->GetTargetData();
			auto baseCharacter = GetWorld()->SpawnActor<AWorldBaseCharacter>(monsterData.WorldCharacterClass, enemySpawnLocation->GetActorLocation(),FRotator::ZeroRotator);
			baseCharacter->SetCharacterData(monsterData);

			// ���ӿ��� ���ܼ� ������ ������ �� ������ �Ѵ�.
			if(baseCharacter->GetController<AAIController>()->GetBrainComponent() != nullptr)
			{
				baseCharacter->GetController<AAIController>()->GetBrainComponent()->StopLogic("BattleMode");
			}
			baseCharacter->SetActorHiddenInGame(true);	

			// ���� BattleCharacter�� ��ȯ�ϰ� ��Ʈ�ѷ��� �Ҵ��Ѵ�.
			ABaseCharacter* enemy = GetWorld()->SpawnActor<ABaseCharacter>(baseCharacter->GetCharacter(), enemySpawnLocation->GetActorLocation(), enemySpawnLocation->GetActorRotation());
			enemy->SetGenericTeamId(baseCharacter->GetGenericTeamId());
			
			battleGameState->AddEnemyArmy(enemy);			// ���� GameState�� �ִ� ����List�� �߰��Ѵ�.

			SpawnArmy(baseCharacter, enemySpawnLocation);	// ������ �δ븦 ��ȯ�Ѵ�.

			// ��ȯ�� ���ϰ� ���� �ð� �Ŀ� AI���� BehaviorTree�� �����Ų��.
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
					// ���� �� ä������ �ڷ� ��ĭ ( ���� 7�� )
					// ���� ������ �����ư��鼭 ���� ��ġ Ž��
					if (locationIndex >= 7)
					{
						int32 temp = locationIndex / 2;
						spawnLocation -= locationActor->GetActorForwardVector() * spawnInterval;
						spawnLocation += locationActor->GetActorRightVector() * spawnInterval * temp;
						locationIndex = 0;
					}
					int32 spawnDir = locationIndex % 2;		// ���� ������
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
							// ���� ����
							AMonsterBaseCharacter* spawnCharacter = GetWorld()->SpawnActor<AMonsterBaseCharacter>(gameInstance->GetMonsterInfo(army->GetTagName())->monster_BP, spawnLocation, locationActor->GetActorRotation());
							spawnCharacter->SetGenericTeamId(baseCharacter->GetGenericTeamId());

							// GameState�� �δ�List�� �߰�
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
		// GameState�� �ִ� ������ �Ʊ��� AI�� BehaviorTree�����Ѵ�.
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
	// �������
	switch (gamestate)
	{
	case EGameState::LOSE:
		break;
	case EGameState::VICTORY:
		// �������� �¸��ϸ� GameInstance�� ������ WorldLevel�� ����List�߿��� ����� ���� �����ؼ� WorldLevel���� �����Ѵ�.
		auto gameInstance = Cast<UmyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (gameInstance != nullptr)
		{
			gameInstance->RemoveMonsterData(gameInstance->GetTargetData().CharacterIndex);
		}
		// ������� â�� ����.
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
	// �÷��̾��� ������ GameInstance�� �����Ѵ�.
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
	SaveWorld();	// �����͸� �����Ѵ�.
	RomoveTimer();	// ���� ���ư��� �ִ� Ÿ�̸Ӹ� �����Ѵ�.
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("WorldLevel"));	// WorldLevel�� �̵�
}

void ABattleGameMode::RomoveTimer()
{
	// ���ֵ��� ����ϰ� �ִ� Ÿ�̸Ӹ� �����Ѵ�.
	auto gameState = GetGameState<ABattleGameState>();
	if(gameState != nullptr)
	{
		gameState->RemoveTimer();
	}
}