// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleWidget.generated.h"

// 몬스터 만났을 때 전투진입 관리 창
UCLASS()
class LADYBUG_API UBattleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UArmyListWidget* UMG_TargetArmyList;		// 상대 부대 리스트
	UPROPERTY(meta = (BindWidget))
		class UArmyListWidget* UMG_MyArmyList;			// 나의 부대 리스트
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_StartBattle;				// 전투시작 버튼
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_RunAway;					// 도망가기 버튼
protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY()
		class AWorldPlayerCharacter* player;
	UPROPERTY()
		class AWorldMonsterCharacter* target;
public:
	
	void SetUp(class AWorldPlayerCharacter* Player, class AWorldMonsterCharacter* Target);
	// 나와 상대의 부대리스트 업데이트
	void UpdateSlot();
protected:
	UFUNCTION()
		void OnClickStartBattleEvent();	// 전투시작 함수
	UFUNCTION()
		void OnClickRunAwayEvent();		// 도망가기 함수
	UFUNCTION()
		void OnVisibilityChangeEvent(ESlateVisibility visible);
};
