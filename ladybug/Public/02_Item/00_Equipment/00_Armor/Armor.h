// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "02_Item/00_Equipment/Equipment.h"
#include "Armor.generated.h"

// 방어구 아이템
UCLASS()
class LADYBUG_API UArmor : public UEquipment
{
	GENERATED_BODY()
public:
	// 아이템 사용
	virtual void UseItem(class APlayerCharacter* player) override;
	virtual void UseItem(class AWorldPlayerCharacter* player) override;
};
