// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "10_WorldCharacter/WorldBaseCharacter.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "WorldMonsterCharacter.generated.h"

USTRUCT(BlueprintType)
struct FMonsterArmy
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMonster> monster = nullptr;
	UPROPERTY(EditAnywhere)
		int32 MaxCount;
	UPROPERTY(EditAnywhere)
		int32 MinCount = 0;
};
USTRUCT(BlueprintType)
struct FWorldMonsterInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FGameplayTag monster_Tag;

	UPROPERTY(EditAnywhere)
		FString monster_Name;

	UPROPERTY(EditAnywhere)
		FString monster_Description;

	UPROPERTY(EditAnywhere)
		FStat monster_Stat;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class USKillBase>> monster_Skill;
	UPROPERTY(EditAnywhere)
		TArray<FMonsterArmy> monster_Army;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AMonsterBaseCharacter> monster_BP;
};
UCLASS()
class LADYBUG_API AWorldMonsterCharacter : public AWorldBaseCharacter
{
	GENERATED_BODY()
public:
	AWorldMonsterCharacter();
protected:
	// Å¸°Ù °¨Áö
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
		class UWidgetComponent* monsterNameWidgetComponent;
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AITree;

	UPROPERTY(VisibleAnywhere)
		FVector SpawnLocation;
	UPROPERTY(VisibleAnywhere)
		int32 SpawnLocationIndex;
public:
	FName GetMonsterTag() { return monsterTag.GetTagName(); }
	class UBehaviorTree* GetAIBehaviorTree() { return AITree; }
	FVector GetSpawnLocation() { return SpawnLocation; }
	FWorldMonsterInfo* const GetWorldMonsterInfo();

	int32 GetSpawnLocationIndex() { return SpawnLocationIndex; }
	void SetSpawnLocationIndex(int32 index) { SpawnLocationIndex = index; }

	virtual void SetCharacterData(FSaveCharacterData CharacterData) override;
};
