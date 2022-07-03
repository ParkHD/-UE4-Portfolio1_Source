// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "02_Item/ItemTypes.h"
#include "SaveVariable.generated.h"

// SaveData 관리

// 부대관리 컴포넌트 데이터
USTRUCT(BlueprintType)
struct FArmyComponentSave
{
	GENERATED_BODY()
public:
	// 부대 리스트
	UPROPERTY()
 		TArray<class UMonster*> ArmyList;	// 부대원 List
};
// 인벤토리 컴포넌트 데이터
USTRUCT(BlueprintType)
struct FInvenComponentSave
{
	GENERATED_BODY()
public:
	// 인벤토리 아이템 리스트
	UPROPERTY()
		TArray<class UItem*> ItemList;		// 인벤토리 : 아이템List
};
// 능력치 컴포넌트 데이터
USTRUCT(BlueprintType)
struct FStatusComponentSave
{
	GENERATED_BODY()
public:
	// 캐릭터 능력치
	FStat CharacterStat;		// 능력치 
};
// 장비 컴포넌트 데이터
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
		TArray<class UWeapon*> WeaponList;	// 현재 장착한 무기들
	UPROPERTY()
		TArray<class UArmor*> ArmorList;	// 현재 장착한 방어구
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
	// 몬스터를 구분 지을 고유인덱스
	int32 CharacterIndex;

	// 실제 소환될 캐릭터BP
	UPROPERTY(BlueprintReadWrite)
		class UClass* WorldCharacterClass = nullptr;

	// WorldLevel에서의 캐릭터 위치
	FVector CharacterLocation;
	// 몬스터를 관리하는 거점Actor의 인덱스
	int32 LocationIndex;

	// ActorComponent데이터
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
