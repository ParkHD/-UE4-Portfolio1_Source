// Fill out your copyright notice in the Description page of Project Settings.


#include "07_Skill/00_RangedSkill/SlashSkill.h"
#include "00_Character/BaseCharacter.h"

void USlashSkill::ActivateSkill()
{
	Super::ActivateSkill();

	// ��ų��� -> �ִϸ��̼� ����
	float skillPlayTime = skillOwner->GetMesh()->GetAnimInstance()->Montage_Play(GetSkillInfo()->skill_Montage, skillFast,EMontagePlayReturnType::Duration);

	// �ִϸ��̼� ���� �� ActionState::NORMAL�� ����
	FTimerHandle skillTimer;
	FTimerDelegate skillDelegate = FTimerDelegate::CreateUObject(skillOwner, &ABaseCharacter::SetActionState, EActionState::NORMAL);
	skillOwner->GetWorld()->GetTimerManager().SetTimer(
		skillTimer,
		skillDelegate,
		skillPlayTime,
		false);
	
}