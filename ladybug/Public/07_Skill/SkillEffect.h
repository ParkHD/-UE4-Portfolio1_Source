// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "SkillEffect.generated.h"

// ��� �Ǵ� ���������� Cost�ϴ���(��Ÿ�� / MP�Ҹ�)
UENUM(BlueprintType)
enum class EEffectType : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	INSTANT,
	DURATION,
};
// ȿ���� �� Ÿ��(����)
UENUM(BlueprintType)
enum class EEffectTarget : uint8 // Enum�̸� �տ� E�� �ٿ�����
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
		EEffectType effectType;		// Ÿ��(��� ����, ���� ����)
	UPROPERTY(EditAnywhere)
		EEffectTarget effectTarget;	// ��� ȿ���� �ο��� ������(����)
	UPROPERTY(EditAnywhere)
		float effectValue;			// cost��
	UPROPERTY(EditAnywhere)
		float effectTime;			// cooltime ��

	FTimerHandle endEffectTimer;
public:
	FGameplayTag& GetEffectTag() { return effectTag; }
	const float GetEffectValue() { return effectValue; }

protected:
	// Effect ���� -> ApplyEffect���� ����
	void ApplyDurationEffect(class ABaseCharacter* target);
	void ApplyInstantEffect(class ABaseCharacter* target);

	// Effect ����
	void RemoveEffect(class ABaseCharacter* target);
public:
	// Effect�� Ÿ�ٿ� �����Ѵ�.
	void ApplyEffect(class ABaseCharacter* target);

	// Cost�� ����� �ִ��� üũ�Ѵ�.
	bool CheckEffectValue(class ABaseCharacter* target);

public:
	// Ÿ�̸� ����
	void RemoveTimer(class ABaseCharacter* target);
};
