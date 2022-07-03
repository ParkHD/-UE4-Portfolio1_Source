// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainWidget.generated.h"

// WorldCharcter에서 사용할 MainWidget
UCLASS()
class LADYBUG_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
protected:

protected:
	UPROPERTY()
		class UEquipInventoryWidget* UMG_Inventory;	// 인벤토리 창
	UPROPERTY()
		class UArmyManagerWidget* UMG_ArmyManager;	// 부대관리 창
	UPROPERTY(Meta = (BindWidget))
		class UBattleWidget* UMG_Battle;			// 전투진입 창
	UPROPERTY(Meta = (BindWidget))
		class UVillageWidget* UMG_VillageWidget;	// 마을진입 창
public:
	class UEquipInventoryWidget* GetUMG_Inventory() { return UMG_Inventory; }
	class UArmyManagerWidget* GetUMG_ArmyManager() { return UMG_ArmyManager; }
	class UBattleWidget* GetUMG_BattleWidget() { return UMG_Battle; }
	class UVillageWidget* GetUMG_VillageWidget() { return UMG_VillageWidget; }

};
