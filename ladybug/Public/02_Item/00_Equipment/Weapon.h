// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "02_Item/00_Equipment/Equipment.h"
#include "Weapon.generated.h"

// 무기 아이템
UCLASS()
class LADYBUG_API UWeapon : public UEquipment
{
	GENERATED_BODY()
	
public:
	// 아이템 사용
	virtual void UseItem(class APlayerCharacter* player) override;
	virtual void UseItem(class AWorldPlayerCharacter* player) override;

};
