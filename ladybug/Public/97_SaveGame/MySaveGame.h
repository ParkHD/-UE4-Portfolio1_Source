  // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"


USTRUCT(BlueprintType)
struct FMonsterSaveData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
		class UMonster* character;
	UPROPERTY(BlueprintReadWrite)
		FVector characterLocation;
};

UCLASS()
class LADYBUG_API UMySaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	UMySaveGame();
public:
	FString SaveSlotName;
	int32 SaveIndex;

	FString tempName;
	UPROPERTY()
		class AWorldPlayerCharacter* playerData;
	UPROPERTY()
		class AWorldMonsterCharacter* battleTargetData;
	UPROPERTY()
		TArray<class AWorldMonsterCharacter*> worldUnitDatas;
};
