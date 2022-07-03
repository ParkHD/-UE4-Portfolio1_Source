// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * ��ȣ�ۿ� �������̽� Ŭ����
 */
class LADYBUG_API IInteractionInterface
{
	GENERATED_BODY()
		
public:
	// Ÿ���� �̸�
	virtual const FText GetName() { return FText::GetEmpty(); };
	// Ÿ�ٰ� interaction �Լ�
	virtual void InterAction(class APlayerCharacter* caller) {};
};
