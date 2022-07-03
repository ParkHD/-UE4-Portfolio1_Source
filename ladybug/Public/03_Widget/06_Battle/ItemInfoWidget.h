// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UItemInfoWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct()override;

protected:

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ItemName;
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_ItemImage;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ItemDecription;

	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_HPStat;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_MPStat;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_SPStat;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_DamageStat;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_DefenceStat;

	UPROPERTY(meta = (BindWidget))
		class UHorizontalBox* HorizontalBox_HPStat;
	UPROPERTY(meta = (BindWidget))
		class UHorizontalBox* HorizontalBox_MPStat;
	UPROPERTY(meta = (BindWidget))
		class UHorizontalBox* HorizontalBox_SPStat;
	UPROPERTY(meta = (BindWidget))
		class UHorizontalBox* HorizontalBox_DamageStat;
	UPROPERTY(meta = (BindWidget))
		class UHorizontalBox* HorizontalBox_DefenceStat;

	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* VerticalBox_Stat;
public:
	UFUNCTION()
		virtual void SetUp(class UItemSlotWidget* selectedSlot);

	void SetUp(class UItem* info);

	void Init();
};
