// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragableWidget.generated.h"

// 드래그가 가능한 위젯 -> 드래그 기능을 넣을 위젯은 이 class를 상속받도록 하여 사용
UCLASS()
class LADYBUG_API UDragableWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
protected:
	// 드래그 시 나올 쉐도우 위젯
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UInventoryButtonShadowWidget> dragShadowWidgetClass;
	UPROPERTY()
		class UInventoryButtonShadowWidget* dragShadowWidget;

	// 드래그 후 정보를 전달할 class
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UWidgetDragDropOperation> dragDropOperationClass;
};
