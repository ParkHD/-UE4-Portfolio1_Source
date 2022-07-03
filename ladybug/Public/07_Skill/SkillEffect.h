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
enum class EEffectType : uint8 // Enum�̸� �տ� E�� �ٿ�����
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
	// Effect�� Ÿ�ٿ� �����Ѵ�.
	void ApplyEffect(class ABaseCharacter* target);

	// Cost�� ����� �ִ��� üũ�Ѵ�.
	bool CheckEffectValue(class ABaseCharacter* target);

public:
	void RemoveTimer(class ABaseCharacter* target);
};
