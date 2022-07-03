// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPCDialogueWidget.generated.h"


// NPC�� ��ȭâ ����
UCLASS()
class LADYBUG_API UNPCDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_GotoShop;			// �������� ��ư
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ExitDialog;		// ��ȭ���� ��ư
protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY()
		class ANPCCharacter* ownerNPC;			// NPC

	// ���� ����
	UPROPERTY()
		class UUserWidget* shopWidget;			
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> UMG_shopWidget;
public:
	void SetOwnerNPC(class ANPCCharacter* npc) { ownerNPC = npc; }


	UFUNCTION()
		void OnClickShop();		// ���� ���� �Լ�
	UFUNCTION()
		void OnClickExit();		// ��ȭ ���� �Լ�
	UFUNCTION()
		void OnVisibilityChangedEvent(ESlateVisibility visible);
};
