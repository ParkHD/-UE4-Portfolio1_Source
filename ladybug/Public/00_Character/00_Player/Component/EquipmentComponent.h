// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "02_Item/ItemTypes.h"
#include "97_SaveGame/SaveVariable.h"
#include "EquipmentComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeWeapon, FWeaponInformation, WeaponInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateEquiment, class UEquipmentComponent*, EquipComp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeEquipment, class UStatusComponent*, statComp);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LADYBUG_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// 장비한 방어구
	UPROPERTY(VisibleAnywhere)
		class UArmor* Helmet;
	UPROPERTY(VisibleAnywhere)
		class UArmor* Cape;
	UPROPERTY(VisibleAnywhere)
		class UArmor* Cloth;
	UPROPERTY(VisibleAnywhere)
		class UArmor* Glove;
	UPROPERTY(VisibleAnywhere)
		class UArmor* Shoes;

	// 장비한 물건 후보
	UPROPERTY(VisibleAnywhere)
		TArray<class UWeapon*> weaponList;
	UPROPERTY(VisibleAnywhere)
		int32 curWeaponIndex = 0;
	// 장비한 무기
	UPROPERTY(VisibleAnywhere)
		class UWeapon* equippedWeapon;
	UPROPERTY(VisibleAnywhere)
		class UWeapon* equippedSupWeapon;

public:
	class UWeapon* GetEquippedWeapon() { return equippedWeapon; }
	class UWeapon* GetEquippedSubWeapon() { return equippedSupWeapon; }
	class TArray<UWeapon*>& GetWeaponList() { return weaponList; }

	class UArmor* GetHelmet() { return Helmet; }
	class UArmor* GetCape() { return Cape; }
	class UArmor* GetCloth() { return Cloth; }
	class UArmor* GetGlove() { return Glove; }
	class UArmor* GetShoes() { return Shoes; }
protected:
	// 처음에 장비할 물건
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UWeapon> mainWeaponBP;
	// 처음에 장비할 물건
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UWeapon> supWeaponBP;
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class UWeapon>> weaponBPList;

public:
	// 무기 관련
	bool IsWeaponListEmpty();
	void AddWeaponList(class UWeapon* weapon);
	bool IsWeaponListFull();
	void RemoveWeaponList(int32 index);
	void SwapWeaponUp(bool isUp);
	void EquipWeapon(class UWeapon* weapon);
	void UpdateWidget();

	void EquipMeleeWeapon();
	void EquipRangeWeapon();

	//방어구 관련
	void EquipHelmet(class UArmor* armor);
	void EquipCape(class UArmor* armor);
	void EquipCloth(class UArmor* armor);
	void EquipGlove(class UArmor* armor);
	void EquipShoes(class UArmor* armor);
	bool UnEquipHelmet();
	void UnEquipCape();
	void UnEquipCloth();
	void UnEquipGlove();
	void UnEquipShoes();

protected:
	// 무기 관련
	void UnEquipWeapon();
	void EquipWeapon(int32 weaponIndex);
	void EquipSupWeapon(class UWeapon* SupWeapon);

	// 방어구 관련


public:
	FOnChangeWeapon OnChangeWeapon;		  // 무기교체 위젯
	FOnUpdateEquiment OnUpdateEquiment;	  // 장비 장착 또는 해제 할 때 업데이트
	FOnChangeEquipment OnChangeEquipment; // 장비창 스텟 변동


public:
	//WorldCharacter
	void SetEquipComponentData(FEquipComponentSave EquipCompData);
	//BattleCharacter
	void SetBattleCharacter(class UEquipmentComponent* EquipComp);
};

