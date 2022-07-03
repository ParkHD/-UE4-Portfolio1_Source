// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/EndJumpAnimNotify.h"
#include "00_Character/00_Player/PlayerCharacter.h"

void UEndJumpAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	APlayerCharacter* player = Cast<APlayerCharacter>(MeshComp->GetOwner());
	if (player != nullptr)
	{
		FTimerDelegate EndJumpDelegate = FTimerDelegate::CreateUObject(player, &APlayerCharacter::SetMoveState, EMoveState::NORMAL);
		player->GetWorldTimerManager().SetTimer(EndJumpTimerHandle, EndJumpDelegate, 0.5f, false);
	}
}