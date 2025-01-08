// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogTestPlay, Log, All);

UCLASS()
class SPARTA_API ATestActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/**
	 * x, y 각각 이동할 거리를 결정하는 함수
	 * 0 또는 1을 무작위로 반환
	 */
	UFUNCTION(BlueprintCallable)
	int32 Step();
	
	void DebugDrawMove(const FVector2D& PrevPosition);

	/**
	 * (0,0)에서 시작하여 총 StepCount회 이동하고
	 * 이동 좌표, 이동 거리, 이벤트 발생 여부 등을 UE_LOG로 출력
	 */
	UFUNCTION(BlueprintCallable)
	void MoveCharacter();

	/*
	 * 두 백터 사이의 이동거리를 계산해서 반환합니다.
	 */
	// UFUNCTION(BlueprintPure)
	// float Distance(FVector2D first, FVector2D second);

public:
	/** 현재 좌표 (시작점 (0,0)) */
	UPROPERTY(BlueprintReadOnly,Category="Test")
	FVector2D CurrentPosition = FVector2D::ZeroVector;

	/** 총 이동 거리 */
	UPROPERTY(BlueprintReadOnly,Category="Test")
	float TotalDistance = 0;

	/** 이벤트 발생 횟수 */
	UPROPERTY(BlueprintReadOnly,Category="Test")
	int32 EventCount = 0;

	/** 이동 횟수 (기본 10) */
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Test|Movement")
	int32 StepCount = 0;
};
