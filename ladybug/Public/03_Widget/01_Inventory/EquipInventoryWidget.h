// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipInventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UEquipInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UEquipmentWidget* UMG_Equipment;
	UPROPERTY(meta = (BindWidget))
		class UInventoryWidget* UMG_Inventory;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Exit;
protected:
	virtual void NativeConstruct() override;
public:
	UFUNCTION()
		void OnChangeVisibility(ESlateVisibility visible);
	UFUNCTION()
		void UpdateInventory(TArray<class UItem*> itemArray);
	UFUNCTION()
		void UpdateEquipment(class UEquipmentComponent* EquipComp);
	UFUNCTION()
		void UpdateStatInfo(class UStatusComponent* StatComp);
	UFUNCTION()
		void OnClickExitButton();
};
