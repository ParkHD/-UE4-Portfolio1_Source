// Fill out your copyright notice in the Description page of Project Settings.


#include "10_WorldCharacter/WorldBaseCharacter.h"

#include "00_Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "00_Character/00_Player/Component/StatusComponent.h"
#include "00_Character/02_Component/ArmyComponent.h"
#include "00_Character/00_Player/Component/EquipmentComponent.h"
#include "08_Monster/Monster.h"
#include "98_GameInstance/myGameInstance.h"

// Sets default values
AWorldBaseCharacter::AWorldBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));
	ArmyManagerComponent = CreateDefaultSubobject<UArmyComponent>(TEXT("ArmyManagerComponent"));
}
AWorldBaseCharacter::~AWorldBaseCharacter()
{
	UE_LOG(LogTemp, Error, TEXT("destroy!!~~ %s"), *GetName());

}
// Called when the game starts or when spawned
void AWorldBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 테스트 용도
	// 에디터에서 부대원 받아서 부대에 추가
	if (Cast<UmyGameInstance>(GetGameInstance())->GetMonsterData().Num() == 0)
	{
		for (TSubclassOf<class UMonster> unit : ArmyListBP)
		{
			auto temp = unit.GetDefaultObject();
			ArmyManagerComponent->AddArmy(temp);
		}
	}
}
void AWorldBaseCharacter::Destroyed()
{
	Super::Destroyed();

	UE_LOG(LogTemp, Error, TEXT("destroy %s"), *GetName());
}
// Called every frame
void AWorldBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWorldBaseCharacter::SetCharacterData(FSaveCharacterData CharacterData)
{
	//StatusComponent = CharacterData.statusComponent;

	ArmyManagerComponent->SetArmyComponentData(CharacterData.ArmyComponentData);
}
