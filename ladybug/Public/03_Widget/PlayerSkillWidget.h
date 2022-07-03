// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "02_Item/ItemTypes.h"
#include "PlayerSkillWidget.generated.h"

// BattleCharacter�� ��ų ����â ����
UCLASS()
class LADYBUG_API UPlayerSkillWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_Skill1_Image;	// ��ų1 �̹���
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_Skill2_Image;	// ��ų2 �̹���
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_WeaponImage;	// ���� �����ϰ� �ִ� ���� ����(�ٰŸ� ���Ÿ�)

	UPROPERTY(meta = (BindWidget))
		class UImage* Image_LockSkill1;		// ��ų1 ��밡�� ���� ����
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_LockSkill2;		// ��ų2 ��밡�� ���� ����
protected:
	virtual void NativeConstruct()override;
protected:
	UPROPERTY(EditAnywhere)
		class UTexture2D* ArrowImage;			// ���Ÿ� ������ ��Ÿ�� ����
	UPROPERTY(EditAnywhere)
		class UTexture2D* OneHandSwordImage;	// �ٰŸ� ������ ��Ÿ�� ����

public:
	UFUNCTION()
		void SetUp(FWeaponInformation weaponInfo);	// ��ų ���� ������Ʈ
	UFUNCTION()
		void UpdateSkill1CoolTime(bool skillAble);	// ��ų ��밡������ ������Ʈ
	UFUNCTION()
		void UpdateSkill2CoolTime(bool skillAble);	// ��ų ��밡������ ������Ʈ
	void Init();
};
