// Fill out your copyright notice in the Description page of Project Settings.


#include "10_WorldCharacter/01_Monster/WorldMonsterCharacter.h"

#include "00_Character/02_Component/ArmyComponent.h"
#include "03_Widget/07_Village/VillageNameWidget.h"
#include "08_Monster/Monster.h"
#include "98_GameInstance/myGameInstance.h"
#include "99_GameMode/BattleGameMode.h"
#include "99_GameMode/WorldGameMode.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"
#include "Kismet/GameplayStatics.h"

AWorldMonsterCharacter::AWorldMonsterCharacter()
{
	AIPerceptionStimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("AIPerceptionStimuliSourceComponent"));
	AIPerceptionStimuliSourceComponent->bAutoRegister = true;
	AIPerceptionStimuliSourceComponent->RegisterForSense(UAISense_Sight::StaticClass());

	monsterNameWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("NameWidegetComponent"));
	monsterNameWidgetComponent->SetupAttachment(RootComponent);

	SetGenericTeamId(FGenericTeamId(10));

	// 움직일 때 가속 되는 방향으로 Turn되게 설정
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	SetGenericTeamId(20);
}
void AWorldMonsterCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AWorldMonsterCharacter::BeginPlay()
{
	Super::BeginPlay();


	if(UGameplayStatics::GetGameMode(GetWorld())->IsA<AWorldGameMode>())
	{
		SpawnLocation = GetActorLocation();
		auto info = GetWorldMonsterInfo();
		if (info != nullptr)
		{
			for (auto monsterKind : info->monster_Army)
			{
				//auto monster = NewObject<UMonster>(GetGameInstance(), NAME_None, RF_NoFlags, monsterKind.monster->GetDefaultObject(), true);
				auto monster = monsterKind.monster.GetDefaultObject();
				float monsterCount = FMath::RandRange(monsterKind.MinCount, monsterKind.MaxCount);
				if (monsterCount > 0)
				{
					monster->SetCount(3);
					ArmyManagerComponent->AddArmy(monster);
				}
			}
		}
		auto widget = Cast<UVillageNameWidget>(monsterNameWidgetComponent->GetUserWidgetObject());
		if (widget != nullptr)
		{
			widget->SetUp(GetWorldMonsterInfo()->monster_Name);
		}
	}
	
}

FWorldMonsterInfo* const AWorldMonsterCharacter::GetWorldMonsterInfo()
{
	if (worldMonsterDataTable != nullptr)
	{
		return worldMonsterDataTable->FindRow<FWorldMonsterInfo>(monsterTag.GetTagName(), "");
	}
	return nullptr;
}

void AWorldMonsterCharacter::SetCharacterData(FSaveCharacterData CharacterData)
{
	Super::SetCharacterData(CharacterData);

	SpawnLocationIndex = CharacterData.LocationIndex;
}

