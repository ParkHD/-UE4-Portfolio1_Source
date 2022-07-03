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

	if(spawnedMonsters.Num() < monsterCount)
	{
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
	int32 randIndex = FMath::RandRange(0, spawnMonsterBP.Num() - 1);

	float spawnLocationX = FMath::RandRange(GetActorLocation().X - spawnRange, GetActorLocation().X + spawnRange);
	float spawnLocationY = FMath::RandRange(GetActorLocation().Y - spawnRange, GetActorLocation().Y + spawnRange);
	FVector SpawnLocation = FVector(spawnLocationX, spawnLocationY, GetActorLocation().Z);

	auto monster = GetWorld()->SpawnActor<AWorldMonsterCharacter>(spawnMonsterBP[randIndex], SpawnLocation, FRotator::ZeroRotator);
	if(monster != nullptr)
	{
		monster->SetSpawnLocationIndex(locationIndex);
		spawnedMonsters.Emplace(monster);
	}
}


