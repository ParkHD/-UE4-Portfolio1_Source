// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatInfoWidget.generated.h"

// 캐릭터 스텟 나타낼 위젯
UCLASS()
class LADYBUG_API UStatInfoWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_MaxHP;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_MaxMP;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_MaxSP;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_Damage;
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_Defence;
protected:
	virtual void NativeConstruct() override;
public:
	// 스텟 창 업데이트
	UFUNCTION()
		void Update(class UStatusComponent* StatComp);

	// 스텟 창 초기화
	void Init();
};
