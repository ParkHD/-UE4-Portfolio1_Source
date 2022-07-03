// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/03_NPC/NPCCharacter.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/CustomController.h"
#include "02_Item/Item.h"
#include "02_Item/00_Equipment/Weapon.h"
#include "02_Item/00_Equipment/00_Armor/Armor.h"
#include "Blueprint/UserWidget.h"
#include "03_Widget/05_NPC/NPCDialogueWidget.h"
#include "08_Monster/Monster.h"
#include "Components/WidgetComponent.h"
// Sets default values
ANPCCharacter::ANPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	clothMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("clothMeshComponent"));
	clothMeshComponent->SetupAttachment(GetMesh());

	pantMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("pantMeshComponent"));
	pantMeshComponent->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 원래 캐릭터 회전 값 저장
	originRotator = GetActorRotation();
}
void ANPCCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
// Called every frame
void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 상호작용을 시작하면 Target 방향으로 회전
	if(isInteract)
	{
		if(npcCaller)
		{
			// Target 방향벡터 구하기
			FVector dir = npcCaller->GetActorLocation() - GetActorLocation();
			FRotator dirRotation = GetActorRotation();
			dirRotation.Yaw = dir.Rotation().Yaw;
			
			// 회전하다가 타겟과의 각도가 오차범위 이내면 회전 정지
			if(FMath::Abs(dirRotation.Yaw - GetActorRotation().Yaw) <= 5.f)
			{
				isInteract = false;
			}
			// 타겟방향으로 보간 회전
			else
			{
				SetActorRotation(FMath::RInterpTo(GetActorRotation(), dirRotation, DeltaTime, interpSpeed));
			}
		}
	}
}


void ANPCCharacter::SetUp(FNPCInfo NPCInfo)
{
	// NPC 별로 데이터 설정
	npcTag = NPCInfo.npc_Tag;
	npcName = NPCInfo.npc_Name;
	UMG_DialogueWidget = NPCInfo.npc_UMG_DialogueWidget;
	for(auto unitClass : NPCInfo.npc_shopList)
	{
		// 파는 물품의 class에 따라 물품 생성 및 판매물품 List 설정 
		if(unitClass.GetDefaultObject()->IsA<UMonster>())
		{
			// 판매 유닛 생성
			auto shopUnit = NewObject<UMonster>(GetGameInstance(), NAME_None, RF_NoFlags, unitClass.GetDefaultObject(), true);
			shopUnit->SetCount(2);
			// 생성한 유닛 판매List에 추가
			shopList.Emplace(shopUnit);
		}
		else if (unitClass.GetDefaultObject()->IsA<UItem>())
		{
			// 판매 아이템 종류를 구분하여 생성
			auto shopltem = NewObject<UItem>();
			if(unitClass.GetDefaultObject()->IsA<UWeapon>())		// 무기 아이템
			{
				shopltem = NewObject<UWeapon>(GetGameInstance(), NAME_None, RF_NoFlags, unitClass.GetDefaultObject(), true);
				shopltem->ItemStatSetUp();
			}
			else if (unitClass.GetDefaultObject()->IsA<UArmor>())	// 방어구 아이템
			{
				shopltem = NewObject<UArmor>(GetGameInstance(), NAME_None, RF_NoFlags, unitClass.GetDefaultObject(), true);
				shopltem->ItemStatSetUp();
			}
			// 생성한 아이템 판매List에 추가
			shopList.Emplace(shopltem);
		}
	}
}

const FText ANPCCharacter::GetName()
{
	return FText::FromString(npcName);
}
void ANPCCharacter::InterAction(class APlayerCharacter* caller)
{
	auto controller = caller->GetController<ACustomController>();

	if (controller != nullptr)
	{
		npcCaller = caller;
		isInteract = true;		// 타겟방향으로 몸을 회전시작

		// 대화창이 없으면 생성
		if (dialogueWidget == nullptr)
		{
			auto dialogue = UMG_DialogueWidget;
			if (dialogue != nullptr)
			{
				dialogueWidget = CreateWidget<UNPCDialogueWidget>(controller, dialogue);
				dialogueWidget->SetOwnerNPC(this);
				dialogueWidget->AddToViewport();
			}
		}
		// 대화창 띄우기
		dialogueWidget->SetVisibility(ESlateVisibility::Visible);
	}
}