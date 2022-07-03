// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_SpawnActor.generated.h"


// Actor�� Spawn�ϴ� NotifyState : ���� ��ȯ ��ų�� ��� -> ��ƼŬ ȿ���� �����ϰ� ȿ���� ������ ���� ��ȯ
UCLASS()
class LADYBUG_API UNotifyState_SpawnActor : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
protected:
	UPROPERTY(EditAnywhere)
		class ABaseCharacter* owner;			// owner

	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor> SpawnActorBP;	// ������ Actor
	UPROPERTY(EditAnywhere)
		float SpawnInterval = 200.f;			// ���� ����
	UPROPERTY(EditAnywhere)
		int32 SpawnCount;						// ���� ����
	UPROPERTY(EditAnywhere)
		UParticleSystem* spawnParticle;			// ���� �� �� ȿ�� ��ƼŬ
	UPROPERTY(EditAnywhere)
		float tempLocationZ;					// ��ƼŬ ��ġ ����

	TArray<FVector> SpawnLocationsArray;		// ���� �� ��ġ Array
};
