// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/BaseCharacter.h"
#include "GameplayTagContainer.h"
#include "MonsterBaseCharacter.generated.h"

// Monster's Base BattleCharacter
UCLASS()
class LADYBUG_API AMonsterBaseCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AMonsterBaseCharacter();

protected:
	// �Ǿƽĺ� ��ƼŬ ������ ������Ʈ
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* teamIdentyParticle;
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

	virtual void Tick(float DeltaTime) override;
protected:
	// ���� Key
	UPROPERTY(EditAnywhere)
		FGameplayTag monsterTag;

	// �Ǿƽĺ� ��ƼŬ
	UPROPERTY(EditAnywhere)
		class UParticleSystem* enemyParticle;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* myTeamParticle;

	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AITree;			// AITree


	UPROPERTY(EditAnywhere)
		float walkSpeed;				// ���� �̵� �ӵ�
	
	FTimerHandle HPBarTimerHandle;		// HPBar ���� Visible Ÿ�̸�
	FTimerHandle StunTimerHandle;		// ���� ���� Ÿ�̸�

	bool bodyAppearance = false;		// ���� �� ��ü �������
	float currentOpacity = 1.f;			// ��ü ����
	UPROPERTY(EditAnywhere)
		float opacityLerpSpeed = 0.1f;	// ��ü ������� �ӵ�

	UPROPERTY(EditAnywhere)
		bool isBoss = false;			// ������������ ����
public:
	FName GetMonsterTag() { return monsterTag.GetTagName(); }
	class UBehaviorTree* GetAIBehaviorTree() { return AITree; }

	// ���� ����
	virtual void SetMoveState(EMoveState characterState) override;
	virtual void SetActionState(EActionState actionState) override;
	virtual void SetAttackState(EAttackState attackState) override;

	// �׾��� �� �̺�Ʈ
	virtual void OnDeadEvent() override;

	// Team����
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;

	void SetDeadAppearance() { bodyAppearance = true; }

	// �⺻����
	virtual void Attack();
	// ����
	virtual void TakeStun(float StunTime) override;

	// �ɷ�ġ ����
	void SetStat();

	// �̵� ���� ���ϱ�
	float GetMoveDirection();

	// ����� ���� �� ��������Ʈ ���ε� �Լ�
	UFUNCTION()
		void OnTakeDamageEvent(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
