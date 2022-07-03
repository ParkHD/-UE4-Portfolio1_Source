// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/BaseCharacter.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NotifyState_SetActionState.generated.h"

// ActionState ���� �� ���� �ð� �Ŀ� ActionState::NORMAL�� ����
UCLASS()
class LADYBUG_API UNotifyState_SetActionState : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;
public:
	UPROPERTY(EditAnywhere)
		EActionState actionState;		// � ActionState�� ���� ����

protected:
	UPROPERTY()
		class ABaseCharacter* owner;	// owner
};
