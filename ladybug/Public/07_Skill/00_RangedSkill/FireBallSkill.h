// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "07_Skill/SKillBase.h"
#include "FireBallSkill.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API UFireBallSkill : public USKillBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AProjectileActor> fireBall;
	UPROPERTY(EditAnywhere)
		FName spawnSocketName;
	UPROPERTY(EditAnywhere)
		float projectileSpeed;
	UPROPERTY(EditAnywhere)
		float spawnTime = 0.f;

protected:
	virtual void ActivateSkill() override;

	void SpawnFireBall();
};
