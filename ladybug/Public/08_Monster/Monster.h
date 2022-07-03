// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "00_Character/00_Player/Component/StatusComponent.h"
#include "Monster.generated.h"

// 몬스터가 드랍하는 아이템 정보
USTRUCT(BlueprintType)
struct FDropItem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UItem> dropItem;	// 드랍하는 아이템
	UPROPERTY(EditAnywhere)
		float dropPercentage;				// 드랍 확률
};

// 몬스터 정보
USTRUCT(BlueprintType)
struct FMonsterInfo : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FGameplayTag monster_Tag;

	UPROPERTY(EditAnywhere)
		FString monster_Name;							// 몬스터 이름
	UPROPERTY(EditAnywhere)
		class UTextureRenderTarget2D* monster_Image;	// 몬스터 프리뷰 이미지
	UPROPERTY(EditAnywhere)
		class UTexture2D* monster_Icon;					// 몬스터 아이콘

	UPROPERTY(EditAnywhere)
		FString monster_Description;					// 몬스터 설명

	UPROPERTY(EditAnywhere)
		FStat monster_Stat;								// 몬스터 스텟
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class USKillBase>> monster_Skill;	// 몬스터 스킬
	UPROPERTY(EditAnywhere)
		TArray<FDropItem> monster_Dropitem;						// 몬스터 드랍 아이템List
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AMonsterBaseCharacter> monster_BP;	// 몬스터 BattleCharacter
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
	void SetCount(float MonCount) { count = MonCount; }				// 유닛 개수 설정
	const FName GetTagName() { return monsterTag.GetTagName(); }
};
