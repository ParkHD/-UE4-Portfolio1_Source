// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentWidget.generated.h"


// 장비창 위젯
UCLASS()
class LADYBUG_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* VerticalBox_ArmorList;	// 방어구 슬롯들
	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* VerticalBox_WeaponList;	// 무기 슬롯들
	UPROPERTY(meta = (BindWidget))
		class UStatInfoWidget* UMG_StatInfo;		// 스텟창

protected:
	virtual void NativeConstruct() override;

protected:
	TArray<class UEquipButtonWidget*> equipSlotList;	// 장비 슬롯 리스트

public:
	void UpdateSlot(class UEquipmentComponent* EquipComp);	// 장비 슬롯들 업데이트
	void UpdateStatInfo(class UStatusComponent* StatComp);	// 스텟창 업데이트
};
