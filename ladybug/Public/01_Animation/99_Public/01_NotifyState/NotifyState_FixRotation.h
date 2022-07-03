// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_FixRotation.generated.h"

// 애니메이션을 루트모션으로 바꿨을 때 회전값이 이상하게 변동되는 것을 방지
// 회전값 고정
UCLASS()
class LADYBUG_API UNotifyState_FixRotation : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

protected:
	class ABaseCharacter* owner;	// owner

	FRotator ownerRotation;			// owner의 애니메이션 시작 전 회전값
};
