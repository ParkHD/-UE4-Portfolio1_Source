// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryButtonShadowWidget.generated.h"

// �κ��丮 �巡�� �� ���� ������ ����
UCLASS()
class LADYBUG_API UInventoryButtonShadowWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

protected:
	
	UPROPERTY()
	class UUserWidget* widgetRef;			// ���� ����
	UPROPERTY()
	class UImage* Image_ItemIcon;
	UPROPERTY()
	class UTextBlock* TextBlock_ItemCount;
public:
	void SetWidgetRef(class UUserWidget* widget) { widgetRef = widget; }	// ���� ���� ����
	void SetUp();
};
