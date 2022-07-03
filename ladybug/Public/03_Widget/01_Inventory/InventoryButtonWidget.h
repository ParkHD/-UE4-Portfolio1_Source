// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "03_Widget/02_DragDrop/DragableWidget.h"
#include "InventoryButtonWidget.generated.h"

// �κ��丮 ���� ����
UCLASS()
class LADYBUG_API UInventoryButtonWidget : public UDragableWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent)override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	
	// ������ ���
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;

	// ������ �巡��
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
protected:
	UPROPERTY()
	class UTextBlock*	TextBlock_ItemCount;// ������ ����
	UPROPERTY()
	class UImage*		Image_ItemIcon;		// ������ �̹���

	// ���콺 �ø��� ������ ������ ��Ÿ�� ����
	UPROPERTY(VisibleAnywhere)
		class UItemInfoWidget* tooltip;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UItemInfoWidget> tooltipWidgetClass;

	UPROPERTY(EditAnywhere)
		int32 itemIndex;		// ���� �ε���
	
	bool isEmpty = true;		// ������ ����°�?

	// �κ��丮 ���� �巡�� �� ���� ������ ����
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UInventoryButtonShadowWidget> buttonShadowWidgetClass;
	UPROPERTY()
		class UInventoryButtonShadowWidget* buttonShadowWidget;
public:
	FText GetItemCountTextBlock();
	class UImage* GetItemIconTexture() { return Image_ItemIcon; }
public:
	const int32 GetIndex() { return itemIndex; }
	void SetIndex(int32 index) { itemIndex = index; }	// ���� �ε��� ����
	void Init();	
	void SetUpButton(class UItem* item);				// ���� SetUp
};
