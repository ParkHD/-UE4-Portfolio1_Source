// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Notify_SetLocation.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UNotify_SetLocation : public UAnimNotify
{
	GENERATED_BODY()
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
protected:
	UPROPERTY(EditAnywhere)
		float value;
};
