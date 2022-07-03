// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "02_Item/ItemTypes.h"

#include "SaveVariable.generated.h"


USTRUCT(BlueprintType)
struct FArmyComponentSave
{
	GENERATED_BODY()
public:
	UPROPERTY()
 		TArray<class UMonster*> ArmyList;
};
USTRUCT(BlueprintType)
struct FInvenComponentSave
{
	GENERATED_BODY()
public:
	UPROPERTY()
		TArray<class UItem*> ItemList;
};
USTRUCT(BlueprintType)
struct FStatusComponentSave
{
	GENERATED_BODY()
public:
	FStat CharacterStat;
};
USTRUCT(BlueprintType)
struct FEquipComponentSave
{
	GENERATED_BODY()
public:
	FEquipComponentSave()
	{
		WeaponList.Init(nullptr, 4);
		ArmorList.Init(nullptr, 5);
	}
public:
	UPROPERTY()
		TArray<class UWeapon*> WeaponList;
	UPROPERTY()
		TArray<class UArmor*> ArmorList;
};
USTRUCT(BlueprintType)
struct FSaveCharacterData
{
	GENERATED_BODY()
public:
	FSaveCharacterData()
	{}
	FSaveCharacterData(class AWorldPlayerCharacter* Player);
	FSaveCharacterData(int32 Index, class AWorldMonsterCharacter* Monster);
public:
	int32 CharacterIndex;

	UPROPERTY(BlueprintReadWrite)
		class UClass* WorldCharacterClass = nullptr;

	FVector CharacterLocation;
	int32 LocationIndex;

	UPROPERTY()
		FArmyComponentSave ArmyComponentData;
	UPROPERTY()
		FInvenComponentSave InvenComponentData;
	UPROPERTY()
		FEquipComponentSave EquipComponentData;
	UPROPERTY()
		FStatusComponentSave StatusComponentData;

	bool operator ==(const FSaveCharacterData& a)
	{
		return CharacterIndex == a.CharacterIndex;
	}
public:
	bool IsEmpty()
	{
		return WorldCharacterClass == nullptr;
	}
};

UCLASS()
class LADYBUG_API USaveVariable : public UObject
{
	GENERATED_BODY()
	
};
