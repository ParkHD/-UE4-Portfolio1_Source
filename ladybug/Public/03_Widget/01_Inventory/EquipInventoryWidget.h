// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipInventoryWidget.generated.h"


// 인벤토리 및 장비창을 총괄하는 위젯
UCLASS()
class LADYBUG_API UEquipInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UEquipmentWidget* UMG_Equipment;		// 장비창 위젯
	UPROPERTY(meta = (BindWidget))
		class UInventoryWidget* UMG_Inventory;		// 인벤토리 위젯
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Exit;					// 나가기버튼
protected:
	virtual void NativeConstruct() override;
public:
	UFUNCTION()
		void OnChangeVisibility(ESlateVisibility visible);
	UFUNCTION()
		void UpdateInventory(TArray<class UItem*> itemArray);		// 인벤토리 위젯 업데이트
	UFUNCTION()
		void UpdateEquipment(class UEquipmentComponent* EquipComp);	// 장비창 위젯 업데이트
	UFUNCTION()
		void UpdateStatInfo(class UStatusComponent* StatComp);		// 스텟창 위젯 업데이트
	UFUNCTION()
		void OnClickExitButton();
};
