// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/99_Public/01_NotifyState/NotifyState_SetActionState.h"

void UNotifyState_SetActionState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if (MeshComp != nullptr)
	{
		// ActionState 설정
		owner = MeshComp->GetOwner<ABaseCharacter>();
		if (owner != nullptr)
		{
			owner->SetActionState(actionState);
		}
	}
}

void UNotifyState_SetActionState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UNotifyState_SetActionState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	// ActionState 복구
	if (owner != nullptr)
	{
		owner->SetActionState(EActionState::NORMAL);
	}
}
