// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "GameplayTagContainer.h"
#include "BaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);

// 이동 상태
UENUM(BlueprintType)
enum class EMoveState : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	NORMAL,	// 기본상태
	RUN,	// 뛰는상태
	JUMP,	// 점프
	FLY,	// 날고있는 상태
};
// 행동 상태
UENUM(BlueprintType)
enum class EActionState : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	NORMAL,	// 기본상태
	DODGE,	// 회피 중
	ATTACK,	// 공격 중
	AIM,	// 조준 중
	BLOCK,	// 방어 중
	SKILL,	// 스킬 사용 중
	MAX,	
};
// 공격 상태
UENUM(BlueprintType)
enum class EAttackState : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	READY,		// 공격 가능 상태
	CHARGING,	// 공격 차징 중
	COOLTIME,	// 공격 불가능 -> 쿨타임 상태
};
// 회전 방향
UENUM(BlueprintType)
enum class ETurnDir : uint8
{
	NORMAL,		// 기본상태
	LEFTTURN,	// 왼쪽 회전
	RIGHTTURN,	// 오른쪽 회전
};
// Damage 타입
UENUM(BlueprintType)
enum class EDamageType : uint8
{
	NORMAL,		// 기본공격으로 인한 대미지
	SKILL,		// 스킬공격으로 인한 대미지
};

// 모든 BattleCharacter의 베이스
UCLASS()
class LADYBUG_API ABaseCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)override;

	// 데미지 타입 및 여러 설정을 위한 TakeDamage
	void TakeDamageType(EDamageType damageType, float DamageAmount, struct FDamageEvent const& DamageEvent, 
		class AController* EventInstigator, AActor* DamageCauser, bool bBreakBlock = false);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(VisibleAnywhere)
		class UStatusComponent* statusComponent;			// 스텟 컴포넌트
	UPROPERTY(VisibleAnywhere)
		class USkillComponent* skillComponent;				// 스킬 컴포넌트
	UPROPERTY(VisibleAnywhere)
		class UArmyComponent* armyComponent;				// 부대 컴포넌트


	UPROPERTY(VisibleAnywhere)
		class UChildActorComponent* WeaponChildActorComponent;	// 메인무기 액터 컴포넌트
	UPROPERTY(VisibleAnywhere)
		class UChildActorComponent* ShieldChildActorComponent;	// 보조무기 액터 컴포넌트

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UWidgetComponent* HPBarWidgetComponent;			// BPBarWidget

	// 타겟 감지
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UAIPerceptionStimuliSourceComponent* AIPerceptionStimuliSourceComponent;
public:
	class UStatusComponent* GetStatusComponent() { return statusComponent; }
	class USkillComponent* GetSkillComponent() { return skillComponent; }
	class UChildActorComponent* GetWeaponComponent() { return WeaponChildActorComponent; }
	class UChildActorComponent* GetShieldComponent() { return ShieldChildActorComponent; }
	class UWidgetComponent* GetHPBarWidgetComponent() { return HPBarWidgetComponent; }
	class UArmyComponent* GetArmyComponent() { return armyComponent; }
protected:
	UPROPERTY(VisibleAnywhere)
		class AWorldBaseCharacter* ownerWorldCharacter;		// WorldCharacter로 BattleCharacter의 본체
	UPROPERTY(VisibleAnywhere)
		EMoveState MoveState;								// 캐릭터가 어떤 이동을 하고 있는지?
	UPROPERTY(VisibleAnywhere)
		EActionState ActionState = EActionState::NORMAL;	// 캐릭터가 어떤 행동을 하고 있는지?
	UPROPERTY(VisibleAnywhere)
		EAttackState AttackState = EAttackState::READY;		// 캐릭터가 공격 할 수 있는 상태인지?

	TArray<AActor*> hitActors;			// 캐릭터가 대미지를 준 Actors -> 하나의 타겟이 중복으로 데미지를 안 입게 하기 위하여

	UPROPERTY(EditAnywhere)
		FGenericTeamId myTeam;			// TeamID

	UPROPERTY(EditAnywhere)
		UAnimationAsset* deadAnimation;	// 죽는 애니메이션

public:
	class AWorldBaseCharacter* GetWorldBaseCharacter() { return ownerWorldCharacter; }
	void SetWorldBaseCharacter(class AWorldBaseCharacter* worldCharacter) { ownerWorldCharacter = worldCharacter; }

	EMoveState GetMoveState() { return MoveState; }
	virtual void SetMoveState(EMoveState characterState);

	EActionState GetActionState() { return ActionState; }
	virtual void SetActionState(EActionState actionState);

	EAttackState GetAttackState() { return AttackState; }
	virtual void SetAttackState(EAttackState attackState);

	// hitActors관리 함수
	bool AddHitActors(AActor* target);		// hitActos에 Actor추가
	void ClearHitActors();					// hitActos 초기화

	virtual void SetGenericTeamId(const FGenericTeamId& TeamID);
	virtual FGenericTeamId GetGenericTeamId() const { return myTeam; }

	virtual void TakeStun(float StunTime);			// 스턴 함수

public:
	ETurnDir turnDir;				// 캐릭터 회전 방향
protected:
	UPROPERTY(EditAnywhere)
		float addforce = 50.f;		// 서로 다른 Actor끼리 밀어내는 힘 수치

	bool isBlockSuccess = false;	// 방어 성공했는지?


	UPROPERTY(EditAnywhere)
		bool isDead = false;		// 캐릭터가 죽었는지?
protected:
	// 애니메이션 설정
	UPROPERTY(EditAnywhere)
		class UAnimBlueprint* defaultAnimationBP;						// 기본 AnimInstance
	UPROPERTY(EditAnywhere)
		class UAnimBlueprint* weaponAnimationBP = defaultAnimationBP;	// 현재 무기의 AnimInstance

	// 몽타주 설정
	UPROPERTY(EditAnywhere)
		class UAnimMontage* attackMontage;		// 기본 공격 몽타주
	UPROPERTY(EditAnywhere)
		class UAnimMontage* hitMontage;			// 기본 피격 몽타주
	UPROPERTY(EditAnywhere)
		class UAnimMontage* hitOnFlyMontage;	// 공중에서 피격 몽타주
	UPROPERTY(EditAnywhere)
		class UAnimMontage* hitBlockMontage;	// 방어 중 피격 몽타주


	UPROPERTY(EditAnywhere)
		class USoundBase* hitSound;			// 피격 사운드
	UPROPERTY(EditAnywhere)
		float falloffDistance = 4000.f;		// 사운드 범위
public:
	FOnDead OnDead;

	class UAnimMontage* GetAttackMontage() { return attackMontage; }
	bool IsDead() const { return isDead; }

public:
	// 다른 Actor끼리 부딪히면 서로 밀어내도록 설정
	UFUNCTION()
		void OnMeshComponentOvelapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnDeadEvent();
};
