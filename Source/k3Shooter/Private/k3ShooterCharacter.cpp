// Fill out your copyright notice in the Description page of Project Settings.


#include "k3ShooterCharacter.h"

// Sets default values
Ak3ShooterCharacter::Ak3ShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Ak3ShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (TargetWord == "") GetNewTargetWord();
}

// Called every frame
void Ak3ShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Ak3ShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("AnyKey", IE_Released, this, &Ak3ShooterCharacter::OnAnyKeyPress);
}

void Ak3ShooterCharacter::OnAnyKeyPress(FKey key){
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, key.GetFName().ToString());
}

void Ak3ShooterCharacter::GetNewTargetWord(){
	Uk3ShooterGameInstance* GI = Cast<Uk3ShooterGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	Typed = "";

	if (GI){
		TargetWord = GI->GetRandomWordOfLength(CurrentWordLength);
	} else TargetWord = "ERROR02";
}


// Compare the two words (target and typed) and calculate a score based on the numbers of correct letters.
float Ak3ShooterCharacter::CompareAndGetScore(){
	if (CurrentWordLength != TargetWord.Len() || TargetWord.Len() != Typed.Len()) return 0.0f; //If the words aren't the same length, calling this makes no sense.

	float score = 0.0f;

	for (int i = 0; i < CurrentWordLength; i++){
		if (TargetWord.Mid(i,1).Equals(Typed.Mid(i,1), ESearchCase::IgnoreCase)) score += 1.0f; //Add modifiers here if needed.
	}

	return score;
}