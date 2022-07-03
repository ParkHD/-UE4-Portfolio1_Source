// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/BaseCharacter.h"
#include "GameplayTagContainer.h"
#include "MonsterBaseCharacter.generated.h"


UCLASS()
class LADYBUG_API AMonsterBaseCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AMonsterBaseCharacter();

protected:
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* teamIdentyParticle;
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere)
		FGameplayTag monsterTag;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* enemyParticle;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* myTeamParticle;

	UPROPERTY(EditAnywhere)
		AActor* patrolLocationActor;
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AITree;
	UPROPERTY(EditAnywhere)
	float walkSpeed;
	
	FTimerHandle HPBarTimerHandle;
	FTimerHandle StunTimerHandle;

	bool bodyAppearance = false;

	float currentOpacity = 1.f;

	UPROPERTY(EditAnywhere)
		float opacityLerpSpeed = 0.1f;
	UPROPERTY(EditAnywhere)
		bool isBoss = false;
public:
	FName GetMonsterTag() { return monsterTag.GetTagName(); }
	const AActor* GetPatrolLocationActor() { return patrolLocationActor; }
	class UBehaviorTree* GetAIBehaviorTree() { return AITree; }

	virtual void SetMoveState(EMoveState characterState) override;
	virtual void SetActionState(EActionState actionState) override;
	virtual void SetAttackState(EAttackState attackState) override;

	virtual void OnDeadEvent() override;

	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;

	void SetDeadAppearance() { bodyAppearance = true; }

	UFUNCTION()
		void OnTakeDamageEvent(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	virtual void Attack();
	virtual void TakeStun(float StunTime) override;

	void SetStat();
};
