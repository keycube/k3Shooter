// Fill out your copyright notice in the Description page of Project Settings.


#include "k3ShooterShop.h"

// Sets default values
Ak3ShooterShop::Ak3ShooterShop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Ak3ShooterShop::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> ItemsTemp;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), Ak3ShooterShopItem::StaticClass(), ItemsTemp);
	for (auto& a : ItemsTemp){
		Items.Add(Cast<Ak3ShooterShopItem>(a));
	}
}

// Called every frame
void Ak3ShooterShop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void Ak3ShooterShop::OnKeyPress(TCHAR key){
	Typed += key;
	// Check if what we typed corresponds to any of the available items.
	for (auto& Item : Items){
		if (Item->Word.Equals(Typed, ESearchCase::IgnoreCase)){ //Exact match? attempt to buy
			Item->TryBuy();
			break; // Breaking out of the for instead of returning will also reset Typed.
		} else if (IsWordStart(Typed, Item->Word)){ //Partial match? do nothing
			return;
		}
	}

	Typed = ""; //No match? Reset what was typed
}

// Checks if a word is the start of another word.
// This only goes one way, as such if start is longer than complete, false is returned.
bool Ak3ShooterShop::IsWordStart(FString start, FString complete){
	if (start.Len() > complete.Len()) return false;
	FString cat = complete.Mid(0, start.Len()); // meow
	return start.Equals(cat, ESearchCase::IgnoreCase);
}