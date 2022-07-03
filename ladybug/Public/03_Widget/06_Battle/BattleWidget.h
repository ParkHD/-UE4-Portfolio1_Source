// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleWidget.generated.h"

// ���� ������ �� �������� ���� â
UCLASS()
class LADYBUG_API UBattleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UArmyListWidget* UMG_TargetArmyList;		// ��� �δ� ����Ʈ
	UPROPERTY(meta = (BindWidget))
		class UArmyListWidget* UMG_MyArmyList;			// ���� �δ� ����Ʈ
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_StartBattle;				// �������� ��ư
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_RunAway;					// �������� ��ư
protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY()
		class AWorldPlayerCharacter* player;
	UPROPERTY()
		class AWorldMonsterCharacter* target;
public:
	
	void SetUp(class AWorldPlayerCharacter* Player, class AWorldMonsterCharacter* Target);
	// ���� ����� �δ븮��Ʈ ������Ʈ
	void UpdateSlot();
protected:
	UFUNCTION()
		void OnClickStartBattleEvent();	// �������� �Լ�
	UFUNCTION()
		void OnClickRunAwayEvent();		// �������� �Լ�
	UFUNCTION()
		void OnVisibilityChangeEvent(ESlateVisibility visible);
};
