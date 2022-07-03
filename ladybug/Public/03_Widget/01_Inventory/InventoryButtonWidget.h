// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "03_Widget/02_DragDrop/DragableWidget.h"
#include "InventoryButtonWidget.generated.h"

// 인벤토리 슬롯 위젯
UCLASS()
class LADYBUG_API UInventoryButtonWidget : public UDragableWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent)override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	
	// 아이템 사용
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;

	// 아이템 드래그
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
protected:
	UPROPERTY()
	class UTextBlock*	TextBlock_ItemCount;// 아이템 개수
	UPROPERTY()
	class UImage*		Image_ItemIcon;		// 아이템 이미지

	// 마우스 올리면 아이템 정보를 나타낼 위젯
	UPROPERTY(VisibleAnywhere)
		class UItemInfoWidget* tooltip;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UItemInfoWidget> tooltipWidgetClass;

	UPROPERTY(EditAnywhere)
		int32 itemIndex;		// 슬롯 인덱스
	
	bool isEmpty = true;		// 슬롯이 비었는가?

	// 인벤토리 슬롯 드래그 시 나올 쉐도우 위젯
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UInventoryButtonShadowWidget> buttonShadowWidgetClass;
	UPROPERTY()
		class UInventoryButtonShadowWidget* buttonShadowWidget;
public:
	FText GetItemCountTextBlock();
	class UImage* GetItemIconTexture() { return Image_ItemIcon; }
public:
	const int32 GetIndex() { return itemIndex; }
	void SetIndex(int32 index) { itemIndex = index; }	// 슬롯 인덱스 설정
	void Init();	
	void SetUpButton(class UItem* item);				// 슬롯 SetUp
};
