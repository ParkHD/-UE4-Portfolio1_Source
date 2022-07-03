// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArmyInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UArmyInfoWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct()override;
protected:
	UPROPERTY()
		class UImage* Image_CharacterPreview;
	UPROPERTY()
		class UTextBlock* TextBlock_UnitName;
	UPROPERTY()
		class UTextBlock* TextBlock_UnitDecription;

	UPROPERTY()
		class UTextBlock* TextBlock_MaxHP;
	UPROPERTY()
		class UTextBlock* TextBlock_MaxMP;
	UPROPERTY()
		class UTextBlock* TextBlock_MaxSP;
	UPROPERTY()
		class UTextBlock* TextBlock_Damage;
	UPROPERTY()
		class UTextBlock* TextBlock_Defence;
	UPROPERTY()
		class UTextBlock* TextBlock_Skill;
protected:
	UPROPERTY(EditAnywhere)
		class UTextureRenderTarget2D* defaultpreviewImage;
public:
	UFUNCTION()
		void SetUp(class UArmyListSlotWidget* selectedSlot);

	void Init();
};
