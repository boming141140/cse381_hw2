// Fill out your copyright notice in the Description page of Project Settings.


#include "BallGameMode.h"
#include "BallSpawner.h"

ABallGameMode::ABallGameMode()
{
    BallSpawnerInstance = CreateDefaultSubobject<UBallSpawner>(TEXT("BallSpawnerInstance"));
 
}

void ABallGameMode::BeginPlay()
{
    Super::BeginPlay();

}

