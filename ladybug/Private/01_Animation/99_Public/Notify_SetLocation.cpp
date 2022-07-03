// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/99_Public/Notify_SetLocation.h"

void UNotify_SetLocation::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if(MeshComp != nullptr)
	{
		auto owner = MeshComp->GetOwner();
		if(owner != nullptr)
		{
			auto newLocation = owner->GetActorLocation();
			newLocation.X = owner->GetActorForwardVector().X * value;
			owner->SetActorLocation(newLocation);
		}
	}
}
