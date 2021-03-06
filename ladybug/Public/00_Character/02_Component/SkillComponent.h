// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "07_Skill/SKillBase.h"

#include "SkillComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangeCoolTime, bool, skillAble);

// 스킬 컴포넌트
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
		TArray<class USKillBase*> SkillList;		// 가지고 있는 스킬List

	TMap<FGameplayTag, float> skillEffects;			// 현재 적용 되고 있는 스킬 or 효과

	// 에디터에서 설정할 스킬List
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class USKillBase>> BP_SkillList;
public:
	// SkillEffect 관련
	bool IsContainEffect(FGameplayTag skillTag) { return skillEffects.Contains(skillTag); }			// 현재 스킬이 적용되고 있는지 확인
	void AddSkillEffect(FGameplayTag skillTag, float time) { skillEffects.Emplace(skillTag, time); }
	void RemoveSkillEffect(FGameplayTag skillTag)
	{
		skillEffects.Remove(skillTag);
	}
public:
	// Skill 관련
	void AddSkill(class USKillBase* skill);				// 스킬 추가
	void RemoveAllSkill() { return SkillList.Empty(); }	// 스킬 삭제
	void UseSkill(const FGameplayTag skillTag);			// 스킬태그를 이용 한 스킬 사용
	void UseSkill(int32 index);							// 인덱스를 이용 한 스킬 사용

	bool IsContainSkill(const FGameplayTag skillTag);	// 스킬을 보유하고 있는지 확인

	const FSkillInformation* GetSkillInfo(const FGameplayTag skillTag);	// 스킬 정보 확인
public:
	void RemoveSkillTimer();							// 스킬 쿨타임 제거
	bool SkillUsable(int32 index);						// 인덱스에 있는 스킬을 사용 할 수 있는지 확인
	int32 GetSkillCount() { return SkillList.Num(); }	// 가지고 있는 스킬 개수 확인

public:
	// 스킬 사용가능한지 위젯 업데이트
	FOnChangeCoolTime UpdateSkill1Able;
	FOnChangeCoolTime UpdateSkill2Able;
};
