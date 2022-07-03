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

	// Actor�� ������ ��ġ Ž��
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
				// ���� �� ä������ �ڷ� ��ĭ ( ���� 7�� )
				// ���� ������ �����ư��鼭 ���� ��ġ Ž��
				if (locationIndex >= 7)
				{
					int32 temp = locationIndex / 2;
					spawnLocation -= owner->GetActorForwardVector() * SpawnInterval;
					spawnLocation += owner->GetActorRightVector() * SpawnInterval * temp;
					locationIndex = 0;
				}
				int32 spawnDir = locationIndex % 2;	// ���� ������
				if (spawnDir == 0)
				{
					spawnLocation -= owner->GetActorRightVector() * SpawnInterval * locationIndex;
				}
				else if (spawnDir == 1)
				{
					spawnLocation += owner->GetActorRightVector() * SpawnInterval * locationIndex;
				}

				// ��ȯ�� ��ġ�� ��ƼŬ ����
				FVector particleLoaction = spawnLocation;
				particleLoaction.Z -= tempLocationZ;	// ��ƼŬ ��ġ ����
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
			// Actor ��ȯ
			AMonsterBaseCharacter* spawnCharacter = owner->GetWorld()->SpawnActor<AMonsterBaseCharacter>(SpawnActorBP, spawnLocation, owner->GetActorRotation());

			// BehaviorTree ����
			if (spawnCharacter->GetAIBehaviorTree() != nullptr)
			{
				spawnCharacter->GetController<AMonsterAIController>()->RunBehaviorTree(spawnCharacter->GetAIBehaviorTree());
			}

			// ��ȯ�� Actor�� GameState�� ���� -> ���� ���� ���� ����
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