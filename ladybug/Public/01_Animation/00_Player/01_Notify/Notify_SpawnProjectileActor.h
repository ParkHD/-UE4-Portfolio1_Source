// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GameplayTagContainer.h"

#include "Notify_SpawnProjectileActor.generated.h"

// ProjectileActor Spawn NotifyState
// ������Ÿ�� ���͸� �����ϰ� !���! �߻��Ѵ�.
// ��ų ����
UCLASS()
class LADYBUG_API UNotify_SpawnProjectileActor : public UAnimNotify
{
	GENERATED_BODY()
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

protected:
	UPROPERTY(EditAnywhere)
		FGameplayTag skill_Tag;					// ���� ����ϴ� ��ų�� �±�

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> ActorToSpawn;	// ��ȯ�� ProjectileActor
	UPROPERTY(EditAnywhere)
		FRotator spawnRotation;					// ProjectileActor Rotation
	UPROPERTY(EditAnywhere)
		FName spawnSocketName;					// ��ȯ�� ��ġ : �����̸�
	UPROPERTY(EditAnywhere)
		float projectileSpeed;					// ProjectileActor Speed

public:
	// �߻� �� ���� ���ϴ� �Լ�
	FVector GetShotDir(class ABaseCharacter* owner);
};
