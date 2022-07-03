// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArmyManagerWidget.generated.h"

// 총괄적으로 부대관리창 관리할 위젯
UCLASS()
class LADYBUG_API UArmyManagerWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY()
		class UArmyInfoWidget* UMG_ArmyInfo;			// 유닛 정보창 위젯

	UPROPERTY()
		class UVerticalBox* VerticalBox_ArmyList;		// 유닛 리스트를 담아 놓은 VerticalBox
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UArmyListSlotWidget> UMG_ArmyListSlotWidget;
	UPROPERTY(Meta = (BindWidget))
		class UButton* Button_Exit;
protected:
	UPROPERTY()
		class UArmyListSlotWidget* selectedSlot;		// 유닛 슬롯 리스트 중에 현재 선택된 슬롯

public:
	void Update(TArray<class UMonster*> armyList);		// 유닛 리스트 업데이트
protected:
	UFUNCTION()
		void OnVisibilityChangedEvent(ESlateVisibility visible);
	UFUNCTION()
		void OnExitButtonClicked();
	UFUNCTION()
		void SetSelectedSlot(class UArmyListSlotWidget* listSlot);
};
