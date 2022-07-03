// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "FootStepNotify.generated.h"


USTRUCT(BlueprintType)
struct FFootStep
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		class UParticleSystem* GroundFootParticle;
	UPROPERTY(EditAnywhere)
		class USoundBase* GroundFootSound;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* SnowFootParticle;
	UPROPERTY(EditAnywhere)
		class USoundBase* SnowFootSound;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* WaterFootParticle;
	UPROPERTY(EditAnywhere)
		class USoundBase* WaterFootSound;
};
UCLASS()
class LADYBUG_API UFootStepNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	UFootStepNotify();
protected:
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
protected:
	UPROPERTY(EditAnywhere)
		bool bAttenuation = true;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bAttenuation == true"))
		float falloffDistance = 4000.f;

	UPROPERTY(EditAnywhere)
		FName footSocketName;
	UPROPERTY(EditAnywhere)
		FFootStep footStep;
	UPROPERTY(EditAnywhere)
		float rayLength;
};
