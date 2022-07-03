// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "10_WorldCharacter/WorldBaseCharacter.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "WorldMonsterCharacter.generated.h"

// 부대원 정보
USTRUCT(BlueprintType)
struct FMonsterArmy
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMonster> monster = nullptr;	// 부대원 class
	UPROPERTY(EditAnywhere)
		int32 MaxCount;				// 최대 개수
	UPROPERTY(EditAnywhere)
		int32 MinCount = 0;			// 최소 개수
};
// WorldCharacter 몬스터의 정보
USTRUCT(BlueprintType)
struct FWorldMonsterInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FGameplayTag monster_Tag;

	UPROPERTY(EditAnywhere)
		FString monster_Name;			// 몬스터 이름
	UPROPERTY(EditAnywhere)
		FString monster_Description;	// 몬스터 설명

	UPROPERTY(EditAnywhere)
		FStat monster_Stat;				// 몬스터 능력치

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class USKillBase>> monster_Skill;		// 몬스터가 가지고있는 스킬
	UPROPERTY(EditAnywhere)
		TArray<FMonsterArmy> monster_Army;							// 몬스터가 가지고 있는 부대
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AMonsterBaseCharacter> monster_BP;		// 몬스터의 BattleCharacter
};
UCLASS()
class LADYBUG_API AWorldMonsterCharacter : public AWorldBaseCharacter
{
	GENERATED_BODY()
public:
	AWorldMonsterCharacter();
protected:
	// 타겟 감지
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSourceComponent;
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere)
		class UDataTable* worldMonsterDataTable;
	UPROPERTY(EditAnywhere)
		FGameplayTag monsterTag;
	UPROPERTY(EditAnywhere)
		class UWidgetComponent* monsterNameWidgetComponent;		// 몬스터 이름 위젯
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AITree;

	UPROPERTY(VisibleAnywhere)
		FVector SpawnLocation;				// 몬스터 스폰 위치
	UPROPERTY(VisibleAnywhere)
		int32 SpawnLocationIndex;			// 몬스터를 관리하는 지역Actor의 인덱스
public:
	FName GetMonsterTag() { return monsterTag.GetTagName(); }
	class UBehaviorTree* GetAIBehaviorTree() { return AITree; }
	FVector GetSpawnLocation() { return SpawnLocation; }
	FWorldMonsterInfo* const GetWorldMonsterInfo();

	int32 GetSpawnLocationIndex() { return SpawnLocationIndex; }
	void SetSpawnLocationIndex(int32 index) { SpawnLocationIndex = index; }

	// 데이터 덮어쓰기
	virtual void SetCharacterData(FSaveCharacterData CharacterData) override;
};
