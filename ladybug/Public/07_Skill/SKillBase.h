// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "GameplayTagContainer.h"
#include "SkillEffect.h"
#include "SKillBase.generated.h"

// ��ų ����
USTRUCT(BlueprintType)
struct FSkillInformation : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		FGameplayTag skill_Tag;				// ��ų �±�

	UPROPERTY(EditAnywhere)
		FString skill_Name;					// ��ų �̸�
	UPROPERTY(EditAnywhere)
		class UTexture2D* skill_Image;		// ��ų �̹���
	UPROPERTY(EditAnywhere)
		FString skill_Description;			// ��ų ����
	UPROPERTY(EditAnywhere)
		float skill_Damage;					// ��ų �����(%)
	UPROPERTY(EditAnywhere)
		float skill_AttackRange;			// ��ų ����(��� �� �� �ִ� �Ÿ�)
	UPROPERTY(EditAnywhere)
		float skill_CoolTime;				// ��ų ��Ÿ��
	UPROPERTY(EditAnywhere)
		class UAnimMontage* skill_Montage;	// ��ų �ִϸ��̼�
};

// ��ų Base
UCLASS(Blueprintable, Blueprintable)
class LADYBUG_API USKillBase : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		FGameplayTag skillTag;				// ��ų ������ ������ Tag
	UPROPERTY(EditAnywhere)
		class UDataTable* skillDataTable;
	UPROPERTY()
		FSkillInformation skillInfo;

	UPROPERTY()
		class ABaseCharacter* skillOwner;	// ��ų ����
	
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> coolTimeEffect;	// ��ų�� ��Ÿ���� ������ effect
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> costEffect;		// ��ų�� Cost�� ������ effect
	UPROPERTY(EditAnywhere)
		TSubclassOf<class USkillEffect> buffEffect;		// ��ų�� ������ ������ effect

	// UseSkill�� ����
public:
	virtual bool CommitSkill();		// ��ų�� ������ �� �ִ��� Ȯ��
protected:
	virtual void ActivateSkill();	// ��ų ����
	virtual void EndSkill();		// ��ų ����

public:
	const FSkillInformation* GetSkillInfo();

	void UseSkill(class ABaseCharacter* caller); // ��ų ���
public:
	FGameplayTag GetCoolTimeTag();
	void RemoveTimer();							// Ÿ�̸ӵ� �ʱ�ȭ -> Level�̵� �� Ÿ�̸Ӱ� ���ư��� ������ ���� �߻�
	void SetSkillOwner(class ABaseCharacter* SkillOwner) { skillOwner = SkillOwner; }
};
