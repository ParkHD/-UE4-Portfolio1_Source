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
	// ����� ��
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

	// ����� ���� �ĺ�
	UPROPERTY(VisibleAnywhere)
		TArray<class UWeapon*> weaponList;
	UPROPERTY(VisibleAnywhere)
		int32 curWeaponIndex = 0;
	// ����� ����
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
	// ó���� ����� ����
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UWeapon> mainWeaponBP;
	// ó���� ����� ����
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UWeapon> supWeaponBP;
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class UWeapon>> weaponBPList;

public:
	// ���� ����
	bool IsWeaponListEmpty();
	void AddWeaponList(class UWeapon* weapon);
	bool IsWeaponListFull();
	void RemoveWeaponList(int32 index);
	void SwapWeaponUp(bool isUp);
	void EquipWeapon(class UWeapon* weapon);
	void UpdateWidget();

	void EquipMeleeWeapon();
	void EquipRangeWeapon();

	//�� ����
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
	// ���� ����
	void UnEquipWeapon();
	void EquipWeapon(int32 weaponIndex);
	void EquipSupWeapon(class UWeapon* SupWeapon);

	// �� ����


public:
	FOnChangeWeapon OnChangeWeapon;		  // ���ⱳü ����
	FOnUpdateEquiment OnUpdateEquiment;	  // ��� ���� �Ǵ� ���� �� �� ������Ʈ
	FOnChangeEquipment OnChangeEquipment; // ���â ���� ����


public:
	//WorldCharacter
	void SetEquipComponentData(FEquipComponentSave EquipCompData);
	//BattleCharacter
	void SetBattleCharacter(class UEquipmentComponent* EquipComp);
};

