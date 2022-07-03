// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitShopInfoWidget.generated.h"

// 유닛장점에 유닛의 정보를 나타낼 위젯
UCLASS()
class LADYBUG_API UUnitShopInfoWidget : public UUserWidget
{
	GENERATED_BODY()

	// 유닛 정보
	UPROPERTY()
		class UTextBlock* TextBlock_UnitDecription;
	UPROPERTY()
		class UTextBlock* TextBlock_MaxHP;
	UPROPERTY()
		class UTextBlock* TextBlock_MaxMP;
	UPROPERTY()
		class UTextBlock* TextBlock_MaxSP;
	UPROPERTY()
		class UTextBlock* TextBlock_Damage;
	UPROPERTY()
		class UTextBlock* TextBlock_Defence;
	UPROPERTY()
		class UTextBlock* TextBlock_Skill;

public:
	// 유닛 정보창 업데이트
	UFUNCTION()
		void SetUp(class UArmyListSlotWidget* selectedSlot);

	void Init();	// 위젯 초기화
};