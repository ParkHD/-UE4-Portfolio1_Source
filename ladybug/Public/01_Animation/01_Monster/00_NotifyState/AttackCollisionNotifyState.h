// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackCollisionNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UAttackCollisionNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

protected:
	UPROPERTY()
	class ABaseCharacter* owner;
	UPROPERTY()
		TArray<class AActor*> hitActor;
	UPROPERTY(EditAnywhere)
		bool isSkill = false;
	UPROPERTY(EditAnywhere)
		bool isBreakBlock = false;
	UPROPERTY(EditAnywhere)
		bool bMultiAttack = false;
	UPROPERTY(EditAnywhere)
		FName startSocketName;
	UPROPERTY(EditAnywhere)
		FName endSocketName;
	UPROPERTY(EditAnywhere)
		float collisionHeight = 50.f;
	UPROPERTY(EditAnywhere);
		float collisionRadius;
};
