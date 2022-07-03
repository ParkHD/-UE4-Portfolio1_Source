// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UnitShopWidget.generated.h"

// NPC ���� ���� ����
UCLASS()
class LADYBUG_API UUnitShopWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		class UVerticalBox* VerticalBox_ShopList;		// �Ǹ� ����Ʈ
	UPROPERTY()
		class UVerticalBox* VerticalBox_MyUnitList;		// ���� ���� ����Ʈ
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Purchase;					// ���Ź�ư
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_Cancel;					// ��ҹ�ư
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ExitButton;				// ������ ��ư
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ShowInfo;					// ���� �������� ��ư
	UPROPERTY(meta = (BindWidget))
		class UUnitShopInfoWidget* UMG_UnitInfo;		// ���� ���� ����
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_UnitName;			// ������ �̸�
	UPROPERTY(meta = (BindWidget))
		class UImage* Image_CharacterPreview;			// ���� preview
protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
		class ANPCCharacter* npcOwner;					// ������ ������ �ִ� owner(NPC)
	UPROPERTY()
		class UArmyListSlotWidget* selectedSlot;		// ���� ���õ� ����
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UArmyListSlotWidget> UMG_ListSlotWidget;
	UPROPERTY(EditAnywhere)
		class UTextureRenderTarget2D* emptyPreviewImage;	// ���� preview�̹����� �⺻��(empty)

	UPROPERTY()
		TArray<class UMonster*> purchaseList;			// ���� ���
public:
	void Init();

	// ���� ������Ʈ
	void Update(TArray<class UMonster*> npcShopList, TArray<class UMonster*> myList);
	void SetNPCOwner(class ANPCCharacter* npc) { npcOwner = npc; };
public:
	// ���ε� �� �Լ�
	UFUNCTION()
		void SetSelectedSlot(class UArmyListSlotWidget* listSlot);	// ���� ���� �Լ�
	UFUNCTION()
		void OnClickExit();			// ������ ��ư �Լ�
	UFUNCTION()
		void OnClickPurchase();		// ���� ��ư �Լ�
	UFUNCTION()
		void OnClickCancel();		// ��� ��ư �Լ�
	UFUNCTION()
		void OnClickInfo();			// ���� ���� ���� �Լ�
	UFUNCTION()
		void OnVisibilityChangedEvent(ESlateVisibility visible);	// ���� Visibility ���� �� �� �Լ�
protected:
	// preview�̹��� ����
	void SetPreviewImage();
};
