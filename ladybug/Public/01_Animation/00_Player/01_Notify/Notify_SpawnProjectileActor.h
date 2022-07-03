// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"

#include "Notify_SpawnProjectileActor.generated.h"

// ProjectileActor Spawn NotifyState
// 프로젝타일 액터를 스폰하고 !즉시! 발사한다.
// 스킬 전용
UCLASS()
class LADYBUG_API UNotify_SpawnProjectileActor : public UAnimNotify
{
	GENERATED_BODY()
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

protected:
	UPROPERTY(EditAnywhere)
		FGameplayTag skill_Tag;					// 현재 사용하는 스킬의 태그

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> ActorToSpawn;	// 소환할 ProjectileActor
	UPROPERTY(EditAnywhere)
		FRotator spawnRotation;					// ProjectileActor Rotation
	UPROPERTY(EditAnywhere)
		FName spawnSocketName;					// 소환할 위치 : 소켓이름
	UPROPERTY(EditAnywhere)
		float projectileSpeed;					// ProjectileActor Speed

public:
	// 발사 할 방향 구하는 함수
	FVector GetShotDir(class ABaseCharacter* owner);
};
