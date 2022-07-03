// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/00_Player/00_NotifyState/ComboAttackNotifyState.h"
#include "00_Character/00_Player/PlayerCharacter.h"


UComboAttackNotifyState::UComboAttackNotifyState()
{
	bIsNativeBranchingPoint = true;
}

void UComboAttackNotifyState::BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload) 
{
	owner = BranchingPointPayload.SkelMeshComponent->GetOwner<APlayerCharacter>();

	if (owner != nullptr)
	{
		owner->bInputComboAttack = false;
	}
}

void UComboAttackNotifyState::BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime) 
{
	
}

void UComboAttackNotifyState::BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload) 
{
	if (owner != nullptr)
	{
		if (owner->bInputComboAttack)
		{
			owner->GetMesh()->GetAnimInstance()->Montage_JumpToSection(sectionName);
		}
		else
		{
			owner->SetActionState(EActionState::NORMAL);
			owner->GetMesh()->GetAnimInstance()->Montage_Stop(0.1f);
		}
	}

}
