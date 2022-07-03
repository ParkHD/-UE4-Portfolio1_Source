// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "SkillEffect.generated.h"

/**
 * 
 */


UENUM(BlueprintType)
enum class EEffectType : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	INSTANT,
	DURATION,
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
		EEffectType effectType;

	UPROPERTY(EditAnywhere)
		FGameplayTag effectTag;
	UPROPERTY(EditAnywhere)
		float effectValue;
	UPROPERTY(EditAnywhere)
		float effectTime;

	FTimerHandle endEffectTimer;
public:
	FGameplayTag& GetEffectTag() { return effectTag; }
	const float GetEffectValue() { return effectValue; }

protected:
	void ApplyDurationEffect(class ABaseCharacter* target);
	void ApplyInstantEffect(class ABaseCharacter* target);

	void RemoveEffect(class ABaseCharacter* target);
public:
	// Effect를 타겟에 적용한다.
	void ApplyEffect(class ABaseCharacter* target);

	// Cost가 충분히 있는지 체크한다.
	bool CheckEffectValue(class ABaseCharacter* target);

public:
	void RemoveTimer(class ABaseCharacter* target);
};
