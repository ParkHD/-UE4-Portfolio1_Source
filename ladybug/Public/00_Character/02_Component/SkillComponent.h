// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "07_Skill/SKillBase.h"

#include "SkillComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeCoolTime, bool, skillAble);

// ��ų ������Ʈ
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
		TArray<class USKillBase*> SkillList;		// ������ �ִ� ��ųList

	TMap<FGameplayTag, float> skillEffects;			// ���� ���� �ǰ� �ִ� ��ų or ȿ��

	// �����Ϳ��� ������ ��ųList
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class USKillBase>> BP_SkillList;
public:
	// SkillEffect ����
	bool IsContainEffect(FGameplayTag skillTag) { return skillEffects.Contains(skillTag); }			// ���� ��ų�� ����ǰ� �ִ��� Ȯ��
	void AddSkillEffect(FGameplayTag skillTag, float time) { skillEffects.Emplace(skillTag, time); }
	void RemoveSkillEffect(FGameplayTag skillTag)
	{
		skillEffects.Remove(skillTag);
	}
public:
	// Skill ����
	void AddSkill(class USKillBase* skill);				// ��ų �߰�
	void RemoveAllSkill() { return SkillList.Empty(); }	// ��ų ����
	void UseSkill(const FGameplayTag skillTag);			// ��ų�±׸� �̿� �� ��ų ���
	void UseSkill(int32 index);							// �ε����� �̿� �� ��ų ���

	bool IsContainSkill(const FGameplayTag skillTag);	// ��ų�� �����ϰ� �ִ��� Ȯ��

	const FSkillInformation* GetSkillInfo(const FGameplayTag skillTag);	// ��ų ���� Ȯ��
public:
	void RemoveSkillTimer();							// ��ų ��Ÿ�� ����
	bool SkillUsable(int32 index);						// �ε����� �ִ� ��ų�� ��� �� �� �ִ��� Ȯ��
	int32 GetSkillCount() { return SkillList.Num(); }	// ������ �ִ� ��ų ���� Ȯ��

public:
	// ��ų ��밡������ ���� ������Ʈ
	FOnChangeCoolTime UpdateSkill1Able;
	FOnChangeCoolTime UpdateSkill2Able;
};
