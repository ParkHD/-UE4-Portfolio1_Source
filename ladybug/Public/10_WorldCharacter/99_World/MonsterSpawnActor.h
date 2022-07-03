// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawnActor.generated.h"


// 몬스터를 관리할 Actor -> 스폰이 되는 몬스터 종류 관리 및 개수 관리
UCLASS()
class LADYBUG_API AMonsterSpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMonsterSpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere)
		int32 locationIndex;					// 지역 구분을 위한 인덱스
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class AWorldMonsterCharacter>> spawnMonsterBP;	// 스폰 가능 한 몬스터의 종류

	UPROPERTY(VisibleAnywhere)
		TArray<class AWorldMonsterCharacter*> spawnedMonsters;	// 현재 스폰 되어있는 몬스터List
	UPROPERTY(EditAnywhere)
		int32 monsterCount;		// 현재 스폰 되어있는 몬스터 개수
	UPROPERTY(EditAnywhere)
		float spawnCoolTime;	// 스폰 쿨타임
	UPROPERTY(EditAnywhere)
		float spawnRange;		// 스폰 할 범위

	float coolTime = spawnCoolTime;	// 타이머
public:
	void SpawnMonster();	// 몬스터 소환
	void AddMonster(class AWorldMonsterCharacter* monster)
	{
		spawnedMonsters.Emplace(monster);
	}
	int32 GetLocationIndex() { return locationIndex; }
};
