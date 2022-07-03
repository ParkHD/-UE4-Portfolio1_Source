// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "06_ProjectileActor/ProjectileActor.h"
#include "ExplodeProjectileActor.generated.h"

/**
 * 
 */
UCLASS()
class LADYBUG_API AExplodeProjectileActor : public AProjectileActor
{
	GENERATED_BODY()

public:
	virtual void OnComponentBeginOverlapEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)override;
protected:
	UPROPERTY(EditAnywhere)
		float radius = 1.f;
	// 터졌을 때 주변에 얼마나 힘을 가할 건가
	UPROPERTY(EditAnywhere)
		float force = 1.f;
};
