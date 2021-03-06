// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/02_Component/SkillComponent.h"
#include "07_Skill/SKillBase.h"
#include "00_Character/BaseCharacter.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

USkillComponent::~USkillComponent()
{

}


// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

	for(auto skill : BP_SkillList)
	{
		AddSkill(skill.GetDefaultObject());
	}
}

void USkillComponent::BeginDestroy()
{
	Super::BeginDestroy();

}


// Called every frame
void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// 스킬이 사용가능 한지 확인하고 스킬 위젯 업데이트
	if(SkillUsable(0))
	{
		UpdateSkill1Able.Broadcast(true);
	}
	else
	{
		UpdateSkill1Able.Broadcast(false);
	}
	// 스킬이 사용가능 한지 확인하고 스킬 위젯 업데이트
	if (SkillUsable(1))
	{
		UpdateSkill2Able.Broadcast(true);
	}
	else
	{
		UpdateSkill2Able.Broadcast(false);
	}
}

void USkillComponent::AddSkill(USKillBase* skill)
{
	skill->SetSkillOwner(GetOwner<ABaseCharacter>());
	SkillList.Emplace(skill);
}

void USkillComponent::UseSkill(const FGameplayTag skillTag)
{
	// 스킬리스트 중에 해당 스킬태그가 있는 지 확인하고 스킬 사용
	for(auto skill : SkillList)
	{
		if(skill->GetSkillInfo()->skill_Tag == skillTag)
		{
			skill->UseSkill(GetOwner<ABaseCharacter>());
		}
	}
}

void USkillComponent::UseSkill(int32 index)
{
	// 스킬리스트 중에 해당 해당 인덱스 스킬 사용
	SkillList[index]->UseSkill(GetOwner<ABaseCharacter>());
}

bool USkillComponent::IsContainSkill(const FGameplayTag skillTag)
{
	// 스킬리스트 중에 해당 스킬태그인 스킬이 있는 지 확인
	for (auto skill : SkillList)
	{
		if (skill->GetSkillInfo()->skill_Tag == skillTag)
		{
			return true;
		}
	}
	return false;
}

const FSkillInformation* USkillComponent::GetSkillInfo(const FGameplayTag skillTag)
{
	for (auto skill : SkillList)
	{
		if (skill->GetSkillInfo()->skill_Tag == skillTag)
		{
			return skill->GetSkillInfo();
		}
	}
	return nullptr;
}

void USkillComponent::RemoveSkillTimer()
{
	for (auto skill : SkillList)
	{
		skill->RemoveTimer();
	}
}

bool USkillComponent::SkillUsable(int32 index)
{
	// 해당 인덱스의 스킬을 사용가능 한지 확인
	if(SkillList.Num() > index)
	{
		if(SkillList[index]->CommitSkill())
		{
			return true;
		}
	}
	return false;
}
