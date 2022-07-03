// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "SkillEffect.generated.h"

// 즉시 또는 지속적으로 Cost하는지(쿨타임 / MP소모)
UENUM(BlueprintType)
enum class EEffectType : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	INSTANT,
	DURATION,
};
// 효과를 줄 타겟(스텟)
UENUM(BlueprintType)
enum class EEffectTarget : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	HP,
	MP,
	SP,
	DAMAGE,
	ATTACKSPEED,
	SPEED,
	COOLTIME
};
UCLASS(Blueprintable)
class LADYBUG_API USkillEffect : public UObject
{
	GENERATED_BODY()
public:
	~USkillEffect();
protected:
	virtual void BeginDestroy() override;
protected:
	UPROPERTY(EditAnywhere)
		FGameplayTag effectTag;
	UPROPERTY(EditAnywhere)
		EEffectType effectType;		// 타입(즉시 적용, 지속 적용)
	UPROPERTY(EditAnywhere)
		EEffectTarget effectTarget;	// 어디에 효과를 부여할 것인지(스텟)
	UPROPERTY(EditAnywhere)
		float effectValue;			// cost값
	UPROPERTY(EditAnywhere)
		float effectTime;			// cooltime 값

	FTimerHandle endEffectTimer;
public:
	FGameplayTag& GetEffectTag() { return effectTag; }
	const float GetEffectValue() { return effectValue; }

protected:
	// Effect 적용 -> ApplyEffect에서 관리
	void ApplyDurationEffect(class ABaseCharacter* target);
	void ApplyInstantEffect(class ABaseCharacter* target);

	// Effect 삭제
	void RemoveEffect(class ABaseCharacter* target);
public:
	// Effect를 타겟에 적용한다.
	void ApplyEffect(class ABaseCharacter* target);

	// Cost가 충분히 있는지 체크한다.
	bool CheckEffectValue(class ABaseCharacter* target);

public:
	// 타이머 제거
	void RemoveTimer(class ABaseCharacter* target);
};
