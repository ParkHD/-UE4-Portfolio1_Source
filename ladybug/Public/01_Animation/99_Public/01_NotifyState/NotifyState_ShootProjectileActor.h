// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"
#include "NotifyState_ShootProjectileActor.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UNotifyState_ShootProjectileActor : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

protected:
	UPROPERTY(EditAnywhere)
		FGameplayTag skill_Tag;

	class ABaseCharacter* owner;

	UPROPERTY(EditAnywhere)
		FRotator spawnRotation;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> ActorToSpawn;
	UPROPERTY(EditAnywhere)
		FName spawnSocketName;
	UPROPERTY(EditAnywhere)
		float projectileSpeed;
	UPROPERTY(VisibleAnywhere)
		class AProjectileActor* projectileActor;
public:
	FVector GetShotDir(class ABaseCharacter* characterOwner);
};
