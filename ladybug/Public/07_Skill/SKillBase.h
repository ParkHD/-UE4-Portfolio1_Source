// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "SkillEffect.h"
#include "SKillBase.generated.h"

// 스킬 정보
USTRUCT(BlueprintType)
struct FSkillInformation : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FGameplayTag skill_Tag;				// 스킬 태그

	UPROPERTY(EditAnywhere)
		FString skill_Name;					// 스킬 이름
	UPROPERTY(EditAnywhere)
		class UTexture2D* skill_Image;		// 스킬 이미지
	UPROPERTY(EditAnywhere)
		FString skill_Description;			// 스킬 설명
	UPROPERTY(EditAnywhere)
		float skill_Damage;					// 스킬 대미지(%)
	UPROPERTY(EditAnywhere)
		float skill_AttackRange;			// 스킬 범위(사용 할 수 있는 거리)
	UPROPERTY(EditAnywhere)
		float skill_CoolTime;				// 스킬 쿨타임
	UPROPERTY(EditAnywhere)
		class UAnimMontage* skill_Montage;	// 스킬 애니메이션
};

// 스킬 Base
UCLASS(Blueprintable, Blueprintable)
class LADYBUG_API USKillBase : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		FGameplayTag skillTag;				// 스킬 종류를 구분할 Tag
	UPROPERTY(EditAnywhere)
		class UDataTable* skillDataTable;
	UPROPERTY()
		FSkillInformation skillInfo;

	UPROPERTY()
		class ABaseCharacter* skillOwner;	// 스킬 주인
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> coolTimeEffect;	// 스킬의 쿨타임을 관리할 effect
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> costEffect;		// 스킬의 Cost를 관리할 effect
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> buffEffect;		// 스킬의 버프를 관리할 effect

	// UseSkill로 관리
public:
	virtual bool CommitSkill();		// 스킬을 실행할 수 있는지 확인
protected:
	virtual void ActivateSkill();	// 스킬 실행
	virtual void EndSkill();		// 스킬 종료

public:
	const FSkillInformation* GetSkillInfo();

	void UseSkill(class ABaseCharacter* caller); // 스킬 사용
public:
	FGameplayTag GetCoolTimeTag();
	void RemoveTimer();							// 타이머들 초기화 -> Level이동 시 타이머가 돌아가고 있으면 오류 발생
	void SetSkillOwner(class ABaseCharacter* SkillOwner) { skillOwner = SkillOwner; }
};
