// Fill out your copyright notice in the Description page of Project Settings.


#include "01_Animation/FootStepNotify.h"
#include "00_Character/BaseCharacter.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystem.h"

UFootStepNotify::UFootStepNotify()
{
	static ConstructorHelpers::FObjectFinder<UParticleSystem> GroundFootParticle(TEXT("/Game/InfinityBladeEffects/Effects/FX_Monsters/FX_Monster_FrostGiant/Notifies/P_FootSteps_Walk.P_FootSteps_Walk"));
	if (GroundFootParticle.Succeeded())
	{
		footStep.GroundFootParticle = GroundFootParticle.Object;
	}
}

void UFootStepNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if(MeshComp != nullptr)
	{
		// 발 밑으로 Ray 설정
		FVector FootLocation = MeshComp->GetSocketLocation(footSocketName);
		FVector EndLocation = FootLocation - MeshComp->GetUpVector() * rayLength;
		FHitResult Hit;
		TArray<TEnumAsByte<EObjectTypeQuery>> object;
		object.Emplace(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
	
		if(UKismetSystemLibrary::LineTraceSingleForObjects(
			MeshComp->GetWorld(),
			FootLocation,
			EndLocation,
			object,
			false,
			TArray<AActor*>(),
			EDrawDebugTrace::None,
			Hit,
			true
			))
		{
			// 지형의 SurfaceType검사 후 Type에 따른 다른 발자국 및 소리 설정
			switch (UGameplayStatics::GetSurfaceType(Hit))
			{
			case EPhysicalSurface::SurfaceType1:	// 일반 지형
			{
				UGameplayStatics::SpawnEmitterAtLocation(MeshComp->GetWorld(), footStep.GroundFootParticle, FootLocation, FRotator::ZeroRotator, true);
				if(bAttenuation)	// 소리 범위 설정
				{
					FSoundAttenuationSettings setting;
					setting.FalloffDistance = falloffDistance;
					USoundAttenuation* soundAtt = NewObject<USoundAttenuation>();
					soundAtt->Attenuation = setting;

					// 사운드 재생
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), footStep.GroundFootSound, FootLocation,
						FRotator::ZeroRotator,
						1.f, 1.f, 0.f, soundAtt);
				}
				else
				{
					// 사운드 재생
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), footStep.GroundFootSound, FootLocation);
				}
				break;
			}
			case EPhysicalSurface::SurfaceType2:	// 눈 지형
			{
				UGameplayStatics::SpawnEmitterAtLocation(MeshComp->GetWorld(), footStep.SnowFootParticle, FootLocation, FRotator::ZeroRotator, true);
				if (bAttenuation)	// 소리 범위 설정
				{
					FSoundAttenuationSettings setting;
					setting.FalloffDistance = falloffDistance;
					USoundAttenuation* soundAtt = NewObject<USoundAttenuation>();
					soundAtt->Attenuation = setting;

					// 사운드 재생
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), footStep.SnowFootSound, FootLocation,
						FRotator::ZeroRotator,
						1.f, 1.f, 0.f, soundAtt);
				}
				else
				{
					// 사운드 재생
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), footStep.SnowFootSound, FootLocation);
				}
				break;
			}
			case EPhysicalSurface::SurfaceType3:	// 물 지형
			{
				UGameplayStatics::SpawnEmitterAtLocation(MeshComp->GetWorld(), footStep.WaterFootParticle, FootLocation, FRotator::ZeroRotator, true);
				if (bAttenuation)	// 소리 범위 설정
				{
					FSoundAttenuationSettings setting;
					setting.FalloffDistance = falloffDistance;
					USoundAttenuation* soundAtt = NewObject<USoundAttenuation>();
					soundAtt->Attenuation = setting;

					// 사운드 재생
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), footStep.WaterFootSound, FootLocation,
						FRotator::ZeroRotator,
						1.f, 1.f, 0.f, soundAtt);
				}
				else
				{
					// 사운드 재생
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), footStep.WaterFootSound, FootLocation);
				}
				break;
			}
			default:
				UGameplayStatics::SpawnEmitterAtLocation(MeshComp->GetWorld(), footStep.GroundFootParticle, FootLocation, FRotator::ZeroRotator, true);
				if (bAttenuation)	// 소리 범위 설정
				{
					FSoundAttenuationSettings setting;
					setting.FalloffDistance = falloffDistance;
					USoundAttenuation* soundAtt = NewObject<USoundAttenuation>();
					soundAtt->Attenuation = setting;

					// 사운드 재생
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), footStep.GroundFootSound, FootLocation,
						FRotator::ZeroRotator,
						1.f, 1.f, 0.f, soundAtt);
				}
				else
				{
					// 사운드 재생
					UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), footStep.GroundFootSound, FootLocation);
				}
				break;
			}
		}
		
	}
}
