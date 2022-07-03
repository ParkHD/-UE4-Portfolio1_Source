// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_ShootArrow.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UNotifyState_ShootArrow : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
protected:
	UPROPERTY(EditAnywhere)
		class ABaseCharacter* owner;
	UPROPERTY(VisibleAnywhere)
		FVector shootDir;
	
	UPROPERTY(EditAnywhere)
		FName SpawnSocketName;
	UPROPERTY(EditAnywhere)
		float ProjectileSpeed;

	UPROPERTY(EditAnywhere)
		float Accuracy;
};