// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VillageNameWidget.generated.h"

// WorldLevel에서 마을 이름 위젯
UCLASS()
class LADYBUG_API UVillageNameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TextBlock_VillageName;	// 마을 이름
public:
	void SetUp(FString villageName);		// 마을 이름 TEXT설정
};
