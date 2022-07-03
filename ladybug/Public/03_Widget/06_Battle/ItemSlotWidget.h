// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlotWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickSlots, class UItemSlotWidget*, slot);

// 아이템 슬롯 위젯
UCLASS()
class LADYBUG_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	// 슬롯 선택
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
protected:
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_ItemImage;			// 아이템 이미지
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ItemName;	// 아이템 이름
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ItemCount;	// 아이템 개수
	UPROPERTY(Meta = (BindWidget))
		class UImage* Image_SelectedFrame;		// 선택된 슬롯 테두리 표시
public:
	class UImage* GetSelectedFrame() { return Image_SelectedFrame; }
protected:
	UPROPERTY()
		class UItem* item;					// 슬롯 안에 있는 아이템
public:
	class UItem* GetItem() { return item; }
	void SetUp(class UItem* itemclass);
public:
	FOnClickSlots OnClickSlot;
};
