// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitShopWidget.generated.h"

// NPC 유닛 상점 위젯
UCLASS()
class LADYBUG_API UUnitShopWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UVerticalBox* VerticalBox_ShopList;		// 판매 리스트
	UPROPERTY()
		class UVerticalBox* VerticalBox_MyUnitList;		// 나의 유닛 리스트
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Purchase;					// 구매버튼
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Cancel;					// 취소버튼
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ExitButton;				// 나가기 버튼
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ShowInfo;					// 유닛 정보보기 버튼
	UPROPERTY(meta = (BindWidget))
		class UUnitShopInfoWidget* UMG_UnitInfo;		// 유닛 정보 위젯
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_UnitName;			// 유닛의 이름
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_CharacterPreview;			// 유닛 preview
protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
		class ANPCCharacter* npcOwner;					// 위젯을 가지고 있는 owner(NPC)
	UPROPERTY()
		class UArmyListSlotWidget* selectedSlot;		// 현재 선택된 슬롯
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UArmyListSlotWidget> UMG_ListSlotWidget;
	UPROPERTY(EditAnywhere)
		class UTextureRenderTarget2D* emptyPreviewImage;	// 유닛 preview이미지의 기본값(empty)

	UPROPERTY()
		TArray<class UMonster*> purchaseList;			// 구매 목록
public:
	void Init();

	// 위젯 업데이트
	void Update(TArray<class UMonster*> npcShopList, TArray<class UMonster*> myList);
	void SetNPCOwner(class ANPCCharacter* npc) { npcOwner = npc; };
public:
	// 바인딩 될 함수
	UFUNCTION()
		void SetSelectedSlot(class UArmyListSlotWidget* listSlot);	// 슬롯 선택 함수
	UFUNCTION()
		void OnClickExit();			// 나가기 버튼 함수
	UFUNCTION()
		void OnClickPurchase();		// 구매 버튼 함수
	UFUNCTION()
		void OnClickCancel();		// 취소 버튼 함수
	UFUNCTION()
		void OnClickInfo();			// 유닛 정보 보기 함수
	UFUNCTION()
		void OnVisibilityChangedEvent(ESlateVisibility visible);	// 위젯 Visibility 변경 될 때 함수
protected:
	// preview이미지 설정
	void SetPreviewImage();
};
