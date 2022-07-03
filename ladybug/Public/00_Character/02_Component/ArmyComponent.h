// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "97_SaveGame/SaveVariable.h"
#include "ArmyComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LADYBUG_API UArmyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UArmyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
protected:
	UPROPERTY(VisibleAnywhere)
		TArray<class UMonster*> ArmyList;
public:
	const TArray<class UMonster*>& GetArmyList() { return ArmyList; }
	bool IsHaveArmy() { return ArmyList.Num() > 0; }

	void AddArmy(class UMonster* army);

	void SetArmyComponentData(FArmyComponentSave Data);
};
