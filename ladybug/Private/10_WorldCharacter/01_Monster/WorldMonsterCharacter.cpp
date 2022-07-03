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

		// 몬스터 스폰되면 DataTable의 정보를 이용해서 부대원들을 넣어준다.
		auto info = GetWorldMonsterInfo();
		if (info != nullptr)
		{
			for (auto monsterKind : info->monster_Army)
			{
				// 부대원의 개수를 랜덤으로 정하여 생성하고, 개수가 0이상이라면 부대에 추가한다.
				auto monster = monsterKind.monster.GetDefaultObject();
				float monsterCount = FMath::RandRange(monsterKind.MinCount, monsterKind.MaxCount);
				if (monsterCount > 0)
				{
					monster->SetCount(monsterCount);
					ArmyManagerComponent->AddArmy(monster);
				}
			}
		}
		// 몬스터의 이름 위젯을 SetUp해준다.
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

