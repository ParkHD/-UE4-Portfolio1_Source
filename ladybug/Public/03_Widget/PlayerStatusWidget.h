// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatusWidget.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UPlayerStatusWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY()
	class UProgressBar* ProgressBar_HP;
	UPROPERTY()
	class UProgressBar* ProgressBar_SP;
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ProgressBar_MP;
public:
	void Init();
	UFUNCTION()
	void UpdateHPProgressBar(class UStatusComponent* statusComp);
	UFUNCTION()
	void UpdateSPProgressBar(class UStatusComponent* statusComp);
	UFUNCTION()
		void UpdateMPProgressBar(class UStatusComponent* statusComp);
};
