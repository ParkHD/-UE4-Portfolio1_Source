// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemInfoWidget.generated.h"

// 아이템 정보창 위젯
UCLASS()
class LADYBUG_API UItemInfoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ItemName;			// 아이템 이름
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_ItemImage;					// 아이템 이미지
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ItemDecription;		// 아이템 설명

	// 능력치 위젯
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_HPStat;				// HP
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_MPStat;				// MP
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_SPStat;				// Stamina
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_DamageStat;			// 공격력
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_DefenceStat;		// 방어력

	// ex) HP : ???
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
		class UVerticalBox* VerticalBox_Stat;			// 스텟 위젯 모아놓은 VerticalBox
public:
	virtual void NativeConstruct()override;

public:
	UFUNCTION()
		virtual void SetUp(class UItemSlotWidget* selectedSlot);

	void SetUp(class UItem* info);

	void Init();
};
