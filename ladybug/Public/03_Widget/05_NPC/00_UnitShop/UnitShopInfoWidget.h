// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitShopInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UUnitShopInfoWidget : public UUserWidget
{
	GENERATED_BODY()

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
	UFUNCTION()
		void SetUp(class UArmyListSlotWidget* selectedSlot);

	void Init();
};
