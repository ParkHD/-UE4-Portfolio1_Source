// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_SpawnActor.generated.h"


// Actor를 Spawn하는 NotifyState : 몬스터 소환 스킬에 사용 -> 파티클 효과를 실행하고 효과가 끝날때 몬스터 소환
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
		TSubclassOf<class AActor> SpawnActorBP;	// 스폰할 Actor
	UPROPERTY(EditAnywhere)
		float SpawnInterval = 200.f;			// 스폰 간격
	UPROPERTY(EditAnywhere)
		int32 SpawnCount;						// 스폰 개수
	UPROPERTY(EditAnywhere)
		UParticleSystem* spawnParticle;			// 스폰 할 시 효과 파티클
	UPROPERTY(EditAnywhere)
		float tempLocationZ;					// 파티클 위치 조정

	TArray<FVector> SpawnLocationsArray;		// 스폰 할 위치 Array
};
