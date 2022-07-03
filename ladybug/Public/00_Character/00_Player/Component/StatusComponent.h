// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "97_SaveGame/SaveVariable.h"
#include "02_Item/ItemTypes.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeStat, class UStatusComponent*, statComp);


// ����������Ʈ
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

	// ĳ������ �ɷ�ġ
	UPROPERTY(EditAnywhere)
		FStat CharacterStat;

	UPROPERTY(EditAnywhere)
		int32 level = 1;

	// ���� ĳ���� ����
	UPROPERTY(EditAnywhere)
		float currentHP = CharacterStat.MaxHP;
	UPROPERTY(EditAnywhere)
		float currentMP = 0;
	UPROPERTY(EditAnywhere)
		float currentSP = CharacterStat.MaxSP;
public:
	FStat GetStat() const { return CharacterStat; }
	float GetHPRatio() { return currentHP / CharacterStat.MaxHP; }
	float GetSPRatio() { return currentSP / CharacterStat.MaxSP; }
	float GetMPRatio() { return currentMP / CharacterStat.MaxMP; }

	float const GetCurrentSP() const { return currentSP; }
	float const GetCurrentMP() const { return currentMP; }
public:
	void Init();

	// ���� ����(��� ����)
	void AddStat(FStat stat);
	void MinusStat(FStat stat);

	// ���� HP, Stamina, MP ����
	void AddHP(float value);
	void AddStamina(float value);
	void AddMP(float value);
	// ���� ����
	void AddDamage(float value);
	// ����� HP, Stamina, MP�ִ� �� Ȯ��
	bool CheckHP(float value);
	bool CheckStamina(float value);
	bool CheckMP(float value);
public:
	// StatUI ������Ʈ
	FOnChangeStat OnChangeHP;
	FOnChangeStat OnChangeSP;
	FOnChangeStat OnChangeMP;

public:
	// WorldCharacter ����
	void SetStatusComponentData(FStatusComponentSave Data);
	// BattleCharacter����, BattleCharacter�� ���� SetUp
	void SetBattleCharacterStat(class UStatusComponent* StatComp);
	void SetBattleCharacterStat(FStat stat);
};
