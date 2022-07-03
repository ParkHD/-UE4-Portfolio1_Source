// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPBarWidget.generated.h"


// AI(BattleCharacter)�� HPBar Widget
UCLASS()
class LADYBUG_API UHPBarWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
		virtual void NativeConstruct() override;
protected:
	UPROPERTY()
		class UProgressBar* ProgressBar_HPBar;		

public:
	void Init();

	// owner�� HP�� ���� ���� ������Ʈ
	UFUNCTION()
		void UpdateHPBar(class UStatusComponent* statusComp);
};