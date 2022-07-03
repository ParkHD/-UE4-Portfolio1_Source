// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"

#include "CollisionRangeNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UCollisionRangeNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
protected:
	UPROPERTY()
		class ABaseCharacter* owner;
	
	FVector startLocation;
	FRotator startRotator;

	UPROPERTY(EditAnywhere)
		FGameplayTag skill_Tag;
	UPROPERTY(EditAnywhere)
		float range;
	UPROPERTY(EditAnywhere)
		float length;
	UPROPERTY(EditAnywhere)
		float collisionRadius;
	UPROPERTY(EditAnywhere)
		float interpSpeed;

	float angle;
};
