// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MonsterSpawnActor.generated.h"


// ���͸� ������ Actor -> ������ �Ǵ� ���� ���� ���� �� ���� ����
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
		int32 locationIndex;					// ���� ������ ���� �ε���
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class AWorldMonsterCharacter>> spawnMonsterBP;	// ���� ���� �� ������ ����

	UPROPERTY(VisibleAnywhere)
		TArray<class AWorldMonsterCharacter*> spawnedMonsters;	// ���� ���� �Ǿ��ִ� ����List
	UPROPERTY(EditAnywhere)
		int32 monsterCount;		// ���� ���� �Ǿ��ִ� ���� ����
	UPROPERTY(EditAnywhere)
		float spawnCoolTime;	// ���� ��Ÿ��
	UPROPERTY(EditAnywhere)
		float spawnRange;		// ���� �� ����

	float coolTime = spawnCoolTime;	// Ÿ�̸�
public:
	void SpawnMonster();	// ���� ��ȯ
	void AddMonster(class AWorldMonsterCharacter* monster)
	{
		spawnedMonsters.Emplace(monster);
	}
	int32 GetLocationIndex() { return locationIndex; }
};
