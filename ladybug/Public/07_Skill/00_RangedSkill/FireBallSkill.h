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
		TSubclassOf<class AProjectileActor> fireBall;	// ���ư� Actor
	UPROPERTY(EditAnywhere)
		FName spawnSocketName;							// ������ ��ġ(����)
	UPROPERTY(EditAnywhere)
		float projectileSpeed;							// ���ư� �ӵ�
	UPROPERTY(EditAnywhere)
		float spawnTime = 0.f;							// ������ �ð�

protected:
	virtual void ActivateSkill() override;				// ��ų ����

	void SpawnFireBall();								// fireball ��ȯ	
};
