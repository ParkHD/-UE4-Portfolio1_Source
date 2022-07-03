// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPCDialogueWidget.generated.h"


// NPC와 대화창 위젯
UCLASS()
class LADYBUG_API UNPCDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_GotoShop;			// 상점열기 버튼
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ExitDialog;		// 대화종료 버튼
protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY()
		class ANPCCharacter* ownerNPC;			// NPC

	// 상점 위젯
	UPROPERTY()
		class UUserWidget* shopWidget;			
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> UMG_shopWidget;
public:
	void SetOwnerNPC(class ANPCCharacter* npc) { ownerNPC = npc; }


	UFUNCTION()
		void OnClickShop();		// 삼점 열기 함수
	UFUNCTION()
		void OnClickExit();		// 대화 종료 함수
	UFUNCTION()
		void OnVisibilityChangedEvent(ESlateVisibility visible);
};
