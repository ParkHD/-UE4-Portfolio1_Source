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
 * 상호작용 인터페이스 클래스
 */
class LADYBUG_API IInteractionInterface
{
	GENERATED_BODY()
		
public:
	// 타겟의 이름
	virtual const FText GetName() { return FText::GetEmpty(); };
	// 타겟과 interaction 함수
	virtual void InterAction(class APlayerCharacter* caller) {};
};
