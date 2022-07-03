// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "03_Widget/02_DragDrop/DragableWidget.h"
#include "EquipButtonWidget.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EEquipSlotType : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	HELMET,
	CAPE,
	CLOTH,
	GLOVE,
	SHOES,
	WEAPON,
};
UCLASS()
class LADYBUG_API UEquipButtonWidget : public UDragableWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		class UImage* Image_BackGround;
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_ItemImage;
protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
protected:
	UPROPERTY(EditAnywhere)
		class UTexture2D* backGroundTexture;
	UPROPERTY(EditAnywhere)
		EEquipSlotType slotType;

	UPROPERTY()
		class UItem* itemInSlot;
	int32 slotIndex = -1;
	// 인벤 칸이 비었는가?
	bool isEmpty = true;
public:

	int32 GetIndex() { return slotIndex; }
	void SetIndex(int32 num) { slotIndex = num; }
	void SetUp(UItem* item);
	void Init();
};
