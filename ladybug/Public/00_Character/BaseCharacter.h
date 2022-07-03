// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "GameplayTagContainer.h"
#include "BaseCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDead);

// �̵� ����
UENUM(BlueprintType)
enum class EMoveState : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	NORMAL,	// �⺻����
	RUN,	// �ٴ»���
	JUMP,	// ����
	FLY,	// �����ִ� ����
};
// �ൿ ����
UENUM(BlueprintType)
enum class EActionState : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	NORMAL,	// �⺻����
	DODGE,	// ȸ�� ��
	ATTACK,	// ���� ��
	AIM,	// ���� ��
	BLOCK,	// ��� ��
	SKILL,	// ��ų ��� ��
	MAX,	
};
// ���� ����
UENUM(BlueprintType)
enum class EAttackState : uint8 // Enum�̸� �տ� E�� �ٿ�����
{
	READY,		// ���� ���� ����
	CHARGING,	// ���� ��¡ ��
	COOLTIME,	// ���� �Ұ��� -> ��Ÿ�� ����
};
// ȸ�� ����
UENUM(BlueprintType)
enum class ETurnDir : uint8
{
	NORMAL,		// �⺻����
	LEFTTURN,	// ���� ȸ��
	RIGHTTURN,	// ������ ȸ��
};
// Damage Ÿ��
UENUM(BlueprintType)
enum class EDamageType : uint8
{
	NORMAL,		// �⺻�������� ���� �����
	SKILL,		// ��ų�������� ���� �����
};

// ��� BattleCharacter�� ���̽�
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

	// ������ Ÿ�� �� ���� ������ ���� TakeDamage
	void TakeDamageType(EDamageType damageType, float DamageAmount, struct FDamageEvent const& DamageEvent, 
		class AController* EventInstigator, AActor* DamageCauser, bool bBreakBlock = false);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(VisibleAnywhere)
		class UStatusComponent* statusComponent;			// ���� ������Ʈ
	UPROPERTY(VisibleAnywhere)
		class USkillComponent* skillComponent;				// ��ų ������Ʈ
	UPROPERTY(VisibleAnywhere)
		class UArmyComponent* armyComponent;				// �δ� ������Ʈ


	UPROPERTY(VisibleAnywhere)
		class UChildActorComponent* WeaponChildActorComponent;	// ���ι��� ���� ������Ʈ
	UPROPERTY(VisibleAnywhere)
		class UChildActorComponent* ShieldChildActorComponent;	// �������� ���� ������Ʈ

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		class UWidgetComponent* HPBarWidgetComponent;			// BPBarWidget

	// Ÿ�� ����
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
		class AWorldBaseCharacter* ownerWorldCharacter;		// WorldCharacter�� BattleCharacter�� ��ü
	UPROPERTY(VisibleAnywhere)
		EMoveState MoveState;								// ĳ���Ͱ� � �̵��� �ϰ� �ִ���?
	UPROPERTY(VisibleAnywhere)
		EActionState ActionState = EActionState::NORMAL;	// ĳ���Ͱ� � �ൿ�� �ϰ� �ִ���?
	UPROPERTY(VisibleAnywhere)
		EAttackState AttackState = EAttackState::READY;		// ĳ���Ͱ� ���� �� �� �ִ� ��������?

	TArray<AActor*> hitActors;			// ĳ���Ͱ� ������� �� Actors -> �ϳ��� Ÿ���� �ߺ����� �������� �� �԰� �ϱ� ���Ͽ�

	UPROPERTY(EditAnywhere)
		FGenericTeamId myTeam;			// TeamID

	UPROPERTY(EditAnywhere)
		UAnimationAsset* deadAnimation;	// �״� �ִϸ��̼�

public:
	class AWorldBaseCharacter* GetWorldBaseCharacter() { return ownerWorldCharacter; }
	void SetWorldBaseCharacter(class AWorldBaseCharacter* worldCharacter) { ownerWorldCharacter = worldCharacter; }

	EMoveState GetMoveState() { return MoveState; }
	virtual void SetMoveState(EMoveState characterState);

	EActionState GetActionState() { return ActionState; }
	virtual void SetActionState(EActionState actionState);

	EAttackState GetAttackState() { return AttackState; }
	virtual void SetAttackState(EAttackState attackState);

	// hitActors���� �Լ�
	bool AddHitActors(AActor* target);		// hitActos�� Actor�߰�
	void ClearHitActors();					// hitActos �ʱ�ȭ

	virtual void SetGenericTeamId(const FGenericTeamId& TeamID);
	virtual FGenericTeamId GetGenericTeamId() const { return myTeam; }

	virtual void TakeStun(float StunTime);			// ���� �Լ�

public:
	ETurnDir turnDir;				// ĳ���� ȸ�� ����
protected:
	UPROPERTY(EditAnywhere)
		float addforce = 50.f;		// ���� �ٸ� Actor���� �о�� �� ��ġ

	bool isBlockSuccess = false;	// ��� �����ߴ���?


	UPROPERTY(EditAnywhere)
		bool isDead = false;		// ĳ���Ͱ� �׾�����?
protected:
	// �ִϸ��̼� ����
	UPROPERTY(EditAnywhere)
		class UAnimBlueprint* defaultAnimationBP;						// �⺻ AnimInstance
	UPROPERTY(EditAnywhere)
		class UAnimBlueprint* weaponAnimationBP = defaultAnimationBP;	// ���� ������ AnimInstance

	// ��Ÿ�� ����
	UPROPERTY(EditAnywhere)
		class UAnimMontage* attackMontage;		// �⺻ ���� ��Ÿ��
	UPROPERTY(EditAnywhere)
		class UAnimMontage* hitMontage;			// �⺻ �ǰ� ��Ÿ��
	UPROPERTY(EditAnywhere)
		class UAnimMontage* hitOnFlyMontage;	// ���߿��� �ǰ� ��Ÿ��
	UPROPERTY(EditAnywhere)
		class UAnimMontage* hitBlockMontage;	// ��� �� �ǰ� ��Ÿ��


	UPROPERTY(EditAnywhere)
		class USoundBase* hitSound;			// �ǰ� ����
	UPROPERTY(EditAnywhere)
		float falloffDistance = 4000.f;		// ���� ����
public:
	FOnDead OnDead;

	class UAnimMontage* GetAttackMontage() { return attackMontage; }
	bool IsDead() const { return isDead; }

public:
	// �ٸ� Actor���� �ε����� ���� �о���� ����
	UFUNCTION()
		void OnMeshComponentOvelapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		virtual void OnDeadEvent();
};
