// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/99_Public/01_NotifyState/NotifyState_FixRotation.h"

#include "00_Character/BaseCharacter.h"

void UNotifyState_FixRotation::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                           float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if(MeshComp != nullptr)
	{
		owner = MeshComp->GetOwner<ABaseCharacter>();
		if (owner != nullptr)
		{
			ownerRotation = owner->GetActorRotation();
		}
	}
}

void UNotifyState_FixRotation::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	if (MeshComp != nullptr)
	{
		if (owner != nullptr)
		{
			owner->SetActorRotation(FRotator(0.f, ownerRotation.Yaw, 0.f));
		}
	}


}

void UNotifyState_FixRotation::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp != nullptr)
	{
		if (owner != nullptr)
		{
			owner->SetActorRotation(FRotator(0.f, ownerRotation.Yaw, 0.f));
		}
	}
	
}
