// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/Notify_EndAttack.h"

#include "00_Character/BaseCharacter.h"

void UNotify_EndAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	auto owner = MeshComp->GetOwner<ABaseCharacter>();
	if(owner != nullptr)
	{
		owner->SetActionState(EActionState::NORMAL);
	}
}
