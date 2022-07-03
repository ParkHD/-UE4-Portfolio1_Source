// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "97_SaveGame/SaveVariable.h"
#include "GenericTeamAgentInterface.h"
#include "WorldBaseCharacter.generated.h"


UCLASS()
class LADYBUG_API AWorldBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWorldBaseCharacter();
	~AWorldBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
		class UStatusComponent* StatusComponent;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = InventoryComp)
		class UEquipmentComponent* EquipmentComponent;
	UPROPERTY(VisibleAnywhere)
		class UArmyComponent* ArmyManagerComponent;
public:
	class UStatusComponent* GetStatusComponent() { return StatusComponent; }
	class UEquipmentComponent* GetEquipmentComponent() { return EquipmentComponent; }
	class UArmyComponent* GetArmyComponent() { return ArmyManagerComponent; }

protected:
	UPROPERTY(EditAnywhere)
		FGenericTeamId myTeam;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABaseCharacter> battleCharacter;
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class UMonster>> ArmyListBP;
public:
	TSubclassOf<class ABaseCharacter> GetCharacter() { return battleCharacter; }
public:
	virtual void SetCharacterData(FSaveCharacterData CharacterData);

	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) { myTeam = TeamID; }
	virtual FGenericTeamId GetGenericTeamId() const { return myTeam; }

};
