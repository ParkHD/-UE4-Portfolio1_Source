// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "WidgetDragDropOperation.generated.h"

// 드래그 시 전달할 정보
UCLASS()
class LADYBUG_API UWidgetDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	// 드래그 중인 위젯의 정보 = 참조 위젯
	UPROPERTY()
		class UUserWidget* widgetRef;
};
