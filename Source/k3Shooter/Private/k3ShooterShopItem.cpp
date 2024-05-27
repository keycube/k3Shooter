// Fill out your copyright notice in the Description page of Project Settings.


#include "k3ShooterShopItem.h"
#include "k3ShooterCharacter.h"

// Sets default values
Ak3ShooterShopItem::Ak3ShooterShopItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Ak3ShooterShopItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Ak3ShooterShopItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Ak3ShooterShopItem::TryBuy(){
	Ak3ShooterCharacter* Character = Cast<Ak3ShooterCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), Ak3ShooterCharacter::StaticClass()));
	if (Character && Character->Money >= Price){
		Character->Money -= Price;
		Buy();
	} 
}

void Ak3ShooterShopItem::Buy(){
	// No implementation, please inherit from this class then implement Buy() yourself
	// Example : Change the word, up the price, do an effect on the player, etc
}