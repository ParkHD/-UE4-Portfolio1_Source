// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/02_Component/ArmyComponent.h"

// Sets default values for this component's properties
UArmyComponent::UArmyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UArmyComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UArmyComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UArmyComponent::AddArmy(class UMonster* army)
{
	ArmyList.Emplace(army);
}

void UArmyComponent::SetArmyComponentData(FArmyComponentSave Data)
{
	ArmyList = Data.ArmyList;
}
