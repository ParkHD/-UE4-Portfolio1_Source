// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentWidget.generated.h"


// ���â ����
UCLASS()
class LADYBUG_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* VerticalBox_ArmorList;	// �� ���Ե�
	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* VerticalBox_WeaponList;	// ���� ���Ե�
	UPROPERTY(meta = (BindWidget))
		class UStatInfoWidget* UMG_StatInfo;		// ����â

protected:
	virtual void NativeConstruct() override;

protected:
	TArray<class UEquipButtonWidget*> equipSlotList;	// ��� ���� ����Ʈ

public:
	void UpdateSlot(class UEquipmentComponent* EquipComp);	// ��� ���Ե� ������Ʈ
	void UpdateStatInfo(class UStatusComponent* StatComp);	// ����â ������Ʈ
};
