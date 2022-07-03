// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryPannelWidget.generated.h"

// �κ��丮 ���Ե��� ��� ���� Pannel
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

	// �κ��丮 ������Ʈ
	UFUNCTION()
		void UpdateButtons(TArray<class UItem*> itemArray);
};
