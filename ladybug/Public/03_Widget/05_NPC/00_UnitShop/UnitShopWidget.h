// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitShopWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UUnitShopWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
		class UVerticalBox* VerticalBox_ShopList;
	UPROPERTY()
		class UVerticalBox* VerticalBox_MyUnitList;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Purchase;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Cancel;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ExitButton;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ShowInfo;
	UPROPERTY(meta = (BindWidget))
		class UUnitShopInfoWidget* UMG_UnitInfo;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_UnitName;
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_CharacterPreview;
protected:
	UPROPERTY()
		class ANPCCharacter* npcOwner;
	UPROPERTY()
		class UArmyListSlotWidget* selectedSlot;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UArmyListSlotWidget> UMG_ListSlotWidget;
	UPROPERTY(EditAnywhere)
		class UTextureRenderTarget2D* emptyPreviewImage;

	UPROPERTY()
		TArray<class UMonster*> purchaseList;
public:
	void Init();
	void Update(TArray<class UMonster*> npcShopList, TArray<class UMonster*> myList);
	void SetNPCOwner(class ANPCCharacter* npc) { npcOwner = npc; };
public:
	UFUNCTION()
		void SetSelectedSlot(class UArmyListSlotWidget* listSlot);

	UFUNCTION()
		void OnClickExit();
	UFUNCTION()
		void OnClickPurchase();
	UFUNCTION()
		void OnClickCancel();
	UFUNCTION()
		void OnClickInfo();
	UFUNCTION()
		void OnVisibilityChangedEvent(ESlateVisibility visible);
protected:
	void SetPreviewImage();
};
