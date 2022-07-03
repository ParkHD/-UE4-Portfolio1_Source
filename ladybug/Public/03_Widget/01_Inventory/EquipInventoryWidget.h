// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipInventoryWidget.generated.h"


// �κ��丮 �� ���â�� �Ѱ��ϴ� ����
UCLASS()
class LADYBUG_API UEquipInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UEquipmentWidget* UMG_Equipment;		// ���â ����
	UPROPERTY(meta = (BindWidget))
		class UInventoryWidget* UMG_Inventory;		// �κ��丮 ����
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Exit;					// �������ư
protected:
	virtual void NativeConstruct() override;
public:
	UFUNCTION()
		void OnChangeVisibility(ESlateVisibility visible);
	UFUNCTION()
		void UpdateInventory(TArray<class UItem*> itemArray);		// �κ��丮 ���� ������Ʈ
	UFUNCTION()
		void UpdateEquipment(class UEquipmentComponent* EquipComp);	// ���â ���� ������Ʈ
	UFUNCTION()
		void UpdateStatInfo(class UStatusComponent* StatComp);		// ����â ���� ������Ʈ
	UFUNCTION()
		void OnClickExitButton();
};
