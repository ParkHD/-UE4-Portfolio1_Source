// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ProjectileActorSpawnNotify.generated.h"

// 사용보류!!!
// 프로젝타일 액터 소환 및 발사 Notify
UCLASS()
class LADYBUG_API UProjectileActorSpawnNotify : public UAnimNotify
{
	GENERATED_BODY()
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> actorToSpawn;	// 스폰할 Actor
	UPROPERTY(EditAnywhere)	
		FName spawnSocketName;					// 스폰 할 위치
	UPROPERTY(EditAnywhere)
		float projectileSpeed;					// projectileActor 스피드
};
