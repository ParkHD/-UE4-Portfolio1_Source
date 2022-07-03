// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_EuqipmentActor/EquipmentActor.h"
#include "WeaponActor.generated.h"

// ����Actor
UCLASS()
class LADYBUG_API AWeaponActor : public AEquipmentActor
{
	GENERATED_BODY()
	
protected:
	virtual void PostInitializeComponents()override;
public:
	// ���� �ݸ��� ���� -> ��� ����� �ֱ�
	UFUNCTION()
		void OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);
};
