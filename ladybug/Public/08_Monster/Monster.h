// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "00_Character/00_Player/Component/StatusComponent.h"
#include "Monster.generated.h"

// ���Ͱ� ����ϴ� ������ ����
USTRUCT(BlueprintType)
struct FDropItem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UItem> dropItem;	// ����ϴ� ������
	UPROPERTY(EditAnywhere)
		float dropPercentage;				// ��� Ȯ��
};

// ���� ����
USTRUCT(BlueprintType)
struct FMonsterInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FGameplayTag monster_Tag;

	UPROPERTY(EditAnywhere)
		FString monster_Name;							// ���� �̸�
	UPROPERTY(EditAnywhere)
		class UTextureRenderTarget2D* monster_Image;	// ���� ������ �̹���
	UPROPERTY(EditAnywhere)
		class UTexture2D* monster_Icon;					// ���� ������

	UPROPERTY(EditAnywhere)
		FString monster_Description;					// ���� ����

	UPROPERTY(EditAnywhere)
		FStat monster_Stat;								// ���� ����
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class USKillBase>> monster_Skill;	// ���� ��ų
	UPROPERTY(EditAnywhere)
		TArray<FDropItem> monster_Dropitem;						// ���� ��� ������List
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AMonsterBaseCharacter> monster_BP;	// ���� BattleCharacter
};

UCLASS(Blueprintable)
class LADYBUG_API UMonster : public UObject
{
	GENERATED_BODY()
public:
	UMonster(){}
	~UMonster() { UE_LOG(LogTemp, Error, TEXT("desUni")); }
protected:
	UPROPERTY(EditAnywhere)
		const UDataTable* monsterDT;
	UPROPERTY(EditAnywhere)
		FGameplayTag monsterTag;
protected:
	UPROPERTY(EditAnywhere)
		FStat characterStat;
	UPROPERTY(EditAnywhere)
		int32 count = 1;

public:
	const FMonsterInfo* GetMonsterInfo();
	const int32 GetCount() { return count; }
	void SetCount(float MonCount) { count = MonCount; }				// ���� ���� ����
	const FName GetTagName() { return monsterTag.GetTagName(); }
};
