// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "02_Item/ItemTypes.h"
#include "PlayerSkillWidget.generated.h"

// BattleCharacter의 스킬 정보창 위젯
UCLASS()
class LADYBUG_API UPlayerSkillWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_Skill1_Image;	// 스킬1 이미지
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_Skill2_Image;	// 스킬2 이미지
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_WeaponImage;	// 현재 장착하고 있는 무기 종류(근거리 원거리)

	UPROPERTY(meta = (BindWidget))
		class UImage* Image_LockSkill1;		// 스킬1 사용가능 여부 위젯
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_LockSkill2;		// 스킬2 사용가능 여부 위젯
protected:
	virtual void NativeConstruct()override;
protected:
	UPROPERTY(EditAnywhere)
		class UTexture2D* ArrowImage;			// 원거리 공격을 나타낼 위젯
	UPROPERTY(EditAnywhere)
		class UTexture2D* OneHandSwordImage;	// 근거리 공격을 나타낼 위젯

public:
	UFUNCTION()
		void SetUp(FWeaponInformation weaponInfo);	// 스킬 정보 업데이트
	UFUNCTION()
		void UpdateSkill1CoolTime(bool skillAble);	// 스킬 사용가능한지 업데이트
	UFUNCTION()
		void UpdateSkill2CoolTime(bool skillAble);	// 스킬 사용가능한지 업데이트
	void Init();
};
