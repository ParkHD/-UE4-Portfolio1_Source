// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"

#include "Notify_SpawnProjectileActor.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UNotify_SpawnProjectileActor : public UAnimNotify
{
	GENERATED_BODY()
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

protected:
	UPROPERTY(EditAnywhere)
		FGameplayTag skill_Tag;

	UPROPERTY(EditAnywhere)
		FRotator spawnRotation;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> ActorToSpawn;
	UPROPERTY(EditAnywhere)
		FName spawnSocketName;
	UPROPERTY(EditAnywhere)
		float projectileSpeed;

public:
	FVector GetShotDir(class ABaseCharacter* owner);
};
