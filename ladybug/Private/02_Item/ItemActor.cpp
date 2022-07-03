// Fill out your copyright notice in the Description page of Project Settings.


#include "02_Item/ItemActor.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/WidgetComponent.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "03_Widget/Item/ItemPickUpWidget.h"
#include "02_Item/Potion.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CAPSULECOMPONENT"));
	sphereComponent->SetCollisionProfileName("Item");
	RootComponent = sphereComponent;

	particleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("PARTICLESYSTEMCOMPONENT"));
	particleSystemComponent->SetupAttachment(RootComponent);
	particleSystemComponent->SetWorldScale3D(FVector(0.5f, 0.5f, 0.5f));
	particleSystemComponent->SetWorldLocation(FVector(0.f, 0.f, -30.f));

	pickUpWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	pickUpWidgetComponent->SetupAttachment(RootComponent);
	pickUpWidgetComponent->SetVisibility(false);
	pickUpWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	pickUpWidgetComponent->SetDrawSize(FVector2D(25.f, 25.f));
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	pickUpWidgetComponent->InitWidget();

	OnActorBeginOverlap.AddUniqueDynamic(this, &AItemActor::OnActorBeginOverlapEvent);
	OnActorEndOverlap.AddUniqueDynamic(this, &AItemActor::OnActorEndOverlapEvent);

	if (itemTable != nullptr)
	{
		auto itemInfo = itemTable->FindRow<FItemInformation>(itemCode, "");

		if (itemInfo != nullptr)
		{
			Item = NewObject<UItem>(GetWorld(), itemInfo->Item_Class);
			Item->SetUp(itemCode, itemCount, itemTable);

			if (pickUpWidgetComponent != nullptr)
			{
				auto pickupWidget = Cast<UItemPickUpWidget>(pickUpWidgetComponent->GetUserWidgetObject());
				if (pickupWidget != nullptr)
				{
					pickupWidget->SetItemText(FText::FromString(itemInfo->item_Name));
				}
			}
		}
	}
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AItemActor::OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
	if (player != nullptr)
	{
		player->pickUpAbleItems.Add(this);
		pickUpWidgetComponent->SetVisibility(true);
	}
}

void AItemActor::OnActorEndOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);
	if (player != nullptr)
	{
		for (int i = 0; i < player->pickUpAbleItems.Num(); i++)
		{
			if (player->pickUpAbleItems[i] == this)
			{
				player->pickUpAbleItems.RemoveAt(i);
				break;
			}
		}
		pickUpWidgetComponent->SetVisibility(false);
	}
}