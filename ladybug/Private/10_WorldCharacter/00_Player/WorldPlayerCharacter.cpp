// Fill out your copyright notice in the Description page of Project Settings.


#include "10_WorldCharacter/00_Player/WorldPlayerCharacter.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "00_Character/00_Player/Component/EquipmentComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/AudioComponent.h"

#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "00_Character/00_Player/Component/InventoryComponent.h"
#include "00_Character/02_Component/ArmyComponent.h"
#include "10_WorldCharacter/00_Player/WorldPlayerController.h"
#include "10_WorldCharacter/01_Monster/WorldMonsterCharacter.h"
#include "98_GameInstance/myGameInstance.h"
#include "10_WorldCharacter/02_StaticActor/00_Village/VillageWorldActor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "02_Item/Item.h"


AWorldPlayerCharacter::AWorldPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	SpringArmComponent->SetupAttachment(GetCapsuleComponent());
	SpringArmComponent->TargetArmLength = 600.0f;
	SpringArmComponent->TargetOffset.Z = 600.f;
	SpringArmComponent->SetRelativeRotation(FRotator::ZeroRotator);
	SpringArmComponent->bUsePawnControlRotation = false;	// Controller에 맞춰서 SpringArm이 움직인다.
	SpringArmComponent->bDoCollisionTest = true;			// 시야에 방해물이 있으면 확대기능

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetRelativeRotation(FRotator(-40.f, 0.f, 0.f));

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComp"));

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SetGenericTeamId(10);
}

void AWorldPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// 테스트용
	for(auto item : itemListBP)
	{
		InventoryComponent->AddItem(item.GetDefaultObject());
	}
}
void AWorldPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	OnActorBeginOverlap.AddUniqueDynamic(this, &AWorldPlayerCharacter::OnActorBeginOverlapEvent);
}

void AWorldPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (NewController != nullptr)
	{
		playerController = Cast<AWorldPlayerController>(NewController);
		// 마우스 커서 보이기
		if (playerController != nullptr)
		{
			playerController->bShowMouseCursor = true;
		}
	}
}

// Called every frame
void AWorldPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AWorldPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Move", EInputEvent::IE_Released, this, &AWorldPlayerCharacter::ReleaseMove);

	PlayerInputComponent->BindAction("ClickCameraRotate", EInputEvent::IE_Pressed, this, &AWorldPlayerCharacter::PressRotate);
	PlayerInputComponent->BindAction("ClickCameraRotate", EInputEvent::IE_Released, this, &AWorldPlayerCharacter::ReleaseRotate);

	PlayerInputComponent->BindAxis("CameraRotate", this, &AWorldPlayerCharacter::RotateCamera);
	PlayerInputComponent->BindAxis("ZoomCamera", this, &AWorldPlayerCharacter::ZoomCamera);

	PlayerInputComponent->BindAction("Inventory", EInputEvent::IE_Pressed, this, &AWorldPlayerCharacter::PressInventoryKey);
	PlayerInputComponent->BindAction("ArmyManager", EInputEvent::IE_Pressed, this, &AWorldPlayerCharacter::PressArmyManagerKey);
}

void AWorldPlayerCharacter::ReleaseMove()
{
	FHitResult hit;
	if (GetController<APlayerController>()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, hit))
	{
		// 이미 클릭 효과가 실행되고 있다면 중단 하고 새롭게 클릭된 곳에 효과 실행
		if(clickNiagaraComponent != nullptr)
		{
			clickNiagaraComponent->DeactivateImmediate();
		}
		clickNiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), clickParticle, hit.Location);
		// 캐릭터 이동
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), hit.Location);
	}
}

void AWorldPlayerCharacter::PressRotate()
{
	bClickRotate = true;	// 왼쪽 마우스 버튼 클릭
}
void AWorldPlayerCharacter::ReleaseRotate()
{
	bClickRotate = false;	// 왼쪽 마우스 버튼 클릭 해제
}
void AWorldPlayerCharacter::RotateCamera(float newAxisValue)
{
	if (bClickRotate)
	{
		// 카메라 회전
		FRotator newRotator = SpringArmComponent->GetRelativeRotation();
		newRotator.Yaw += newAxisValue;
		SpringArmComponent->SetRelativeRotation(newRotator);
	}
}
void AWorldPlayerCharacter::ZoomCamera(float newAxisValue)
{
	// 휠 방향에 따라 확대 or 축소
	SpringArmComponent->TargetArmLength = FMath::Clamp(SpringArmComponent->TargetArmLength -= newAxisValue * speed, 300.f, 1000.f);
	SpringArmComponent->TargetOffset.Z = FMath::Clamp(SpringArmComponent->TargetOffset.Z -= newAxisValue * speed, 300.f, 1000.f);
}
void AWorldPlayerCharacter::PressInventoryKey()
{
	if (playerController != nullptr)
	{
		playerController->OpenInventoryWidget();
		playerController->bShowMouseCursor = true;
	}
	else if(playerController == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("null"));

	}
}
void AWorldPlayerCharacter::PressArmyManagerKey()
{
	if (playerController != nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("OPENARMY"));
		playerController->OpenArmyManagerWidget();
		playerController->bShowMouseCursor = true;
	}
}

void AWorldPlayerCharacter::OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor)
{
	if(playerController != nullptr)
	{
		// 몬스터를 만났을 때 전투창 열고 게임 정지
		if (OtherActor->IsA<AWorldMonsterCharacter>())
		{
			auto target = Cast<AWorldMonsterCharacter>(OtherActor);
			playerController->OpenBattleWidget(target);
			UGameplayStatics::SetGamePaused(GetWorld(), true);
		}
		// 마을을 만났을 때 마을진입창 열고 게임 정지
		else if (OtherActor->IsA<AVillageWorldActor>())
		{
			auto target = Cast<AVillageWorldActor>(OtherActor);
			if (target != nullptr)
			{
				playerController->OpenVillageWidget(target);
				UGameplayStatics::SetGamePaused(GetWorld(), true);
			}
		}
	}
}

void AWorldPlayerCharacter::SetCharacterData(FSaveCharacterData CharacterData)
{
	Super::SetCharacterData(CharacterData);

	// 데이터 덮어쓰기
	InventoryComponent->SetInvenComponentData(CharacterData.InvenComponentData);
	ArmyManagerComponent->SetArmyComponentData(CharacterData.ArmyComponentData);
	EquipmentComponent->SetEquipComponentData(CharacterData.EquipComponentData);
	StatusComponent->SetStatusComponentData(CharacterData.StatusComponentData);
}
