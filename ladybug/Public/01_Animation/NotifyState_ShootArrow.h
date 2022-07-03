// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_ShootArrow.generated.h"

// 화살 발사하는 NotifyState
UCLASS()
class LADYBUG_API UNotifyState_ShootArrow : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
protected:
	UPROPERTY(EditAnywhere)
		class ABaseCharacter* owner;	// owner

	UPROPERTY(VisibleAnywhere)
		FVector shootDir;			// 화살 날아갈 방향
	UPROPERTY(EditAnywhere)
		FName SpawnSocketName;		// 화살 생성 위치
	UPROPERTY(EditAnywhere)
		float ProjectileSpeed;		// 화살 속도

	UPROPERTY(EditAnywhere)
		float Accuracy;				// 정확도
};
