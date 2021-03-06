// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"

// 날라가면서 대미지를 주는 Actor(화살, fireball ...)
UCLASS()
class LADYBUG_API AProjectileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileActor();

protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	UPROPERTY(EditAnywhere)
		class UCapsuleComponent* sphereComponent;					// 공격 반응을 할 콜리전
	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* particleComponent;			// 효과
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* skeletalMeshComponent;		
	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* projectileComponent;
	UPROPERTY(EditAnywhere)
		class UAudioComponent* audioComponent;						// 사운드

public:
	class UProjectileMovementComponent* GetProjectileComponent() { return projectileComponent; }

protected:
	UPROPERTY(EditAnywhere)
		class UParticleSystem* hitParticle;		// overlap반응 시 터지는 효과

	UPROPERTY(EditAnywhere)
		bool bAttachToTarget = true;		// overlap 시 타겟에 붙을 것인가
	UPROPERTY(EditAnywhere)
		bool bHitSingle = true;				// 하나의 대상에만 대미지를 줄 것인가
	UPROPERTY(EditAnywhere)
		bool bLifeSpan = true;				// 생명주기 설정
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bLifeSpan == true"))
		float lifeSpanValue;				// 생명주기 값 설정

	UPROPERTY(EditAnywhere)
		float skillDamage;					// 대미지
	UPROPERTY(EditAnywhere)
		bool isSkill = false;				// 스킬공격인가?(스킬 or 기본화살)
	UPROPERTY(EditAnywhere)
		bool bIgnoreMyTeam = false;			// 내 팀은 무시하고 지나갈 것인가
	UPROPERTY()
		TArray<class AActor*> hitActors;	// 대미지를 받은 ActorList
public:
	UFUNCTION()
		virtual void OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	void TurnOnCollision(bool bTurn);
	void SetSkillDamage(float damage) { skillDamage = damage; }	// 대미지 설정
};

