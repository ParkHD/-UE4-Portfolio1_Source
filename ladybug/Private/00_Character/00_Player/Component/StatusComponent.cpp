// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/Component/StatusComponent.h"

#include "BrainComponent.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/Component/EquipmentComponent.h"
#include "00_Character/01_Monster/MonsterAIController.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if(GetOwner()->IsA<AWorldBaseCharacter>())
		owningCharacter = GetOwner<AWorldBaseCharacter>();
	else if(GetOwner()->IsA<ABaseCharacter>())
		player = GetOwner<ABaseCharacter>();
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ĳ������ Move���¿� ���� ���¹̳� ����
	if(player != nullptr)
	{
		switch (player->GetMoveState())
		{
		case EMoveState::NORMAL:
			// �Ϲ� �����̸� ���¹̳� ȸ��
			AddStamina(5 * DeltaTime);
			break;

		case EMoveState::RUN:
			// �ٰ������� ���¹̳� ����
			if (CheckStamina(10.f))
				AddStamina(-10 * DeltaTime);
			// ����� ���¹̳� ������ �Ϲ� ���·� ���� -> �޸��� ���߱�
			else
				player->SetMoveState(EMoveState::NORMAL);
			break;
			
		case EMoveState::FLY:
			// ���� ������ ���¹̳� ����
			if (CheckStamina(10.f))
				AddStamina(-10 * DeltaTime);
			// ����� ���¹̳� ������ �Ϲ� ���·� ���� -> ���� ���߱�
			else
				player->SetMoveState(EMoveState::NORMAL);
			break;
		}
	}
}


void UStatusComponent::Init()
{
	currentHP = CharacterStat.MaxHP;
	currentMP = 0.f;
	currentSP = CharacterStat.MaxSP;
}

void UStatusComponent::AddStat(FStat stat)
{
	CharacterStat += stat;
}

void UStatusComponent::MinusStat(FStat stat)
{
	CharacterStat -= stat;
}

void UStatusComponent::AddHP(float value)
{
	currentHP = FMath::Clamp(currentHP + value, 0.f, CharacterStat.MaxHP);

	// Player : Status Widget ������Ʈ 
	// Monster : HPBar ������Ʈ
	OnChangeHP.Broadcast(this);	

	// Dead Event
	if (currentHP <= 0)
		Cast<ABaseCharacter>(GetOwner())->OnDead.Broadcast();
}

bool UStatusComponent::CheckHP(float value)
{
	return currentHP >= value;
}

void UStatusComponent::AddStamina(float value)
{
	currentSP = FMath::Clamp(currentSP + value, 0.f, CharacterStat.MaxSP);

	// Player : Status Widget ������Ʈ
	OnChangeSP.Broadcast(this);

	// AI����
	// AI�� Stamina ���� �� ������ ������ ������Ʈ
	if(player->IsA<AMonsterBaseCharacter>())
	{
		auto aiController = player->GetController<AMonsterAIController>();
		if (aiController != nullptr)
		{
			if(aiController->GetBlackboardComponent() != nullptr)
			{
				aiController->GetBlackboardComponent()->SetValueAsFloat("Stamina", currentSP);
			}
		}
	}
}
bool UStatusComponent::CheckStamina(float value)
{
	return currentSP >= value;
}

void UStatusComponent::AddMP(float value)
{
	currentMP = FMath::Clamp(currentMP + value, 0.f, CharacterStat.MaxMP);
	// Player : Status Widget ������Ʈ
	OnChangeMP.Broadcast(this);
}

bool UStatusComponent::CheckMP(float value)
{
	return currentMP >= value;
}

void UStatusComponent::AddDamage(float value)
{
	CharacterStat.Damage += value;
}
void UStatusComponent::SetStatusComponentData(FStatusComponentSave Data)
{
	CharacterStat = Data.CharacterStat;
	GetOwner<AWorldBaseCharacter>()->GetEquipmentComponent()->OnChangeEquipment.Broadcast(this);
}

void UStatusComponent::SetBattleCharacterStat(UStatusComponent* StatComp)
{
	CharacterStat = StatComp->GetStat();

	Init();
}

void UStatusComponent::SetBattleCharacterStat(FStat stat)
{
	CharacterStat = stat;
	Init();
}
