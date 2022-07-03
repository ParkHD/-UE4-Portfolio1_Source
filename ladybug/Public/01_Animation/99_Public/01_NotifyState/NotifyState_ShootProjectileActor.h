// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GameplayTagContainer.h"
#include "NotifyState_ShootProjectileActor.generated.h"

// ProjectileActor Spawn NotifyState
// ������Ÿ�� ���͸� �����ϰ� ���� �ð� �Ŀ� �߻��Ѵ�.
// ��ų ����
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
		FGameplayTag skill_Tag;			// � ��ų���� ��ų�±�

	class ABaseCharacter* owner;		// owner

	// ������ Actor ����
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> ActorToSpawn;	// ������ ActorBP
	UPROPERTY(EditAnywhere)
		FRotator spawnRotation;					// ������ ȸ����
	UPROPERTY(EditAnywhere)
		FName spawnSocketName;					// ������ ��ġ : ����
	UPROPERTY(EditAnywhere)
		float projectileSpeed;					// projectileActor �ӵ�

	UPROPERTY(VisibleAnywhere)
		class AProjectileActor* projectileActor;	// ��ȯ�� projectileActor
public:
	// �߻��� ���� ���ϴ� �Լ�
	FVector GetShotDir(class ABaseCharacter* characterOwner);
};
