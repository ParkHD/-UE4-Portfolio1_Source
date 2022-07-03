// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "HumanCharacter.generated.h"

UCLASS()
class LADYBUG_API AHumanCharacter : public AMonsterBaseCharacter
{
	GENERATED_BODY()
public:
	AHumanCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = InventoryComp)
		class UEquipmentComponent* EquipmentComponent;

public:
	class UEquipmentComponent* GetEquipmentComponent() { return EquipmentComponent; }

protected:
	// 처음에 장비할 물건
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UWeapon> defaultWeaponBP;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UWeapon> defaultSupWeaponBP;

public:
	void SetAttackMontage(class UAnimMontage* montage);
	void SetHitMontage(class UAnimMontage* montage);

	virtual void SetActionState(EActionState actionState) override;

};
