// Fill out your copyright notice in the Description page of Project Settings.


#include "07_Skill/SKillBase.h"
#include "07_Skill/SkillEffect.h"
#include "00_Character/02_Component/SkillComponent.h"
#include "00_Character/BaseCharacter.h"
#include "00_Character/00_Player/Component/StatusComponent.h"

bool USKillBase::CommitSkill()
{
	if (skillOwner != nullptr)
	{
		// 스킬이 cooltime이 아닌지 확인
		auto cooleffect = coolTimeEffect.GetDefaultObject();
		if (cooleffect != nullptr)
		{
			if (skillOwner->GetSkillComponent()->IsContainEffect(cooleffect->GetEffectTag()))
			{
				return false;
			}
		}
		
		// 충분한 Cost가 있는지 확인
		auto costeffect = costEffect.GetDefaultObject();
		if (costeffect != nullptr)
		{
			if (!costeffect->CheckEffectValue(skillOwner))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

void USKillBase::ActivateSkill()
{
	if (skillOwner != nullptr)
	{
		skillOwner->SetActionState(EActionState::SKILL);
	}
}

const FSkillInformation* USKillBase::GetSkillInfo()
{
	if (skillDataTable != nullptr)
	{
		return skillDataTable->FindRow<FSkillInformation>(skillTag.GetTagName(), "");
	}
	return nullptr;
}
void USKillBase::EndSkill()
{
}
void USKillBase::UseSkill(class ABaseCharacter* caller)
{
	skillOwner = caller;

	// 스킬을 사용할 수 있는 상태인지 확인
	if (CommitSkill())
	{
		// 스킬 쿨타임 및 cost 적용
		if (skillOwner != nullptr && coolTimeEffect != nullptr)
		{
			const auto coolEffect = coolTimeEffect.GetDefaultObject();
			coolEffect->ApplyEffect(skillOwner);
		}
		if (skillOwner != nullptr && costEffect != nullptr)
		{
			const auto costeffect = costEffect.GetDefaultObject();
			costeffect->ApplyEffect(skillOwner);
		}
		if (skillOwner != nullptr && buffEffect != nullptr)
		{
			const auto buff = buffEffect.GetDefaultObject();
			buff->ApplyEffect(skillOwner);
		}
		// 스킬 실행
		ActivateSkill();
	}
	// 스킬 종료
	EndSkill();
}

FGameplayTag USKillBase::GetCoolTimeTag()
{
	if (coolTimeEffect != nullptr)
	{
		return coolTimeEffect.GetDefaultObject()->GetEffectTag();
	}
	return FGameplayTag::EmptyTag;
}

void USKillBase::RemoveTimer()
{
	if(coolTimeEffect != nullptr && skillOwner != nullptr)
	{
		// 쿨타입 타이머 제거
		coolTimeEffect.GetDefaultObject()->RemoveTimer(skillOwner);
	}
}
