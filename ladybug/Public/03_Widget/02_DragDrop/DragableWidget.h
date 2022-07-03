// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DragableWidget.generated.h"

// �巡�װ� ������ ���� -> �巡�� ����� ���� ������ �� class�� ��ӹ޵��� �Ͽ� ���
UCLASS()
class LADYBUG_API UDragableWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
protected:
	// �巡�� �� ���� ������ ����
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UInventoryButtonShadowWidget> dragShadowWidgetClass;
	UPROPERTY()
		class UInventoryButtonShadowWidget* dragShadowWidget;

	// �巡�� �� ������ ������ class
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UWidgetDragDropOperation> dragDropOperationClass;
};
