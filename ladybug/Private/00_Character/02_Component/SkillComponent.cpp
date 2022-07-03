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

	// ��ų�� ��밡�� ���� Ȯ���ϰ� ��ų ���� ������Ʈ
	if(SkillUsable(0))
	{
		UpdateSkill1Able.Broadcast(true);
	}
	else
	{
		UpdateSkill1Able.Broadcast(false);
	}
	// ��ų�� ��밡�� ���� Ȯ���ϰ� ��ų ���� ������Ʈ
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
	// ��ų����Ʈ �߿� �ش� ��ų�±װ� �ִ� �� Ȯ���ϰ� ��ų ���
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
	// ��ų����Ʈ �߿� �ش� �ش� �ε��� ��ų ���
	SkillList[index]->UseSkill(GetOwner<ABaseCharacter>());
}

bool USkillComponent::IsContainSkill(const FGameplayTag skillTag)
{
	// ��ų����Ʈ �߿� �ش� ��ų�±��� ��ų�� �ִ� �� Ȯ��
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
	// �ش� �ε����� ��ų�� ��밡�� ���� Ȯ��
	if(SkillList.Num() > index)
	{
		if(SkillList[index]->CommitSkill())
		{
			return true;
		}
	}
	return false;
}
