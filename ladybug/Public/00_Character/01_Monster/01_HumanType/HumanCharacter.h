// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "HumanCharacter.generated.h"

// 인간형 타입 몬스터 BattleCharacter
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
	// 인간형은 무기를 스왑 가능하게 하기 위하여 장비 컴포넌트 추가
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
	// 무기에 따른 몽타주 설정
	void SetAttackMontage(class UAnimMontage* montage);
	void SetHitMontage(class UAnimMontage* montage);

	virtual void SetActionState(EActionState actionState) override;
};
