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
	PlayerInputComponent->BindAction("AnyKey", IE_Released, this, &Ak3ShooterCharacter::OnAnyKeyPress); // Bind any key press to that function
}


// Executed on any key press (bound in SetupPlayerInputComponent)
void Ak3ShooterCharacter::OnAnyKeyPress(FKey key){

	if (TargetWord == "") GetNewTargetWord(); // If we don't have a word, get a new one. This should only happen the first time.

	//Check if we pressed a letter.
	FString n = key.GetFName().ToString().ToUpper();
	//GetFName returns the character we press, if pressing letters on keyboard. 
	//So here we can just check if we have that character, then check if it's a letter (between A (65) and Z (90)).
	if (n.Len() != 1 || ((unsigned int)(n[0]) < 65 || (unsigned int)(n[0]) > 90)) return; 

	Typed += n;

	if (Typed.Len() > CurrentWordLength) Typed = Typed.Mid(0, CurrentWordLength); // If what you typed is somehow above the length we want, trim it down
	if (Typed.Len() == CurrentWordLength){
		CompareAndGetScore(); // TODO : do something with the resulting score
		// GetNewTargetWord(); //TODO : Uncomment this (commented for debugging purposes)
	} 


	GEngine->AddOnScreenDebugMessage(0x3001, 15.0f, FColor::Red, FString::Printf(TEXT("Pressed %s, current word is %s, target is %s"), *n, *Typed, *TargetWord)); //DEBUG
}

// Get a random word to be the new target
void Ak3ShooterCharacter::GetNewTargetWord(){
	Uk3ShooterGameInstance* GI = Cast<Uk3ShooterGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())); 

	Typed = "";

	if (GI){
		TargetWord = GI->GetRandomWordOfLength(CurrentWordLength); // GameInstance has a function to do this. See k3Shooter/k3ShooterGameInstance.cpp
	} else TargetWord = "ERROR02";
}


// Compare the two words (target and typed) and calculate a score based on the numbers of correct letters.
float Ak3ShooterCharacter::CompareAndGetScore(){
	if (CurrentWordLength != TargetWord.Len() || TargetWord.Len() != Typed.Len()) return 0.0f; //If the words aren't the same length, calling this makes no sense.

	float score = 0.0f;

	for (int i = 0; i < CurrentWordLength; i++){
		if (TargetWord.Mid(i,1).Equals(Typed.Mid(i,1), ESearchCase::IgnoreCase)) score += 1.0f; //TODO?: Add modifiers here if needed.
	}

	GEngine->AddOnScreenDebugMessage(0x3002, 15.0f, FColor::Red, FString::Printf(TEXT("Score : %f"), score)); //DEBUG

	return score;
}