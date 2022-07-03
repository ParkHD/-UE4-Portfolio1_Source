// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatusWidget.generated.h"

// 플레이어 상태창(HP, MP, Stamina) 위젯
UCLASS()
class LADYBUG_API UPlayerStatusWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
protected:
	UPROPERTY()
	class UProgressBar* ProgressBar_HP;		// HPBar
	UPROPERTY()
	class UProgressBar* ProgressBar_SP;		// StaminaBar
	UPROPERTY(meta = (BindWidget))
		class UProgressBar* ProgressBar_MP;	// MPBar
public:
	void Init();
	UFUNCTION()
		void UpdateHPProgressBar(class UStatusComponent* statusComp);	// HPBar Update
	UFUNCTION()
		void UpdateSPProgressBar(class UStatusComponent* statusComp);	// StaminaBar Update
	UFUNCTION()
		void UpdateMPProgressBar(class UStatusComponent* statusComp);	// MPBar Update
};
