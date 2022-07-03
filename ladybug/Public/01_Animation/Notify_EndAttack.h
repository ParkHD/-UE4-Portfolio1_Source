// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Notify_EndAttack.generated.h"


// 공격이 끝나면 ActionState::NORMAL로 변경
UCLASS()
class LADYBUG_API UNotify_EndAttack : public UAnimNotify
{
	GENERATED_BODY()
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)override;

};
