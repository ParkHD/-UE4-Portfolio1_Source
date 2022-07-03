// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemInfoWidget.generated.h"

// ������ ����â ����
UCLASS()
class LADYBUG_API UItemInfoWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ItemName;			// ������ �̸�
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_ItemImage;					// ������ �̹���
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ItemDecription;		// ������ ����

	// �ɷ�ġ ����
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_HPStat;				// HP
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_MPStat;				// MP
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_SPStat;				// Stamina
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_DamageStat;			// ���ݷ�
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_DefenceStat;		// ����

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
		class UVerticalBox* VerticalBox_Stat;			// ���� ���� ��Ƴ��� VerticalBox
public:
	virtual void NativeConstruct()override;

public:
	UFUNCTION()
		virtual void SetUp(class UItemSlotWidget* selectedSlot);

	void SetUp(class UItem* info);

	void Init();
};
