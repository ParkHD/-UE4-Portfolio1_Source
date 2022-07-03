// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EndJumpAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UEndJumpAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
protected:
	//타이머정보 저장댐
	FTimerHandle EndJumpTimerHandle;
};
