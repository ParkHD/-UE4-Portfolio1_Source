// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

// WorldCharcter���� ����� MainWidget
UCLASS()
class LADYBUG_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

protected:
	UPROPERTY()
		class UEquipInventoryWidget* UMG_Inventory;	// �κ��丮 â
	UPROPERTY()
		class UArmyManagerWidget* UMG_ArmyManager;	// �δ���� â
	UPROPERTY(Meta = (BindWidget))
		class UBattleWidget* UMG_Battle;			// �������� â
	UPROPERTY(Meta = (BindWidget))
		class UVillageWidget* UMG_VillageWidget;	// �������� â
public:
	class UEquipInventoryWidget* GetUMG_Inventory() { return UMG_Inventory; }
	class UArmyManagerWidget* GetUMG_ArmyManager() { return UMG_ArmyManager; }
	class UBattleWidget* GetUMG_BattleWidget() { return UMG_Battle; }
	class UVillageWidget* GetUMG_VillageWidget() { return UMG_VillageWidget; }

};
