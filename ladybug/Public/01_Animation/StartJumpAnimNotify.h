// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "StartJumpAnimNotify.generated.h"

// 사용안함 -> NotifyState_SetActionState로 통합
// 점프 시 MoveState 설정
UCLASS()
class LADYBUG_API UStartJumpAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
};
