// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemManagerWidget.generated.h"

// ����ǰ ����â �� NPC���� ���� ����
UCLASS()
class LADYBUG_API UItemManagerWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* VerticalBox_TargetList;	// ����ǰ ����Ʈ
	UPROPERTY(meta = (BindWidget))
		class UVerticalBox* VerticalBox_MyList;		// �� �κ��丮 ����Ʈ
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_BringIn;				// �������� ��ư
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_BringOut;				// �������� ��ư
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_CompleteButton;		// �Ϸ� ��ư

	UPROPERTY(meta = (BindWidget))
		class UItemInfoWidget* UMG_ItemInfo;		// ������ ����â ����
protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY()
		class ANPCCharacter* npcOwner;							// NPC
	UPROPERTY()
		class UItemSlotWidget* selectedSlot;					// ���õ� ����
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UItemSlotWidget> UMG_ListSlotWidget;

	UPROPERTY()
		TArray<class UItem*> purchaseList;			// ���Ÿ��
	UPROPERTY()
		TArray<class UItem*> sellList;				// �ǸŸ��
public:
	void Init();

	// ������ ����Ʈ ������Ʈ
	void Update(TArray<class UItem*> npcShopList, TArray<class UItem*> myList);
	void SetNPCOwner(class ANPCCharacter* npc) { npcOwner = npc; };
public:
	UFUNCTION()
		void SetSelectedSlot(class UItemSlotWidget* listSlot);	// ���� ���� �Լ�

	UFUNCTION()
		void OnClickExit();			// ������ �Լ�
	UFUNCTION()
		void OnClickBringIn();		// �������� �Լ�
	UFUNCTION()
		void OnClickBringOut();		// �������� �Լ�

	UFUNCTION()
		void OnVisibilityChangedEvent(ESlateVisibility visible);
};
