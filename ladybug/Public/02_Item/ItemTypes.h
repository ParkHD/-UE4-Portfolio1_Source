// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ItemTypes.generated.h"

// �ɷ�ġ ����ü
USTRUCT(BlueprintType)
struct FStat
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxHP;	// �ִ� ü��
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxMP;	// �ִ� ����
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxSP;	// �ִ� Stamina

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Damage;	// �����
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Defence;	// ����
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AttackSpeed;	// ���ݼӵ�

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
// ������ Ÿ��
UENUM(BlueprintType)
enum class EItemType : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	ETC,		// ��Ÿ
	CONSUME,	// �Һ�
	EQUIPMENT	// ���
};

// ���Ÿ��
UENUM(BlueprintType)
enum class EEQuipmentType : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	ARMOR,	// ��
	WEAPON	// ����
};
// �� Ÿ��
UENUM(BlueprintType)
enum class EArmorType : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	HELMET,	// ���
	CAPE,	// ����
	CLOTH,	// ����
	GLOVE,	// �尩
	SHOES,	// �Ź�
};
// ���� Ÿ��
UENUM(BlueprintType)
enum class EWeaponType : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	ONEHAND,	// �Ѽչ���
	TWOHAND,	// �μչ���
	BOW,		// Ȱ
	SHIELD,		// ����
	ARROW,		// ȭ��
};

// ���� Ÿ��
UENUM(BlueprintType)
enum class EAttackType : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	Melee,		// �ٰŸ� ����
	Range,		// ���Ÿ� ����
};

// ������ ���� ����ü
USTRUCT(BlueprintType)
struct FItemInformation : public FTableRowBase
{
	GENERATED_BODY()
public:

	// ������ Actor���� ������class ������ �ʿ���Class
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UItem> Item_Class;

	UPROPERTY(EditAnywhere)
		EItemType item_Type;	

	UPROPERTY(EditAnywhere)
		FName item_Code;
	UPROPERTY(EditAnywhere)
		FString item_Name;					// ������ �̸�
	UPROPERTY(EditAnywhere)
		FString item_Description_Short;		// ������ ª�� ����
	UPROPERTY(EditAnywhere)
		FString item_Description_Long;		// ������ �� ����
	UPROPERTY(EditAnywhere)
		class UTexture2D* item_Image;		// ������ �̹���
	UPROPERTY(EditAnywhere)
		int32 item_MaxCount;				// ������ �ִ� ����
	UPROPERTY(EditAnywhere)
		int32 item_Count;					// ������ ����

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
		FStat equipmentStatMax;					// �ִ� ���� �� �ִ� �ɷ�ġ
	UPROPERTY(EditAnywhere)
		FStat equipmentStatMin;					// �ּ� ���� �� �ִ� �ɷ�ġ

	UPROPERTY(EditAnywhere)
		class USkeletalMesh* equipmentMesh;		// ����� SkeletalMesh

	UPROPERTY(EditAnywhere)
		bool bEquipped = false;					// ���� �����ϰ� �ִ���
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
		class UAnimBlueprint* weaponAnimationBP;				// ���� AnimBluePrint
	UPROPERTY(EditAnywhere)
		class UAnimMontage* attackMontage;						// ���� ��Ÿ��
	UPROPERTY(EditAnywhere)
		class UAnimMontage* hitMontage;							// �ǰ� ��Ÿ��
	UPROPERTY(EditAnywhere)
		FName equipSocketName;									// ������ ��ġ : ����
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AProjectileActor> projectileActor;	// ���Ⱑ �߻� �� �� �ִ� ProjectileActor
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class USKillBase>> Weapon_Skills;	// ���Ⱑ ������ �ִ� ��ųList

	UPROPERTY(EditAnywhere)
		bool isMainWeapon;										// ���ι����ΰ�?
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
	// ȸ����
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
