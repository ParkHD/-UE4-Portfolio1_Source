// Fill out your copyright notice in the Description page of Project Settings.


#include "10_WorldCharacter/01_Monster/WorldMonAIController.h"
#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"
#include "10_WorldCharacter/01_Monster/WorldMonsterCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

AWorldMonAIController::AWorldMonAIController()
{
	// 컨트롤러랑 소유한 Pawn이랑 연결
	bAttachToPawn = true;

	// 기본제공 AIPerceptionComponent
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	// 시야로 적 탐지
	UAISenseConfig_Sight* sightConfig;
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));
	sightConfig->SightRadius = 1200.f;
	sightConfig->LoseSightRadius = 1500.f;
	sightConfig->PeripheralVisionAngleDegrees = 45.f;
	sightConfig->DetectionByAffiliation.bDetectEnemies = true;
	sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	sightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	sightConfig->SetMaxAge(5.f);

	PerceptionComponent->ConfigureSense(*sightConfig);
}

void AWorldMonAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AWorldMonAIController::OnActorPerceptionUpdatedEvent);
}

void AWorldMonAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	auto ownerMonster = Cast<AWorldMonsterCharacter>(InPawn);
	if(ownerMonster != nullptr)
	{
		if (ownerMonster->GetAIBehaviorTree() != nullptr)
		{
			RunBehaviorTree(ownerMonster->GetAIBehaviorTree());
		}
	}
}

void AWorldMonAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AWorldMonAIController::OnActorPerceptionUpdatedEvent(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		// 탐지된 타겟이 Player인지 확인
		AWorldPlayerCharacter* target = Cast<AWorldPlayerCharacter>(Actor);
		if (target != nullptr)
		{
			GetBlackboardComponent()->SetValueAsObject("Target", Actor);
		}
	}
	else
	{

	}
}
