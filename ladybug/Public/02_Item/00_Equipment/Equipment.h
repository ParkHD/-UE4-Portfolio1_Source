// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "02_Item/Item.h"
#include "00_Character/00_Player/Component/StatusComponent.h"

#include "Equipment.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UEquipment : public UItem
{
	GENERATED_BODY()
public:
	UEquipment();
protected:
	FStat equipmentStat;
public:
	FStat GetStat() { return equipmentStat; }
public:
	virtual void ItemStatSetUp() override;
};
