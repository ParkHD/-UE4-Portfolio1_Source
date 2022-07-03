// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ItemTypes.generated.h"

USTRUCT(BlueprintType)
struct FStat
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxHP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxMP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxSP;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Damage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Defence;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AttackSpeed;

	FStat& operator + (const FStat& target)
	{
		this->MaxHP += target.MaxHP;
		this->MaxMP += target.MaxMP;
		this->MaxSP += target.MaxSP;

		this->Damage += target.Damage;
		this->Defence += target.Defence;
		this->AttackSpeed += target.AttackSpeed;

		return *this;
	}
	FStat& operator +=(const FStat& target)
	{
		this->MaxHP += target.MaxHP;
		this->MaxMP += target.MaxMP;
		this->MaxSP += target.MaxSP;

		this->Damage += target.Damage;
		this->Defence += target.Defence;
		this->AttackSpeed += target.AttackSpeed;

		return *this;
	}
	FStat& operator - (const FStat& target)
	{
		this->MaxHP -= target.MaxHP;
		this->MaxMP -= target.MaxMP;
		this->MaxSP -= target.MaxSP;

		this->Damage -= target.Damage;
		this->Defence -= target.Defence;
		this->AttackSpeed -= target.AttackSpeed;

		return *this;
	}
	FStat& operator -= (const FStat& target)
	{
		this->MaxHP -= target.MaxHP;
		this->MaxMP -= target.MaxMP;
		this->MaxSP -= target.MaxSP;

		this->Damage -= target.Damage;
		this->Defence -= target.Defence;
		this->AttackSpeed -= target.AttackSpeed;

		return *this;
	}
};
UENUM(BlueprintType)
enum class EItemType : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	ETC,
	CONSUME,
	EQUIPMENT
};

UENUM(BlueprintType)
enum class EEQuipmentType : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	ARMOR,
	WEAPON
};

UENUM(BlueprintType)
enum class EArmorType : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	HELMET,
	CAPE,
	CLOTH,
	GLOVE,
	SHOES,
};
UENUM(BlueprintType)
enum class EWeaponType : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	ONEHAND,
	TWOHAND,
	BOW,
	SHIELD,
	ARROW,
};
UENUM(BlueprintType)
enum class EAttackType : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	Melee,
	Range,
};
USTRUCT(BlueprintType)
struct FItemInformation : public FTableRowBase
{
	GENERATED_BODY()
public:

	// 아이템 Actor에서 아이템class 생성시 필요한Class
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UItem> Item_Class;

	UPROPERTY(EditAnywhere)
		EItemType item_Type;

	UPROPERTY(EditAnywhere)
		FName item_Code;
	UPROPERTY(EditAnywhere)
		FString item_Name;
	UPROPERTY(EditAnywhere)
		FString item_Description_Short;
	UPROPERTY(EditAnywhere)
		FString item_Description_Long;
	UPROPERTY(EditAnywhere)
		class UTexture2D* item_Image;
	UPROPERTY(EditAnywhere)
		int32 item_MaxCount;
	UPROPERTY(EditAnywhere)
		int32 item_Count;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AItemActor> itemActorClass;
};

USTRUCT(BlueprintType)
struct FEquipmentInformation : public FItemInformation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		EEQuipmentType equipmentType;

	UPROPERTY(EditAnywhere)
		FStat equipmentStatMax;
	UPROPERTY(EditAnywhere)
		FStat equipmentStatMin;

	UPROPERTY(EditAnywhere)
		class USkeletalMesh* equipmentMesh;

	UPROPERTY(EditAnywhere)
		bool bEquipped = false;
};

USTRUCT(BlueprintType)
struct FArmorInformation : public FEquipmentInformation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		EArmorType armorType;

};

USTRUCT(BlueprintType)
struct FWeaponInformation : public FEquipmentInformation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		EWeaponType WeaponType;
	UPROPERTY(EditAnywhere)
		EAttackType AttackType;
	UPROPERTY(EditAnywhere)
		class UAnimBlueprint* weaponAnimationBP;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* attackMontage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* hitMontage;
	UPROPERTY(EditAnywhere)
		FName equipSocketName;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AProjectileActor> projectileActor;
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class USKillBase>> Weapon_Skills;

	UPROPERTY(EditAnywhere)
		bool isMainWeapon;
};
USTRUCT(BlueprintType)
struct FConSumeInformation : public FItemInformation
{
	GENERATED_BODY()
public:

};

USTRUCT(BlueprintType)
struct FPotionInformation : public FConSumeInformation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		float recoverHP;
	UPROPERTY(EditAnywhere)
		float recoverMP;
	UPROPERTY(EditAnywhere)
		float recoverSP;

};

UCLASS()
class LADYBUG_API UItemTypes : public UObject
{
	GENERATED_BODY()
	
};
