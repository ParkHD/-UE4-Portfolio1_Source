// Fill out your copyright notice in the Description page of Project Settings.


#include "10_WorldCharacter/02_StaticActor/00_Village/VillageWorldActor.h"

#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "03_Widget/07_Village/VillageNameWidget.h"

// Sets default values
AVillageWorldActor::AVillageWorldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	RootComponent = sphereComponent;

	staticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	staticMeshComponent->SetupAttachment(sphereComponent);

	villageNameWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("NameWidegetComponent"));
	villageNameWidgetComponent->SetupAttachment(sphereComponent);
}

// Called when the game starts or when spawned
void AVillageWorldActor::BeginPlay()
{
	Super::BeginPlay();

	// 마을 이름 위젯 SetUp
	auto widget = Cast<UVillageNameWidget>(villageNameWidgetComponent->GetUserWidgetObject());
	if(widget != nullptr)
	{
		widget->SetUp(Village_Name);
	}

}

void AVillageWorldActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

// Called every frame
void AVillageWorldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


