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

	// ...
	player = GetOwner<ABaseCharacter>();
	if(GetOwner()->IsA<AWorldBaseCharacter>())
	{
		owningCharacter = GetOwner<AWorldBaseCharacter>();
	}
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
 
	if(player != nullptr)
	{
		switch (player->GetMoveState())
		{
		case EMoveState::NORMAL:
			AddStamina(5 * DeltaTime);
			break;
		case EMoveState::RUN:
			if (CheckStamina(10.f))
			{
				AddStamina(-10 * DeltaTime);
			}
			else
			{
				player->SetMoveState(EMoveState::NORMAL);
			}
			break;
		case EMoveState::FLY:
			if (CheckStamina(10.f))
			{
				AddStamina(-10 * DeltaTime);
			}
			else
			{
				player->SetMoveState(EMoveState::NORMAL);
			}
			break;
		}

		/*if(IsContainState(EHitState::STUN))
		{
			
		}*/
	}
	
}

//void UStatusComponent::AddCharacterState(EHitState State)
//{
//	CharacterState.AddUnique(State);
//}

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
	OnChangeHP.Broadcast(this);
	if (currentHP <= 0)
	{
		Cast<ABaseCharacter>(GetOwner())->OnDead.Broadcast();
	}
}

bool UStatusComponent::CheckHP(float value)
{
	return currentHP >= value;
}

void UStatusComponent::AddStamina(float value)
{
	currentSP = FMath::Clamp(currentSP + value, 0.f, CharacterStat.MaxSP);
	OnChangeSP.Broadcast(this);
	if(player->IsA<AMonsterBaseCharacter>())
	{
		auto aiController = player->GetController<AMonsterAIController>();
		if (aiController != nullptr)
		{
			if(aiController->GetBlackboardComponent() != nullptr)
			{
				aiController->GetBlackboardComponent()->SetValueAsFloat("Stamina", currentSP);
			}
			//auto stamina = aiController->GetBlackboardComponent()->GetValueAsFloat("Stamina");
			//UE_LOG(LogTemp, Log, TEXT("stamina : %f"), stamina);

			//aiController->GetBlackboardComponent()->SetValueAsFloat("Stamina", currentSP);
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
	OnChangeMP.Broadcast(this);
}

bool UStatusComponent::CheckMP(float value)
{
	return currentMP >= value;
}


void UStatusComponent::SetStatusComponentData(FStatusComponentSave Data)
{
	CharacterStat = Data.CharacterStat;
	GetOwner<AWorldBaseCharacter>()->GetEquipmentComponent()->OnChangeEquipment.Broadcast(this);
}

void UStatusComponent::SetBattleCharacter(UStatusComponent* StatComp)
{
	CharacterStat = StatComp->GetStat();

	Init();
}

void UStatusComponent::SetBattelCharacter(FStat stat)
{
	CharacterStat = stat;
	Init();
}
