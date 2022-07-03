// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "GameplayTagContainer.h"
#include "BaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);

UENUM(BlueprintType)
enum class EMoveState : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	NORMAL,
	RUN,
	JUMP,
	FLY,
};
UENUM(BlueprintType)
enum class EActionState : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	NORMAL,
	ATTACK,
	AIM,
	BLOCK,
	SKILL,
	MAX,
};

UENUM(BlueprintType)
enum class EAttackState : uint8 // Enum이름 앞에 E꼭 붙여야함
{
	READY,
	CHARGING,
	COOLTIME,
};

UENUM(BlueprintType)
enum class ETurnDir : uint8
{
	NORMAL,
	LEFTTURN,
	RIGHTTURN,
};
UENUM(BlueprintType)
enum class EDamageType : uint8
{
	NORMAL,
	SKILL,
};
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
	void TakeDamageType(EDamageType damageType, float DamageAmount, struct FDamageEvent const& DamageEvent, 
		class AController* EventInstigator, AActor* DamageCauser, bool bBreakBlock = false);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(VisibleAnywhere)
		class UStatusComponent* statusComponent;
	UPROPERTY(VisibleAnywhere)
		class USkillComponent* skillComponent;

	UPROPERTY(VisibleAnywhere)
		class UChildActorComponent* WeaponChildActorComponent;
	UPROPERTY(VisibleAnywhere)
		class UChildActorComponent* ShieldChildActorComponent;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UWidgetComponent* HPBarWidgetComponent;
	
	UPROPERTY(VisibleAnywhere)
		class UArmyComponent* armyComponent;

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
		class AWorldBaseCharacter* ownerWorldCharacter;
	UPROPERTY(VisibleAnywhere)
		EMoveState MoveState;
	UPROPERTY(VisibleAnywhere)
		EActionState ActionState = EActionState::NORMAL;
	UPROPERTY(VisibleAnywhere)
		EAttackState AttackState = EAttackState::READY;

	// 내 공격에 맞은 Actors
	TArray<AActor*> hitActors;

	UPROPERTY(EditAnywhere)
		FGenericTeamId myTeam;

	UPROPERTY(EditAnywhere)
		UAnimationAsset* deadAnimation;

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
	bool AddHitActors(AActor* target);
	void ClearHitActors();

	virtual void SetGenericTeamId(const FGenericTeamId& TeamID);
	virtual FGenericTeamId GetGenericTeamId() const { return myTeam; }

	virtual void TakeStun(float StunTime);

	UFUNCTION()
	void OnMeshComponentOvelapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnDeadEvent();
public:
	ETurnDir turnDir;
protected:
	UPROPERTY(EditAnywhere)
		float addforce = 50.f;
	bool isBlockSuccess = false;

	UPROPERTY(EditAnywhere)
		float spawnInterval;
	UPROPERTY(EditAnywhere)
		bool isDead = false;
protected:
	// 애니메이션 설정
	UPROPERTY(EditAnywhere)
		class UAnimBlueprint* defaultAnimationBP;
	UPROPERTY(EditAnywhere)
		class UAnimBlueprint* weaponAnimationBP = defaultAnimationBP;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* attackMontage;

	UPROPERTY(EditAnywhere)
		class UAnimMontage* hitMontage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* hitOnFlyMontage;
	UPROPERTY(EditAnywhere)
		class UAnimMontage* hitBlockMontage;

	UPROPERTY(EditAnywhere)
		class USoundBase* hitSound;
	UPROPERTY(EditAnywhere)
		float falloffDistance = 4000.f;
public:
	FOnDead OnDead;

	class UAnimMontage* GetAttackMontage() { return attackMontage; }
	bool IsDead() const { return isDead; }


};
