// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPannelWidget.generated.h"

// 인벤토리 슬롯들을 모아 놓은 Pannel
UCLASS()
class LADYBUG_API UInventoryPannelWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		class UUniformGridPanel* UniformGridPanel_Buttons;
protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
		TArray<class UInventoryButtonWidget*> inventoryButtons;
public:
	void InitButtons();

	// 인벤토리 업데이트
	UFUNCTION()
		void UpdateButtons(TArray<class UItem*> itemArray);
};
