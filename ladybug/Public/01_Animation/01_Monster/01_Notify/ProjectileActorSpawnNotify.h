// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ProjectileActorSpawnNotify.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UProjectileActorSpawnNotify : public UAnimNotify
{
	GENERATED_BODY()
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> actorToSpawn;
	UPROPERTY(EditAnywhere)
		FName spawnSocketName;
	UPROPERTY(EditAnywhere)
		float projectileSpeed;
};
