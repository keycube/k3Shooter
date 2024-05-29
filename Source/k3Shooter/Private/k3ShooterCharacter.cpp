// Fill out your copyright notice in the Description page of Project Settings.


#include "k3ShooterCharacter.h"
#include "k3ShooterEnemyBase.h"

// Sets default values
Ak3ShooterCharacter::Ak3ShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->Activate(true);


	//Bind overlap
	this->OnActorBeginOverlap.AddDynamic(this, &Ak3ShooterCharacter::OnOverlap);
    this->OnActorEndOverlap.AddDynamic(this, &Ak3ShooterCharacter::OnEndOverlap);

}

// Called when the game starts or when spawned
void Ak3ShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (TargetWord == "") GetNewTargetWord();
	Shop = Cast<Ak3ShooterShop>(UGameplayStatics::GetActorOfClass(GetWorld(), Ak3ShooterShop::StaticClass()));
}

// Called every frame
void Ak3ShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ShopRotationAlpha <= 1.0f){
		ShopRotationAlpha += DeltaTime;
		if (ShopRotationAlpha >= 1.0f) ShopRotationAlpha = 1.0f;
		Camera->SetWorldRotation(FRotator(FQuat::Slerp(ShopRotationStart.Quaternion(), ShopRotationEnd.Quaternion(), ShopRotationAlpha)));
	}
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

	
	FString n = key.GetFName().ToString().ToUpper();

	if (n == "ONE") { // DEBUG - TO REMOVE ONCE GYROSCOPE IMPLEMENTED
		ToggleShop();
		return;
	}

	//Check if we pressed a letter.
	//GetFName returns the character we press, if pressing letters on keyboard. 
	//So here we can just check if we have that character, then check if it's a letter (between A (65) and Z (90)).
	if (n.Len() != 1 || ((unsigned int)(n[0]) < 65 || (unsigned int)(n[0]) > 90)) return; 

	// Shop is handled differently than this.
	if (IsInShop) return ShopOnKeyPress(n[0]); 

	Typed += n;

	if (Typed.Len() > CurrentWordLength) Typed = Typed.Mid(0, CurrentWordLength); // If what you typed is somehow above the length we want, trim it down
	if (Typed.Len() == CurrentWordLength){
		CompareAndGetScore(); // TODO : do something with the resulting score
		GetNewTargetWord();
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
		if (TargetWord.Mid(i,1).Equals(Typed.Mid(i,1), ESearchCase::IgnoreCase)){
			// Score Calculation
			score += DamagePerLetter;
		} 
	}

	GEngine->AddOnScreenDebugMessage(0x3002, 15.0f, FColor::Red, FString::Printf(TEXT("Score : %f"), score)); //DEBUG

	return score;
}


// FIXME: There is apparently a crash in this function. I don't see it, but unreal does sometimes. 
FString Ak3ShooterCharacter::GetCurrentWordProgress(){
	if (TargetWord=="") return FString(TEXT("ERROR04"));
	FString s = "";
	for (int i = 0; i < Typed.Len(); i++){
		if (TargetWord.Mid(i,1).Equals(Typed.Mid(i,1), ESearchCase::IgnoreCase)){
			s += "<Correct>"+TargetWord.Mid(i,1)+"</>";
		} else s += "<Wrong>"+TargetWord.Mid(i,1)+"</>";
	}
	s += TargetWord.Mid(Typed.Len());
	return s;
}

void Ak3ShooterCharacter::ResetDefaultValues(){
	CurrentWordLength = 3;
	Typed = "";
	TargetWord = "";
	Health = 100;
	Money = 0.0f;
	MoneyGain = 1.0f;
	DamagePerLetter = 1.0f;
	IsInShop = false;
	// Add other variables here if any
}

void Ak3ShooterCharacter::Hurt(float DamageTaken){
	Health -= (int)DamageTaken; //Always round down damage taken.
								//Add some other parameters here if needed.
	if (Health <= 0) {
		// Death. todo
	}
}

void Ak3ShooterCharacter::OnOverlap(AActor* MyActor, AActor* OtherActor){
	if (Ak3ShooterEnemyBase* enemy = Cast<Ak3ShooterEnemyBase>(OtherActor); enemy){
		Hurt(enemy->CurrentHealth * enemy->DamageMultiplier);
		enemy->Destroy(); // only destroy, we don't kill so we don't get money
	}
}

void Ak3ShooterCharacter::OnEndOverlap(AActor* MyActor, AActor* OtherActor){

}

/**
 * SHOP
 */


void Ak3ShooterCharacter::ToggleShop(){
	IsInShop = !IsInShop;
	ShopRotationStart = FRotator::MakeFromEuler(FVector(0,0,IsInShop?0:180)); //
	ShopRotationEnd = FRotator::MakeFromEuler(FVector(0,0,IsInShop?180:0));   // shop location is at 180 - but remember, we toggle IsInShop before!
	ShopRotationAlpha = ShopRotationAlpha<1.0f?1.0f-ShopRotationAlpha:0.0f;
	if (IsInShop && Shop) Shop->Typed = ""; // reset typed when entering shop. do we do the same when exiting? idk.
}

void Ak3ShooterCharacter::ShopOnKeyPress(TCHAR n){
	if (Shop) Shop->OnKeyPress(n);
}