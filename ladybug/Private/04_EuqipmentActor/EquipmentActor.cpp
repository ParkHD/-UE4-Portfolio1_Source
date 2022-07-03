// Fill out your copyright notice in the Description page of Project Settings.


#include "04_EuqipmentActor/EquipmentActor.h"

// Sets default values
AEquipmentActor::AEquipmentActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));

	RootComponent = SkeletalMesh;
}

// Called when the game starts or when spawned
void AEquipmentActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEquipmentActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

