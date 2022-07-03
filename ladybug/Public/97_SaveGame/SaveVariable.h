// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "02_Item/ItemTypes.h"
#include "SaveVariable.generated.h"

// SaveData ����

// �δ���� ������Ʈ ������
USTRUCT(BlueprintType)
struct FArmyComponentSave
{
	GENERATED_BODY()
public:
	// �δ� ����Ʈ
	UPROPERTY()
 		TArray<class UMonster*> ArmyList;	// �δ�� List
};
// �κ��丮 ������Ʈ ������
USTRUCT(BlueprintType)
struct FInvenComponentSave
{
	GENERATED_BODY()
public:
	// �κ��丮 ������ ����Ʈ
	UPROPERTY()
		TArray<class UItem*> ItemList;		// �κ��丮 : ������List
};
// �ɷ�ġ ������Ʈ ������
USTRUCT(BlueprintType)
struct FStatusComponentSave
{
	GENERATED_BODY()
public:
	// ĳ���� �ɷ�ġ
	FStat CharacterStat;		// �ɷ�ġ 
};
// ��� ������Ʈ ������
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
		TArray<class UWeapon*> WeaponList;	// ���� ������ �����
	UPROPERTY()
		TArray<class UArmor*> ArmorList;	// ���� ������ ��
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
	// ���͸� ���� ���� �����ε���
	int32 CharacterIndex;

	// ���� ��ȯ�� ĳ����BP
	UPROPERTY(BlueprintReadWrite)
		class UClass* WorldCharacterClass = nullptr;

	// WorldLevel������ ĳ���� ��ġ
	FVector CharacterLocation;
	// ���͸� �����ϴ� ����Actor�� �ε���
	int32 LocationIndex;

	// ActorComponent������
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
