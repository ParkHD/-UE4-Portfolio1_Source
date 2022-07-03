// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_EuqipmentActor/EquipmentActor.h"
#include "WeaponActor.generated.h"

// 무기Actor
UCLASS()
class LADYBUG_API AWeaponActor : public AEquipmentActor
{
	GENERATED_BODY()
	
protected:
	virtual void PostInitializeComponents()override;
public:
	// 무기 콜리전 반응 -> 상대 대미지 주기
	UFUNCTION()
		void OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);
};
