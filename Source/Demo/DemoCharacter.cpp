// Copyright Epic Games, Inc. All Rights Reserved.

#include "DemoCharacter.h"
#include "AbilitySystemComponent.h"
#include "Weapon.h"
#include "Scroll.h"
#include "TimerManager.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "DraconicArcanisAbility.h"
#include "DraconicArcanisAction.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ADemoCharacter

ADemoCharacter::ADemoCharacter()
{
	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System Component"));
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	 // Initialize stance
    CurrentStance = EDragonicArconisStance::PowerUp;

	// Initialize attack rate, example: attack every 1.5 seconds
    AttackRate = 1.5f;
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ADemoCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}
//////////////////////////////////////////////////////////////////////////
// Input

void ADemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ADemoCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ADemoCharacter::Look);

        // Dragonic Arconist
        EnhancedInputComponent->BindAction("UseDragonicArconisPower", ETriggerEvent::Triggered, this, &ADemoCharacter::UseDragonicArconisPower);
        EnhancedInputComponent->BindAction("CycleDragonicArconis", ETriggerEvent::Triggered, this, &ADemoCharacter::CycleDragonicArconis);
		PlayerInputComponent->BindAction("UseDragonicArconisPower", IE_Pressed, this, &ADemoCharacter::UseDragonicArconisPower);
    	PlayerInputComponent->BindAction("CycleDragonicArconis", IE_Pressed, this, &ADemoCharacter::CycleDragonicArconis);

        // AutoAttack 
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ADemoCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

//Dragonic Arconist
{
    Super::BeginPlay();

    // Give the ability to the character
    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(UDraconicArcanisAbility::StaticClass(), 1, 0));
        AbilitySystemComponent->InitAbilityActorInfo(this, this);
    }
}

UAbilitySystemComponent* ADemoCharacter::GetAbilitySystemComponent() const
{
    return AbilitySystemComponent;
}

void ADemoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(DraconicArcanisAction, ETriggerEvent::Triggered, this, &ADemoCharacter::ActivateDraconicArcanis);
    }
}

void ADemoCharacter::AutoAttack(AActor* Target)
{
    if (Target == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("Target is null. Cannot initiate auto-attack."));
        return;
    }

    CurrentTarget = Target;
    GetWorld()->GetTimerManager().SetTimer(AttackTimerHandle, this, &ADemoCharacter::PerformAttack, AttackRate, true);

    // Move towards the target if out of range
    MoveTowardsTarget();
}

void ADemoCharacter::StopAutoAttack()
{
    GetWorld()->GetTimerManager().ClearTimer(AttackTimerHandle);
    CurrentTarget = nullptr;
}

void ADemoCharacter::PerformAttack()
{
    if (CurrentTarget == nullptr)
    {
        StopAutoAttack();
        return;
    }

    float WeaponRange = 200.0f; // Example range, replace with actual value
    float DistanceToTarget = FVector::Dist(GetActorLocation(), CurrentTarget->GetActorLocation());

    if (DistanceToTarget <= WeaponRange)
    {
        // Perform the attack on the target
        UE_LOG(LogTemp, Log, TEXT("Attacking target: %s"), *CurrentTarget->GetName());

        // Add attack logic here (e.g., decreasing health, playing animation, etc.)
    }
    else
    {
        // Target is out of range, move towards the target
        MoveTowardsTarget();
    }
}

void ADemoCharacter::MoveTowardsTarget()
{
    if (CurrentTarget != nullptr)
    {
        UE_LOG(LogTemp, Log, TEXT("Moving towards target: %s"), *CurrentTarget->GetName());

        // Example movement logic
        FVector TargetLocation = CurrentTarget->GetActorLocation();
        UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
        if (NavSystem)
        {
            FNavLocation NavLocation;
            NavSystem->GetRandomPointInNavigableRadius(TargetLocation, 0.0f, NavLocation);
            MoveToLocation(NavLocation.Location);
        }
    }
}

// Placeholder function for moving to a location (replace with actual movement logic)
void ADemoCharacter::MoveToLocation(const FVector& Location)
{
    // Example movement logic using Unreal Engine's AI system
    UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Location);
}
void ADemoCharacter::ActivateDraconicArcanis()
{
    if (AbilitySystemComponent)
    {
        AbilitySystemComponent->TryActivateAbilityByClass(UDraconicArcanisAbility::StaticClass());
    }
}
void ADemoCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

// Use Dragonic Arconis Power
void ADemoCharacter::UseDragonicArconisPower()
{
    switch (CurrentStance)
    {
        case EDragonicArconisStance::PowerUp:
            DragonicArconisPowerUp();
            break;
        case EDragonicArconisStance::Support:
            DragonicArconisSupport();
            break;
        case EDragonicArconisStance::Defense:
            DragonicArconisDefense();
            break;
        default:
            break;
    }
}

// Power-Up: Increase AD or AP
void ADemoCharacter::DragonicArconisPowerUp()
{
    AttackDamage += 20.0f;
    AbilityPower += 10.0f;
    UE_LOG(LogTemp, Warning, TEXT("Power-Up activated: AD and AP increased"));
}

// Support: Provide utility like healing or state switching
void ADemoCharacter::DragonicArconisSupport()
{
    Health += 100.0f; // Example: Heal the character
    UE_LOG(LogTemp, Warning, TEXT("Support activated: Health increased"));
}

// Defense: Take a defensive stance
void ADemoCharacter::DragonicArconisDefense()
{
    Defense += 5.0f; // Example: Increase defense
    UE_LOG(LogTemp, Warning, TEXT("Defense activated: Defense increased"));
}

// Cycle through different Dragonic Arconis abilities
void ADemoCharacter::CycleDragonicArconis()
{
    switch (CurrentStance)
    {
        case EDragonicArconisStance::PowerUp:
            CurrentStance = EDragonicArconisStance::Support;
            UE_LOG(LogTemp, Warning, TEXT("Switched to Support Stance"));
            break;
        case EDragonicArconisStance::Support:
            CurrentStance = EDragonicArconisStance::Defense;
            UE_LOG(LogTemp, Warning, TEXT("Switched to Defense Stance"));
            break;
        case EDragonicArconisStance::Defense:
            CurrentStance = EDragonicArconisStance::PowerUp;
            UE_LOG(LogTemp, Warning, TEXT("Switched to Power-Up Stance"));
            break;
        default:
            break;
    }
}
