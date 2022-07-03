// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPannelWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UInventoryPannelWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY()
		class UUniformGridPanel* UniformGridPanel_Buttons;
	UPROPERTY()
		TArray<class UInventoryButtonWidget*> inventoryButtons;

public:
	void InitButtons();

	UFUNCTION()
	void UpdateButtons(TArray<class UItem*> itemArray);
};
