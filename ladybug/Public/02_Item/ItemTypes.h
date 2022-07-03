// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "ItemTypes.generated.h"

// 능력치 구조체
USTRUCT(BlueprintType)
struct FStat
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxHP;	// 최대 체력
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxMP;	// 최대 마나
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxSP;	// 최대 Stamina

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Damage;	// 대미지
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Defence;	// 방어력
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float AttackSpeed;	// 공격속도

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
// 아이템 타입
UENUM(BlueprintType)
enum class EItemType : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	ETC,		// 기타
	CONSUME,	// 소비
	EQUIPMENT	// 장비
};

// 장비타입
UENUM(BlueprintType)
enum class EEQuipmentType : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	ARMOR,	// 방어구
	WEAPON	// 무기
};
// 방어구 타입
UENUM(BlueprintType)
enum class EArmorType : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	HELMET,	// 헬맷
	CAPE,	// 망토
	CLOTH,	// 갑옷
	GLOVE,	// 장갑
	SHOES,	// 신발
};
// 무기 타입
UENUM(BlueprintType)
enum class EWeaponType : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	ONEHAND,	// 한손무기
	TWOHAND,	// 두손무기
	BOW,		// 활
	SHIELD,		// 방패
	ARROW,		// 화살
};

// 공격 타입
UENUM(BlueprintType)
enum class EAttackType : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	Melee,		// 근거리 무기
	Range,		// 원거리 무기
};

// 아이템 정보 구조체
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
		FString item_Name;					// 아이템 이름
	UPROPERTY(EditAnywhere)
		FString item_Description_Short;		// 아이템 짧은 설명
	UPROPERTY(EditAnywhere)
		FString item_Description_Long;		// 아이템 긴 설명
	UPROPERTY(EditAnywhere)
		class UTexture2D* item_Image;		// 아이템 이미지
	UPROPERTY(EditAnywhere)
		int32 item_MaxCount;				// 아이템 최대 개수
	UPROPERTY(EditAnywhere)
		int32 item_Count;					// 아이템 개수

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
		FStat equipmentStatMax;					// 최대 나올 수 있는 능력치
	UPROPERTY(EditAnywhere)
		FStat equipmentStatMin;					// 최소 나올 수 있는 능력치

	UPROPERTY(EditAnywhere)
		class USkeletalMesh* equipmentMesh;		// 장비의 SkeletalMesh

	UPROPERTY(EditAnywhere)
		bool bEquipped = false;					// 현재 장착하고 있는지
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
		class UAnimBlueprint* weaponAnimationBP;				// 무기 AnimBluePrint
	UPROPERTY(EditAnywhere)
		class UAnimMontage* attackMontage;						// 공격 몽타주
	UPROPERTY(EditAnywhere)
		class UAnimMontage* hitMontage;							// 피격 몽타주
	UPROPERTY(EditAnywhere)
		FName equipSocketName;									// 장착할 위치 : 소켓
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AProjectileActor> projectileActor;	// 무기가 발사 할 수 있는 ProjectileActor
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class USKillBase>> Weapon_Skills;	// 무기가 가지고 있는 스킬List

	UPROPERTY(EditAnywhere)
		bool isMainWeapon;										// 메인무기인가?
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
	// 회복량
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
