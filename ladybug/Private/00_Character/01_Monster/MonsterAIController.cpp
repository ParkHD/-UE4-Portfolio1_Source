// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/01_Monster/MonsterAIController.h"
#include "00_Character/01_Monster/MonsterBaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Damage.h"

#include "00_Character/00_Player/Component/StatusComponent.h"
#include "Components/WidgetComponent.h"
#include "03_Widget/03_Character/HPBarWidget.h"

AMonsterAIController::AMonsterAIController()
{
	// 컨트롤러랑 소유한 Pawn이랑 연결
	bAttachToPawn = true;

	// 기본제공 AIPerceptionComponent
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	// 시야로 AI가 적을 인지하도록 설정
	UAISenseConfig_Sight* sightConfig;
	sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AISenseConfig_Sight"));
	sightConfig->SightRadius = 3500.f;
	sightConfig->LoseSightRadius = 4000.f;
	sightConfig->PeripheralVisionAngleDegrees = 90.f;
	FAISenseAffiliationFilter filter;
	filter.bDetectEnemies = true;
	sightConfig->DetectionByAffiliation = filter;
	sightConfig->SetMaxAge(5.f);
	PerceptionComponent->ConfigureSense(*sightConfig);
}
void AMonsterAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	PerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AMonsterAIController::OnActorPerceptionUpdatedEvent);
}
void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	ownerMonster = Cast<AMonsterBaseCharacter>(InPawn);
	if (ownerMonster != nullptr)
	{
		// 안 해주면 hpBarWidget이 nullptr뜸
		ownerMonster->GetHPBarWidgetComponent()->InitWidget();
		UHPBarWidget* hpBarWidget = Cast<UHPBarWidget>(ownerMonster->GetHPBarWidgetComponent()->GetUserWidgetObject());
		if (hpBarWidget != nullptr)
		{
			hpBarWidget->Init();
			// 몬스터 HPBar 위젯 업데이트
			ownerMonster->GetStatusComponent()->OnChangeHP.AddUniqueDynamic(hpBarWidget,
				&UHPBarWidget::UpdateHPBar);

			// 몬스터 블랙보드 MP Value 업데이트
			ownerMonster->GetStatusComponent()->OnChangeMP.AddUniqueDynamic(this, &AMonsterAIController::SetStatusOnBlackBoard);
		}
	}
}

void AMonsterAIController::OnActorPerceptionUpdatedEvent(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		ABaseCharacter* target = Cast<ABaseCharacter>(Actor);
		
		if (target != nullptr)
		{
			if (target->GetGenericTeamId() != ownerMonster->GetGenericTeamId())
			{
				// 현재 Target과 지금 인지된 Target의 거리를 비교하여 가까운 것을 Target으로 삼는다.
				auto curTarget = Cast<ABaseCharacter>(GetBlackboardComponent()->GetValueAsObject("Target"));
				if(curTarget != nullptr)
				{
					if(ownerMonster->GetDistanceTo(target) < ownerMonster->GetDistanceTo(curTarget))
					{
						GetBlackboardComponent()->SetValueAsObject("Target", Actor);
					}
				}
			}
		}
	}
	else
	{

	}
}
void AMonsterAIController::SetStatusOnBlackBoard(class UStatusComponent* statusComponent)
{
	GetBlackboardComponent()->SetValueAsFloat("MP", statusComponent->GetCurrentMP());
}