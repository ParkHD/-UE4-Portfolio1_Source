// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArmyListSlotWidget.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClickSlot, class UArmyListSlotWidget*, slot);

// 유닛 슬롯 위젯
UCLASS()
class LADYBUG_API UArmyListSlotWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
protected:
	// 유닛 정보
	UPROPERTY()
		class UImage* Image_CharacterImage;
	UPROPERTY()
		class UTextBlock* TextBlock_CharacterName;
	UPROPERTY()
		class UTextBlock* TextBlock_CharacterCount;

	UPROPERTY(Meta = (BindWidget))
		class UImage* Image_SelectedFrame;		// 슬롯이 선택되면 표시할 테두리 
public:
	class UImage* GetSelectedFrame() { return Image_SelectedFrame; }
protected:
	UPROPERTY()
		class UMonster* unit;					// 슬롯에 해당하는 유닛
public:
	class UMonster* GetUnit() { return unit; }
	void SetUp(class UMonster* army);
public:
	// 슬롯 클릭 시 테두리 표시 및 유닛 정보창 업데이트 할 델리게이트 함수
	FOnClickSlot OnClickSlot;
};
