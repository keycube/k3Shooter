// Fill out your copyright notice in the Description page of Project Settings.


#include "k3ShooterEnemyBase.h"

// Sets default values
Ak3ShooterEnemyBase::Ak3ShooterEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
    RootComponent = BoxCollision;

    // Create StaticMeshComponent and attach to BoxComponent
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMesh->SetupAttachment(BoxCollision);

	// Create StaticMeshComponent and attach to BoxComponent
    HealthBar = CreateDefaultSubobject<UMaterialBillboardComponent>(TEXT("HealthBarBillboard"));
    HealthBar->SetupAttachment(BoxCollision);

}

// Called when the game starts or when spawned
void Ak3ShooterEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	GetPlayer();
	ResetToDefaultValues();


	// Snap to ground so it looks more natural
	FHitResult hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	GetWorld()->LineTraceSingleByChannel(hit, GetActorLocation(), (GetActorLocation() + GetActorUpVector() * -500.0f), ECC_WorldStatic, QueryParams);

	//We snap to ground based on the static mesh because it's the visual part
	if (hit.bBlockingHit) SetActorLocation(hit.ImpactPoint + (StaticMesh->Bounds.BoxExtent.Z));

}

// Called every frame
void Ak3ShooterEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector movement = (GetPlayer()->GetActorLocation() - GetActorLocation()) * MovementSpeed * DeltaTime;
	movement.Z = 0.0f;
	SetActorLocation(GetActorLocation()+movement);

	if (CurrentHealth <= 0.0f){
		OnDeath();
		Destroy();
	}
}

void Ak3ShooterEnemyBase::OnOverlap(AActor* MyActor, AActor* OtherActor){

}

void Ak3ShooterEnemyBase::OnEndOverlap(AActor* MyActor, AActor* OtherActor){
	
}

Ak3ShooterCharacter* Ak3ShooterEnemyBase::GetPlayer(){
	if (Player) return Player;
	else return Cast<Ak3ShooterCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), Ak3ShooterCharacter::StaticClass()));
}


// You need to implement these yourself
void Ak3ShooterEnemyBase::ResetToDefaultValues_Implementation(){}
void Ak3ShooterEnemyBase::OnDeath_Implementation(){}