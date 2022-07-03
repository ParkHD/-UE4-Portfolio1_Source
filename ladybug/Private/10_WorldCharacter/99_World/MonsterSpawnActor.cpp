// Fill out your copyright notice in the Description page of Project Settings.


#include "10_WorldCharacter/99_World/MonsterSpawnActor.h"

#include "10_WorldCharacter/01_Monster/WorldMonsterCharacter.h"

// Sets default values
AMonsterSpawnActor::AMonsterSpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMonsterSpawnActor::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AMonsterSpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 지역의 몬스터 최대 개수 이하인지 확인
	if(spawnedMonsters.Num() < monsterCount)
	{
		// 쿨타임이 지나면 몬스터 소환
		coolTime += DeltaTime;
		if (coolTime >= spawnCoolTime)
		{
			SpawnMonster();
			coolTime = 0;
		}
	}
}

void AMonsterSpawnActor::SpawnMonster()
{
	// 스폰할 몬스터 랜덤으로 설정
	int32 randIndex = FMath::RandRange(0, spawnMonsterBP.Num() - 1);

	// 스폰할 위치 정해진 범위 안에 랜덤으로 설정
	float spawnLocationX = FMath::RandRange(GetActorLocation().X - spawnRange, GetActorLocation().X + spawnRange);
	float spawnLocationY = FMath::RandRange(GetActorLocation().Y - spawnRange, GetActorLocation().Y + spawnRange);
	FVector SpawnLocation = FVector(spawnLocationX, spawnLocationY, GetActorLocation().Z);

	// 몬스터 스폰
	auto monster = GetWorld()->SpawnActor<AWorldMonsterCharacter>(spawnMonsterBP[randIndex], SpawnLocation, FRotator::ZeroRotator);
	if(monster != nullptr)
	{
		// 몬스터를 지역Actor에 상속시키기
		monster->SetSpawnLocationIndex(locationIndex);
		spawnedMonsters.Emplace(monster);
	}
}


