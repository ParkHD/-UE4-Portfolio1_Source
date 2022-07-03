// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Notify_PlaySound.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UNotify_PlaySound : public UAnimNotify
{
	GENERATED_BODY()
public:
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
protected:
	UPROPERTY(EditAnywhere)
		class USoundBase* soundToPlay;
	UPROPERTY(EditAnywhere)
		bool bAttenuation = true;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bAttenuation == true"))
		float falloffDistance = 4000.f;
};
