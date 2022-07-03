// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "03_Widget/02_DragDrop/DragableWidget.h"
#include "EquipButtonWidget.generated.h"

// 어떤 종류의 장비 슬롯인가
UENUM(BlueprintType)
enum class EEquipSlotType : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	HELMET,		// 헬맷
	CAPE,		// 망토
	CLOTH,		// 갑옷
	GLOVE,		// 장갑
	SHOES,		// 신발
	WEAPON,		// 무기
};

// 장비 슬롯
UCLASS()
class LADYBUG_API UEquipButtonWidget : public UDragableWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		class UImage* Image_BackGround;		// 슬롯 배경
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_ItemImage;		// 아이템 이미지
protected:
	// 생성자 이전에 호출 -> 장비슬롯마다 다른 배경 이미지를 넣기 위함
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
protected:
	UPROPERTY(EditAnywhere)
		class UTexture2D* backGroundTexture;	// 슬롯 배경 이미지
	UPROPERTY(EditAnywhere)
		EEquipSlotType slotType;				// 장비 슬롯의 종류

	UPROPERTY()
		class UItem* itemInSlot;				// 슬롯의 있는 아이템

	int32 slotIndex = -1;						// 슬롯 인덱스 (0~3 : 무기 4~8 : 방어구)
	
	bool isEmpty = true;						// 슬롯이 비어있는가?
public:
	int32 GetIndex() { return slotIndex; }
	void SetIndex(int32 num) { slotIndex = num; }
	void SetUp(UItem* item);					// 슬롯 SetUp(이미지, 개수 등)
	void Init();								// 슬롯 초기화
};
