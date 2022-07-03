// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "WidgetDragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UWidgetDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
public:
	// �巡�� ���� ������ ����
	UPROPERTY()
		class UUserWidget* widgetRef;
};
