// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPCDialogueWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UNPCDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_GotoShop;
	UPROPERTY(meta = (BindWidget))
		class UButton* Button_ExitDialog;
protected:
	UPROPERTY()
		class ANPCCharacter* ownerNPC;
	UPROPERTY()
		class UUserWidget* shopWidget;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> UMG_shopWidget;
public:
	void SetOwnerNPC(class ANPCCharacter* npc) { ownerNPC = npc; }
	UFUNCTION()
		void OnClickShop();
	UFUNCTION()
		void OnClickExit();

	UFUNCTION()
		void OnVisibilityChangedEvent(ESlateVisibility visible);
};
