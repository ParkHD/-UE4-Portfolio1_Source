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
	// effect를 적용한다
	target->GetSkillComponent()->AddSkillEffect(effectTag, effectTime);
	switch (effectTarget)
	{
	case EEffectTarget::COOLTIME:
		break;
	case EEffectTarget::DAMAGE:
		target->GetStatusComponent()->AddDamage(effectValue);
		break;
	}
	// 일정시간 후에 effect를 삭제한다.
	FTimerDelegate endEffectDelegate = FTimerDelegate::CreateUObject(this, &USkillEffect::RemoveEffect, target);
	target->GetWorldTimerManager().SetTimer(
		endEffectTimer,
		endEffectDelegate,
		effectTime,
		false);
}
void USkillEffect::ApplyInstantEffect(class ABaseCharacter* target)
{
	// effect를 적용한다
	target->GetSkillComponent()->AddSkillEffect(effectTag, 0);
	// cost를 깍는다
	target->GetStatusComponent()->AddMP(-effectValue);
	// effect를 삭제한다.
	RemoveEffect(target);
}
void USkillEffect::RemoveEffect(class ABaseCharacter* target)
{
	if(target != nullptr)
	{
		// 적용되어 있던 effect를 제거
		switch (effectTarget)
		{
		case EEffectTarget::COOLTIME:
			break;
		case EEffectTarget::DAMAGE:
			target->GetStatusComponent()->AddDamage(-effectValue);
			break;
		}

		// 적용되고 있는 effect 제거
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
	// 충분한 MP가 있는지 확인한다.
	return target->GetStatusComponent()->CheckMP(effectValue);
}

void USkillEffect::RemoveTimer(class ABaseCharacter* target)
{
	if(target->GetWorldTimerManager().TimerExists(endEffectTimer))
	{
		target->GetWorldTimerManager().ClearTimer(endEffectTimer);
	}
}
