// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/StartJumpAnimNotify.h"
#include "00_Character/00_Player/PlayerCharacter.h"

void UStartJumpAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APlayerCharacter* player = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (player != nullptr)
	{
		player->SetMoveState(EMoveState::JUMP);
	}
}