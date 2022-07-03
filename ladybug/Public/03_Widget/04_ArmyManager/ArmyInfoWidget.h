// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArmyInfoWidget.generated.h"

// 부대원의 능력치를 나타낼 위젯
UCLASS()
class LADYBUG_API UArmyInfoWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct()override;
protected:
	UPROPERTY()
		class UImage* Image_CharacterPreview;		// 캐릭터 이미지 preview

	// 캐릭터 정보
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
		class UTextureRenderTarget2D* defaultpreviewImage;	// 캐릭터 이미지 preview의 기본값(empty)
public:
	// 현재 클릭된 슬롯을 기준으로 캐릭터 정보 업데이트
	UFUNCTION()
		void SetUp(class UArmyListSlotWidget* selectedSlot);

	void Init();
};
