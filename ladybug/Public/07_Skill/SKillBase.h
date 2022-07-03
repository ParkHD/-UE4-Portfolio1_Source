// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "SkillEffect.h"
#include "SKillBase.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSkillInformation : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FGameplayTag skill_Tag;

	UPROPERTY(EditAnywhere)
		FString skill_Name;
	UPROPERTY(EditAnywhere)
		class UTexture2D* skill_Image;
	UPROPERTY(EditAnywhere)
		FString skill_Description;
	UPROPERTY(EditAnywhere)
		float skill_Damage;
	UPROPERTY(EditAnywhere)
		float skill_AttackRange;
	UPROPERTY(EditAnywhere)
		float skill_CoolTime;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* skill_Montage;
};

UCLASS(Blueprintable, Blueprintable)
class LADYBUG_API USKillBase : public UObject
{
	GENERATED_BODY()
	

protected:
	// 스킬 종류를 구분할 Tag
	UPROPERTY(EditAnywhere)
		FGameplayTag skillTag;
	UPROPERTY(EditAnywhere)
		class UDataTable* skillDataTable;
	UPROPERTY()
		FSkillInformation skillInfo;

	UPROPERTY()
		class ABaseCharacter* skillOwner;
	// 스킬의 쿨타임을 관리할 effect
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> coolTimeEffect;
	// 스킬의 Cost를 관리할 effect
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> costEffect;
public:
	virtual bool CommitSkill();
protected:
	virtual void ActivateSkill();
	virtual void EndSkill();
public:
	const FSkillInformation* GetSkillInfo();

	void UseSkill(class ABaseCharacter* caller);


public:
	FGameplayTag GetCoolTimeTag();
	void RemoveTimer();
	void SetSkillOwner(class ABaseCharacter* SkillOwner) { skillOwner = SkillOwner; }
};
