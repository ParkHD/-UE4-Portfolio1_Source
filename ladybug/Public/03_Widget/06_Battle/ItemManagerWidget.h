// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemManagerWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UItemManagerWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* VerticalBox_TargetList;
	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* VerticalBox_MyList;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_BringIn;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_BringOut;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_CompleteButton;

	UPROPERTY(meta = (BindWidget))
		class UItemInfoWidget* UMG_ItemInfo;

protected:
	UPROPERTY()
		class ANPCCharacter* npcOwner;
	UPROPERTY()
		class UItemSlotWidget* selectedSlot;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UItemSlotWidget> UMG_ListSlotWidget;
	UPROPERTY(EditAnywhere)
		class UTextureRenderTarget2D* emptyPreviewImage;

	UPROPERTY()
		TArray<class UItem*> purchaseList;
	UPROPERTY()
		TArray<class UItem*> sellList;
public:
	void Init();
	void Update(TArray<class UItem*> npcShopList, TArray<class UItem*> myList);
	void SetNPCOwner(class ANPCCharacter* npc) { npcOwner = npc; };
public:
	UFUNCTION()
		void SetSelectedSlot(class UItemSlotWidget* listSlot);

	UFUNCTION()
		void OnClickExit();
	UFUNCTION()
		void OnClickBringIn();
	UFUNCTION()
		void OnClickBringOut();

	UFUNCTION()
		void OnVisibilityChangedEvent(ESlateVisibility visible);
protected:
	void SetPreviewImage();
};
