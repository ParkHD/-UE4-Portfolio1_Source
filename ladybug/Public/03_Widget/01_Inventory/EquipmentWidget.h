// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* VerticalBox_ArmorList;
	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* VerticalBox_WeaponList;
	UPROPERTY(meta = (BindWidget))
		class UStatInfoWidget* UMG_StatInfo;

protected:
	virtual void NativeConstruct() override;

protected:
	TArray<class UEquipButtonWidget*> equipSlotList;

public:
	void UpdateSlot(class UEquipmentComponent* EquipComp);
	void UpdateStatInfo(class UStatusComponent* StatComp);

};
