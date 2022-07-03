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
	// 피아식별 파티클 관리할 컴포넌트
	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* teamIdentyParticle;
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

	virtual void Tick(float DeltaTime) override;
protected:
	// 몬스터 Key
	UPROPERTY(EditAnywhere)
		FGameplayTag monsterTag;

	// 피아식별 파티클
	UPROPERTY(EditAnywhere)
		class UParticleSystem* enemyParticle;
	UPROPERTY(EditAnywhere)
		class UParticleSystem* myTeamParticle;

	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AITree;			// AITree


	UPROPERTY(EditAnywhere)
		float walkSpeed;				// 몬스터 이동 속도
	
	FTimerHandle HPBarTimerHandle;		// HPBar 위젯 Visible 타이머
	FTimerHandle StunTimerHandle;		// 몬스터 스턴 타이머

	bool bodyAppearance = false;		// 죽은 후 시체 사라지기
	float currentOpacity = 1.f;			// 시체 투명도
	UPROPERTY(EditAnywhere)
		float opacityLerpSpeed = 0.1f;	// 시체 사라지는 속도

	UPROPERTY(EditAnywhere)
		bool isBoss = false;			// 보스몬스터인지 설정
public:
	FName GetMonsterTag() { return monsterTag.GetTagName(); }
	class UBehaviorTree* GetAIBehaviorTree() { return AITree; }

	// 상태 설정
	virtual void SetMoveState(EMoveState characterState) override;
	virtual void SetActionState(EActionState actionState) override;
	virtual void SetAttackState(EAttackState attackState) override;

	// 죽었을 때 이벤트
	virtual void OnDeadEvent() override;

	// Team설정
	virtual void SetGenericTeamId(const FGenericTeamId& TeamID) override;

	void SetDeadAppearance() { bodyAppearance = true; }

	// 기본공격
	virtual void Attack();
	// 스턴
	virtual void TakeStun(float StunTime) override;

	// 능력치 설정
	void SetStat();

	// 이동 방향 구하기
	float GetMoveDirection();

	// 대미지 입을 때 델리게이트 바인딩 함수
	UFUNCTION()
		void OnTakeDamageEvent(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
