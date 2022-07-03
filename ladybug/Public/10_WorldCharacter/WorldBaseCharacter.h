// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "97_SaveGame/SaveVariable.h"
#include "GenericTeamAgentInterface.h"
#include "WorldBaseCharacter.generated.h"


// WorldCharacter의 Base class
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
		class UStatusComponent* StatusComponent;		// 능력치 컴포넌트
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = InventoryComp)
		class UEquipmentComponent* EquipmentComponent;	// 장비관리 컴포넌트
	UPROPERTY(VisibleAnywhere)
		class UArmyComponent* ArmyManagerComponent;		// 부대관리 컴포넌트
public:
	class UStatusComponent* GetStatusComponent() { return StatusComponent; }
	class UEquipmentComponent* GetEquipmentComponent() { return EquipmentComponent; }
	class UArmyComponent* GetArmyComponent() { return ArmyManagerComponent; }

protected:
	UPROPERTY(EditAnywhere)
		FGenericTeamId myTeam;									// TeamID
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABaseCharacter> battleCharacter;		// BattleCharacter

	// 에디터 테스트용으로 부대에 넣을 부대원List
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class UMonster>> ArmyListBP;			
public:
	TSubclassOf<class ABaseCharacter> GetCharacter() { return battleCharacter; }
public:
	// 데이터 덮어쓰기
	virtual void SetCharacterData(FSaveCharacterData CharacterData);

	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) { myTeam = TeamID; }
	virtual FGenericTeamId GetGenericTeamId() const { return myTeam; }

};
