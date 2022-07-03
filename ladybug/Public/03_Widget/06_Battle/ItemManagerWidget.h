// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemManagerWidget.generated.h"

// 전리품 관리창 및 NPC물건 상점 위젯
UCLASS()
class LADYBUG_API UItemManagerWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* VerticalBox_TargetList;	// 전리품 리스트
	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* VerticalBox_MyList;		// 내 인벤토리 리스트
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_BringIn;				// 가져오기 버튼
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_BringOut;				// 내보내기 버튼
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_CompleteButton;		// 완료 버튼

	UPROPERTY(meta = (BindWidget))
		class UItemInfoWidget* UMG_ItemInfo;		// 아이템 정보창 위젯
protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
		class ANPCCharacter* npcOwner;							// NPC
	UPROPERTY()
		class UItemSlotWidget* selectedSlot;					// 선택된 슬롯
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UItemSlotWidget> UMG_ListSlotWidget;

	UPROPERTY()
		TArray<class UItem*> purchaseList;			// 구매목록
	UPROPERTY()
		TArray<class UItem*> sellList;				// 판매목록
public:
	void Init();

	// 아이템 리스트 업데이트
	void Update(TArray<class UItem*> npcShopList, TArray<class UItem*> myList);
	void SetNPCOwner(class ANPCCharacter* npc) { npcOwner = npc; };
public:
	UFUNCTION()
		void SetSelectedSlot(class UItemSlotWidget* listSlot);	// 슬롯 선택 함수

	UFUNCTION()
		void OnClickExit();			// 나가기 함수
	UFUNCTION()
		void OnClickBringIn();		// 가져오기 함수
	UFUNCTION()
		void OnClickBringOut();		// 내보내기 함수

	UFUNCTION()
		void OnVisibilityChangedEvent(ESlateVisibility visible);
};
