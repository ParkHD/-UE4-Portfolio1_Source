// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"

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
		class UCapsuleComponent* sphereComponent;
	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* particleComponent;
	UPROPERTY(EditAnywhere)
		class USkeletalMeshComponent* skeletalMeshComponent;
	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* projectileComponent;
	UPROPERTY(EditAnywhere)
		class UAudioComponent* audioComponent;

public:
	class UProjectileMovementComponent* GetProjectileComponent() { return projectileComponent; }

protected:
	UPROPERTY(EditAnywhere)
		class UParticleSystem* hitParticle;

	UPROPERTY(EditAnywhere)
		bool bAttachToTarget = true;
	UPROPERTY(EditAnywhere)
		bool bHitSingle = true;
	UPROPERTY(EditAnywhere)
		bool bLifeSpan = true;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "bLifeSpan == true"))
		float lifeSpanValue;

	UPROPERTY(EditAnywhere)
		float skillDamage;
	UPROPERTY(EditAnywhere)
		bool isSkill = false;
	UPROPERTY(EditAnywhere)
		bool bIgnoreMyTeam = false;
	UPROPERTY()
		TArray<class AActor*> hitActors;
public:
	UFUNCTION()
		virtual void OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	void TurnOnCollision(bool bTurn);
	void SetSkillDamage(float damage) { skillDamage = damage; }
};

