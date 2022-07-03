// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackCollisionNotifyState.generated.h"

// �ݸ����� �����Ͽ� ���� 
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
		TArray<class AActor*> hitActor;		// �� Ÿ���� �ߺ� �ǰ� ���� �� �޵��� ���� 

	UPROPERTY(EditAnywhere)
		bool isSkill = false;				// ��ų�������� �⺻�������� ����
	UPROPERTY(EditAnywhere)
		bool isBreakBlock = false;			// ����� �� ������ ���ΰ�?
	UPROPERTY(EditAnywhere)
		bool bMultiAttack = false;			// �������� �����ϴ� ��Ƽ �����ΰ�?

	// �ݸ��� ����
	UPROPERTY(EditAnywhere)
		FName startSocketName;			// �ݸ��� ���� ��ġ ������
	UPROPERTY(EditAnywhere)
		FName endSocketName;			// �ݸ��� ���� ��ġ ����
	UPROPERTY(EditAnywhere)
		float collisionHeight = 50.f;	// �ݸ��� ����
	UPROPERTY(EditAnywhere);
		float collisionRadius;			// �ݸ��� ������
};
