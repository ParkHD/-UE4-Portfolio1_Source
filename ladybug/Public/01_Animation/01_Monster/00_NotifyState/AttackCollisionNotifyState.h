// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackCollisionNotifyState.generated.h"

// 콜리전을 생성하여 공격 
UCLASS()
class LADYBUG_API UAttackCollisionNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

protected:
	UPROPERTY()
	class ABaseCharacter* owner;		// owner

	
	UPROPERTY()
		TArray<class AActor*> hitActor;		// 한 타겟이 중복 되게 공격 안 받도록 방지 

	UPROPERTY(EditAnywhere)
		bool isSkill = false;				// 스킬공격인지 기본공격인지 구분
	UPROPERTY(EditAnywhere)
		bool isBreakBlock = false;			// 상대의 방어를 무시할 것인가?
	UPROPERTY(EditAnywhere)
		bool bMultiAttack = false;			// 여러명을 공격하는 멀티 공격인가?

	// 콜리전 설정
	UPROPERTY(EditAnywhere)
		FName startSocketName;			// 콜리전 생성 위치 시작점
	UPROPERTY(EditAnywhere)
		FName endSocketName;			// 콜리전 생성 위치 끝점
	UPROPERTY(EditAnywhere)
		float collisionHeight = 50.f;	// 콜리전 높이
	UPROPERTY(EditAnywhere);
		float collisionRadius;			// 콜리전 반지름
};
