// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/99_Public/01_NotifyState/NotifyState_SpawnActor.h"

#include "00_Character/BaseCharacter.h"
#include "00_Character/01_Monster/MonsterAIController.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "99_GameMode/BattleGameMode.h"
#include "99_GameMode/00_GameState/BattleGameState.h"

void UNotifyState_SpawnActor::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                          float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	SpawnLocationsArray.Empty();

	// Actor를 스폰할 위치 탐색
	owner = MeshComp->GetOwner<ABaseCharacter>();
	if (owner != nullptr)
	{
		auto battleGameMode = Cast<ABattleGameMode>(UGameplayStatics::GetGameMode(MeshComp->GetWorld()));
		if (battleGameMode != nullptr)
		{
			FVector spawnLocation = owner->GetActorLocation() - owner->GetActorForwardVector() * SpawnInterval;
			int32 locationIndex = 0;
			for (int i = 0; i < SpawnCount; i++)
			{
				// 한줄 다 채웠으면 뒤로 한칸 ( 한줄 7명 )
				// 왼쪽 오른쪽 번갈아가면서 스폰 위치 탐색
				if (locationIndex >= 7)
				{
					int32 temp = locationIndex / 2;
					spawnLocation -= owner->GetActorForwardVector() * SpawnInterval;
					spawnLocation += owner->GetActorRightVector() * SpawnInterval * temp;
					locationIndex = 0;
				}
				int32 spawnDir = locationIndex % 2;	// 왼쪽 오른쪽
				if (spawnDir == 0)
				{
					spawnLocation -= owner->GetActorRightVector() * SpawnInterval * locationIndex;
				}
				else if (spawnDir == 1)
				{
					spawnLocation += owner->GetActorRightVector() * SpawnInterval * locationIndex;
				}

				// 소환할 위치에 파티클 실행
				FVector particleLoaction = spawnLocation;
				particleLoaction.Z -= tempLocationZ;	// 파티클 위치 조정
				UGameplayStatics::SpawnEmitterAtLocation(MeshComp->GetWorld(), spawnParticle, particleLoaction);

				SpawnLocationsArray.Emplace(spawnLocation);
				locationIndex++;
			}
		}
	}
}

void UNotifyState_SpawnActor::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

}

void UNotifyState_SpawnActor::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	// Actor Spawn
	if(owner != nullptr)
	{
		auto battleGameState = Cast<ABattleGameState>(UGameplayStatics::GetGameState(owner->GetWorld()));

		for(auto spawnLocation : SpawnLocationsArray)
		{
			// Actor 소환
			AMonsterBaseCharacter* spawnCharacter = owner->GetWorld()->SpawnActor<AMonsterBaseCharacter>(SpawnActorBP, spawnLocation, owner->GetActorRotation());

			// BehaviorTree 실행
			if (spawnCharacter->GetAIBehaviorTree() != nullptr)
			{
				spawnCharacter->GetController<AMonsterAIController>()->RunBehaviorTree(spawnCharacter->GetAIBehaviorTree());
			}

			// 소환된 Actor를 GameState에 저장 -> 전투 종료 조건 위함
			if(spawnCharacter != nullptr)
			{
				spawnCharacter->SetGenericTeamId(owner->GetGenericTeamId());
				if (owner->GetGenericTeamId() == 10)
				{
					battleGameState->AddMyArmy(spawnCharacter);
				}
				else if (owner->GetGenericTeamId() == 20)
				{
					battleGameState->AddEnemyArmy(spawnCharacter);
				}
			}
		}
	}


}