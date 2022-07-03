// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryButtonShadowWidget.generated.h"

// 인벤토리 드래그 시 나올 쉐도우 위젯
UCLASS()
class LADYBUG_API UInventoryButtonShadowWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

protected:
	
	UPROPERTY()
	class UUserWidget* widgetRef;			// 참조 위젯
	UPROPERTY()
	class UImage* Image_ItemIcon;
	UPROPERTY()
	class UTextBlock* TextBlock_ItemCount;
public:
	void SetWidgetRef(class UUserWidget* widget) { widgetRef = widget; }	// 참조 위젯 설정
	void SetUp();
};
