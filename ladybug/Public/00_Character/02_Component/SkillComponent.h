// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "07_Skill/SKillBase.h"

#include "SkillComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeCoolTime, bool, skillAble);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LADYBUG_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();
	~USkillComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere)
		TArray<class USKillBase*> SkillList;


	TMap<FGameplayTag, float> skillEffects;

	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class USKillBase>> BP_SkillList;
public:
	bool IsContainEffect(FGameplayTag skillTag) { return skillEffects.Contains(skillTag); }
	void AddSkillEffect(FGameplayTag skillTag, float time) { skillEffects.Emplace(skillTag, time); }
	void RemoveSkillEffect(FGameplayTag skillTag)
	{
		skillEffects.Remove(skillTag);
	}
public:
	void AddSkill(class USKillBase* skill);
	void RemoveAllSkill() { return SkillList.Empty(); }
	void UseSkill(const FGameplayTag skillTag);
	void UseSkill(int32 index);

	bool IsContainSkill(const FGameplayTag skillTag);
	const FSkillInformation* GetSkillInfo(const FGameplayTag skillTag);

public:
	void RemoveSkillTimer();
	bool SkillUsable(int32 index);
	int32 GetSkillCount() { return SkillList.Num(); }
public:
	FOnChangeCoolTime UpdateSkill1Able;
	FOnChangeCoolTime UpdateSkill2Able;
};
