// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "97_SaveGame/SaveVariable.h"
#include "02_Item/ItemTypes.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeStat, class UStatusComponent*, statComp);


//UENUM(BlueprintType)
//enum class EHitState : uint8 // Enum이름 앞에 E꼭 붙여야함
//{
//	STUN,
//	FIRE,
//};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LADYBUG_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
		class AWorldBaseCharacter* owningCharacter;
	UPROPERTY()
		class ABaseCharacter* player;
	// 캐릭터의 Stat
	UPROPERTY(EditAnywhere)
		FStat CharacterStat;
	//UPROPERTY(VisibleAnywhere)
	//	TArray<EHitState> CharacterState;

	UPROPERTY(EditAnywhere)
		int32 level = 1;

	UPROPERTY(EditAnywhere)
		float currentHP = CharacterStat.MaxHP;
	UPROPERTY(EditAnywhere)
		float currentMP = 0;
	UPROPERTY(EditAnywhere)
		float currentSP = CharacterStat.MaxSP;
public:
	FStat GetStat() const { return CharacterStat; }
	float const GetCurrentSP() { return currentSP; }
	float GetHPRatio() { return currentHP / CharacterStat.MaxHP; }
	float GetSPRatio() { return currentSP / CharacterStat.MaxSP; }
	float GetMPRatio() { return currentMP / CharacterStat.MaxMP; }

	float GetCurrentMP() const { return currentMP; }
//public:
//	bool IsContainState(EHitState State) { return CharacterState.Contains(State); }
//	void AddCharacterState(EHitState State);
//	void RemoveState(EHitState State) { CharacterState.Remove(State); }
public:
	void Init();

	void AddStat(FStat stat);
	void MinusStat(FStat stat);


	void AddHP(float value);
	bool CheckHP(float value);

	void AddStamina(float value);
	bool CheckStamina(float value);

	void AddMP(float value);
	bool CheckMP(float value);
public:
	FOnChangeStat OnChangeHP;
	FOnChangeStat OnChangeSP;
	FOnChangeStat OnChangeMP;

public:
	void SetStatusComponentData(FStatusComponentSave Data);
	// BattleCharacter 전용
	void SetBattleCharacter(class UStatusComponent* StatComp);
	void SetBattelCharacter(FStat stat);
};
