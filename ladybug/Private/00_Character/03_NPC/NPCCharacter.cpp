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

	if(isInteract)
	{
		if(npcCaller)
		{
			FVector dir = npcCaller->GetActorLocation() - GetActorLocation();
			FRotator dirRotation = GetActorRotation();
			dirRotation.Yaw = dir.Rotation().Yaw;
			if(FMath::Abs(dirRotation.Yaw - GetActorRotation().Yaw) <= 5.f)
			{
				isInteract = false;
			}
			else
			{
				SetActorRotation(FMath::RInterpTo(GetActorRotation(), dirRotation, DeltaTime, interpSpeed));
			}
		}
	}
}


void ANPCCharacter::SetUp(FNPCInfo NPCInfo)
{
	npcTag = NPCInfo.npc_Tag;
	npcName = NPCInfo.npc_Name;
	UMG_DialogueWidget = NPCInfo.npc_UMG_DialogueWidget;
	for(auto unitClass : NPCInfo.npc_shopList)
	{
		if(unitClass.GetDefaultObject()->IsA<UMonster>())
		{
			auto shopUnit = NewObject<UMonster>(GetGameInstance(), NAME_None, RF_NoFlags, unitClass.GetDefaultObject(), true);
			shopUnit->SetCount(2);
			shopList.Emplace(shopUnit);
		}
		else if (unitClass.GetDefaultObject()->IsA<UItem>())
		{
			auto shopltem = NewObject<UItem>();
			if(unitClass.GetDefaultObject()->IsA<UWeapon>())
			{
				shopltem = NewObject<UWeapon>(GetGameInstance(), NAME_None, RF_NoFlags, unitClass.GetDefaultObject(), true);
				shopltem->ItemStatSetUp();
			}
			else if (unitClass.GetDefaultObject()->IsA<UArmor>())
			{
				shopltem = NewObject<UArmor>(GetGameInstance(), NAME_None, RF_NoFlags, unitClass.GetDefaultObject(), true);
				shopltem->ItemStatSetUp();
			}
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
		isInteract = true;

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
		else
		{
			dialogueWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
	if(dialogueWidget != nullptr)
	{
		dialogueWidget->SetVisibility(ESlateVisibility::Visible);
	}
}