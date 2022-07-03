// Fill out your copyright notice in the Description page of Project Settings.


#include "07_Skill/SkillEffect.h"
#include "00_Character/BaseCharacter.h"
#include "00_Character/02_Component/SkillComponent.h"
#include "00_Character/00_Player/Component/StatusComponent.h"

USkillEffect::~USkillEffect()
{
	
}

void USkillEffect::BeginDestroy()
{
	UObject::BeginDestroy();

}

void USkillEffect::ApplyDurationEffect(ABaseCharacter* target)
{
	target->GetSkillComponent()->AddSkillEffect(effectTag, effectTime);

	FTimerDelegate endEffectDelegate = FTimerDelegate::CreateUObject(this, &USkillEffect::RemoveEffect, target);
	target->GetWorldTimerManager().SetTimer(
		endEffectTimer,
		endEffectDelegate,
		effectTime,
		false);
}
void USkillEffect::ApplyInstantEffect(class ABaseCharacter* target)
{
	target->GetSkillComponent()->AddSkillEffect(effectTag, 0);

	target->GetStatusComponent()->AddMP(-effectValue);

	RemoveEffect(target);
}
void USkillEffect::RemoveEffect(class ABaseCharacter* target)
{
	if(target != nullptr)
	{
		if(target->GetSkillComponent() != nullptr)
		{
			target->GetSkillComponent()->RemoveSkillEffect(effectTag);
		}
	}
}
void USkillEffect::ApplyEffect(class ABaseCharacter* target)
{
	switch (effectType)
	{
	case EEffectType::INSTANT:
		ApplyInstantEffect(target);
		break;
	case EEffectType::DURATION:
		ApplyDurationEffect(target);
		break;
	}
}
bool USkillEffect::CheckEffectValue(class ABaseCharacter* target)
{
	return target->GetStatusComponent()->CheckMP(effectValue);
	
}

void USkillEffect::RemoveTimer(class ABaseCharacter* target)
{
	if(target->GetWorldTimerManager().TimerExists(endEffectTimer))
	{
		target->GetWorldTimerManager().ClearTimer(endEffectTimer);
	}
}
