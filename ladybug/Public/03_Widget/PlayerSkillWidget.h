// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "02_Item/ItemTypes.h"
#include "PlayerSkillWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UPlayerSkillWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_Skill1_Image;
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_Skill2_Image;
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_WeaponImage;

	UPROPERTY(meta = (BindWidget))
		class UImage* Image_LockSkill1;
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_LockSkill2;
protected:
	virtual void NativeConstruct()override;
protected:
	UPROPERTY(EditAnywhere)
		class UTexture2D* ArrowImage;
	UPROPERTY(EditAnywhere)
		class UTexture2D* OneHandSwordImage;

public:
	UFUNCTION()
		void SetUp(FWeaponInformation weaponInfo);
	UFUNCTION()
		void UpdateSkill1CoolTime(bool skillAble);
	UFUNCTION()
		void UpdateSkill2CoolTime(bool skillAble);
	void Init();
};
