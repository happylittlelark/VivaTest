// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/VTPlayer.h"
#include "AIController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "Player/VTPlayerStart.h"
#include "Player/VTPlayerState.h"
#include "Player/VTProjectile.h"
#include "Player/VTTankPawn.h"

DEFINE_LOG_CATEGORY(LogVTPlayer);

// Sets default values
AVTPlayer::AVTPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AVTPlayer::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SpawnTank();
	}

	if (IsLocallyControlled())
	{
		SetViewTargetOnTank();
	}
}

void AVTPlayer::OnTankPawnDestroyed()
{
	if (IsValid(TankPawn))
	{
		TankPawn->OnTankPawnDestroyed.RemoveAll(this);
	}

	if (HasAuthority())
	{
		SpawnTank();
	}
}


FVector AVTPlayer::FindDeprojectedMouseLocation() const
{
	APlayerController* PlayerController = GetController<APlayerController>();
	if (!IsValid(PlayerController))
	{
		return FVector(0.f);
	}

	FVector WorldLocation;
	FVector WorldDirection;

	const bool bDeprojected = PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	if (!bDeprojected)
	{
		return FVector(0.f);
	}

	FHitResult Hit;
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(MouseDeprojectionTrace));
	
	const TArray<const AActor*> IgnoreActors = {this, TankPawn};
	TraceParams.AddIgnoredActors(IgnoreActors);
	
	bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, WorldLocation, WorldDirection * 100000.f + WorldLocation, ECollisionChannel::ECC_Visibility, TraceParams);
	return Hit.Location;
}

void AVTPlayer::FireWeapon()
{
	ServerSpawnProjectile();
}

void AVTPlayer::ChooseMoveLocation()
{
	ServerMoveToLocation(FindDeprojectedMouseLocation());

	SetViewTargetOnTank();
}

void AVTPlayer::SetViewTargetOnTank()
{
	if (!IsValid(TankPawn))
	{
		return;
	}

	SetActorTransform(TankPawn->GetCameraTransform());

	APlayerController* PlayerController = GetController<APlayerController>();

	if (!IsValid(PlayerController))
	{
		return;
	}
	
	PlayerController->SetViewTarget(TankPawn);
}

void AVTPlayer::OnRep_TankPawn()
{
	SetViewTargetOnTank();
}

void AVTPlayer::ServerSpawnProjectile_Implementation()
{
	if (!IsValid(ProjectileClass))
	{
		return;
	}
	
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;
	SpawnInfo.OverrideLevel = GetLevel();
	SpawnInfo.ObjectFlags |= RF_Transient;
	SpawnInfo.Instigator = this;
	SpawnInfo.Owner = this;
	
	const AVTProjectile* Projectile = GetWorld()->SpawnActor<AVTProjectile>(ProjectileClass, TankPawn->GetProjectileSpawnTransform(), SpawnInfo);

	if (IsValid(Projectile))
	{
		Projectile->Fire(ProjectileForce);
	}
}


void AVTPlayer::ServerMoveToLocation_Implementation(const FVector& NewLocation)
{
	TankAIController->MoveToLocation(NewLocation);
}

void AVTPlayer::SpawnTank()
{
	if (!IsValid(TankAIControllerClass))
	{
		UE_LOG(LogVTPlayer, Error, TEXT("TankAIControllerClass was invalid, therefore Tank not spawned"));

		return;
	}
	
	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsWithTag(this, AVTPlayerStart::ActiveTag, OutActors);

	if (OutActors.Num() == 0)
	{
		UE_LOG(LogVTPlayer, Error, TEXT("Couldn't find any active Player Starts, therefore Tank not spawned"));

		return;
	}

	const int RandomIndex = FMath::RandRange(0, OutActors.Num()-1);

	const AActor* SpawnPoint = OutActors[RandomIndex];

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.OverrideLevel = GetLevel();
	SpawnInfo.ObjectFlags |= RF_Transient;
	SpawnInfo.Instigator = this;
	SpawnInfo.Owner = this;

	TankAIController = GetWorld()->SpawnActor<AAIController>(TankAIControllerClass, SpawnPoint->GetActorTransform(), SpawnInfo);

	if (!IsValid(TankAIController))
	{
		UE_LOG(LogVTPlayer, Error, TEXT("Couldn't spawn Tank Controller, therefore Tank not spawned"));
		return;
	}

	TankPawn = GetWorld()->SpawnActor<AVTTankPawn>(TankPawnClass, SpawnPoint->GetActorTransform(), SpawnInfo);

	if (!IsValid(TankPawn))
	{
		UE_LOG(LogVTPlayer, Error, TEXT("Couldn't spawn TankPawn, therefore Tank not spawned"));

		return;
	}

	TankAIController->Possess(TankPawn);

	TankPawn->OnTankPawnDestroyed.AddUObject(this, &ThisClass::OnTankPawnDestroyed);
}

void AVTPlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AVTPlayer, TankPawn);
	DOREPLIFETIME(AVTPlayer, TankAIController);
}

// Called to bind functionality to input
void AVTPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	if (!ensure(EnhancedInputComponent))
	{
		return;
	}

	APlayerController* const PlayerController = GetController<APlayerController>();

	if (!IsValid(PlayerController))
	{
		return;
	}
	
	//if (const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>())
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			if (!InputMappingContext.IsNull())
			{
				InputSystem->AddMappingContext(InputMappingContext.LoadSynchronous(), 1);
			}
		}
	}
	
	for (const auto& InputMapInfo : InputActionMap)
	{
		EnhancedInputComponent->BindAction(InputMapInfo.Value.LoadSynchronous(), ETriggerEvent::Triggered, this, InputMapInfo.Key);
	}
}

void AVTPlayer::OnRep_Controller()
{
	Super::OnRep_Controller();

	APlayerController* PlayerController = GetController<APlayerController>();

	if (!IsValid(PlayerController))
	{
		return;
	}
	
	PlayerController->SetShowMouseCursor(true);

	SetViewTargetOnTank();
}

void AVTPlayer::AddScore()
{
	if (!HasAuthority())
	{
		return;
	}

	AVTPlayerState* PlayerStateLocal = GetPlayerState<AVTPlayerState>();

	if (!IsValid(PlayerStateLocal))
	{
		return;
	}

	PlayerStateLocal->ScorePoint();
}

void AVTPlayer::Zoom(const float Value)
{
	TankPawn->Zoom(Value);
}

