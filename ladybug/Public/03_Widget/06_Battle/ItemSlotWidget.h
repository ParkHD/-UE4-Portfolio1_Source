// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlotWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickSlots, class UItemSlotWidget*, slot);
UCLASS()
class LADYBUG_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
protected:
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_ItemImage;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ItemName;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_ItemCount;
	UPROPERTY(Meta = (BindWidget))
		class UImage* Image_SelectedFrame;
public:
	class UImage* GetSelectedFrame() { return Image_SelectedFrame; }
protected:
	UPROPERTY()
		class UItem* item;
public:
	class UItem* GetItem() { return item; }
	void SetUp(class UItem* itemclass);
public:
	FOnClickSlots OnClickSlot;
};
