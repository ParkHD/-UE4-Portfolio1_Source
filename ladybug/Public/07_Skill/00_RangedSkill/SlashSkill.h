// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "07_Skill/SKillBase.h"
#include "SlashSkill.generated.h"

/**
 * Animation으로 실행되는 Skill
 */
UCLASS()
class LADYBUG_API USlashSkill : public USKillBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		float skillFast = 1.0f;				// 애니메이션 실행 속도
public:
	virtual void ActivateSkill() override;
};
