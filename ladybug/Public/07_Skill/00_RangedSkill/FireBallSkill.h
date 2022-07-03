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
		TSubclassOf<class AProjectileActor> fireBall;	// 날아갈 Actor
	UPROPERTY(EditAnywhere)
		FName spawnSocketName;							// 스폰될 위치(소켓)
	UPROPERTY(EditAnywhere)
		float projectileSpeed;							// 날아갈 속도
	UPROPERTY(EditAnywhere)
		float spawnTime = 0.f;							// 스폰될 시간

protected:
	virtual void ActivateSkill() override;				// 스킬 실행

	void SpawnFireBall();								// fireball 소환	
};
