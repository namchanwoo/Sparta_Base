// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

DEFINE_LOG_CATEGORY(LogTestPlay);

// Sets default values
ATestActor::ATestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTestPlay, Warning, TEXT("==== TestActor BeginPlay() ===="));

	// 10회 이동 테스트 진행
	MoveCharacter();

	// 총 이동 결과 요약
	UE_LOG(LogTestPlay, Warning, TEXT("총 이동 거리: %f"), TotalDistance);
	UE_LOG(LogTestPlay, Warning, TEXT("발생한 총 이벤트 수: %d"), EventCount);
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

int32 ATestActor::Step()
{
	// 0 또는 1을 랜덤으로 반환
	return FMath::RandRange(0, 1);
}

void ATestActor::DebugDrawMove(const FVector2D& PrevPosition)
{
	// 현재 액터의 월드 위치를 가져옴
	FVector ActorLocation = GetActorLocation();

	float DebugScale = 50.f;
	// 액터 기준의 2D 좌표(PrevPosition, CurrentPosition)를  월드 좌표로 변환(Z축은 0.0f 가정)
	FVector Start3D = ActorLocation + FVector(PrevPosition.X * DebugScale, PrevPosition.Y * DebugScale, 0.0f);
	FVector End3D = ActorLocation + FVector(CurrentPosition.X * DebugScale, CurrentPosition.Y * DebugScale, 0.0f);


	// 이전 위치 → 현재 위치를 그리는 디버그 라인
	DrawDebugLine(
		GetWorld(),
		Start3D,
		End3D,
		FColor::Green,
		false, // 영구 표시 여부(false: 일정 시간 후 사라짐)
		50.0f, // 표시 시간(초)
		5, // DepthPriority(기본값 0보다 높게 설정해도 무방)
		10.0f // 선 두께
	);

	// 4) 새로운 위치에 작은 스피어(구체) 그리기
	DrawDebugSphere(
		GetWorld(),
		End3D,
		12.0f, // 반지름
		16, // 세그먼트(둥글기 정도)
		FColor::Yellow,
		false, // 영구 표시 여부
		50.0f // 표시 시간(초)
	);
}

void ATestActor::MoveCharacter()
{
	UE_LOG(LogTestPlay, Warning, TEXT("이동 시작 위치 (%f, %f)"), CurrentPosition.X, CurrentPosition.Y);

	for (int32 i = 0; i < StepCount; i++)
	{
		// 이전 좌표 저장
		FVector2D PrevPosition = CurrentPosition;

		// x, y 각각 이동할 값을 랜덤으로 얻어서 좌표 갱신
		int32 XStep = Step();
		int32 YStep = Step();
		CurrentPosition.X += XStep;
		CurrentPosition.Y += YStep;

		// 이번 스텝의 이동 거리 계산
		float StepDistance = (CurrentPosition - PrevPosition).Size();
		TotalDistance += StepDistance;

		// 좌표 이동 로그 출력
		UE_LOG(LogTestPlay, Warning, TEXT("%d단계: (%f, %f)에서 (%f, %f)로 이동되었습니다. 걸음 거리: %f"),
		       i + 1,
		       PrevPosition.X, PrevPosition.Y,
		       CurrentPosition.X, CurrentPosition.Y,
		       StepDistance
		);

		//디버그 드로잉 부분	
		DebugDrawMove(PrevPosition);


		// 50% 확률로 이벤트 발생 여부 결정
		float RandomEventValue = FMath::FRand(); // [0,1) 범위
		if (RandomEventValue < 0.5f)
		{
			EventCount++;
			UE_LOG(LogTestPlay, Warning, TEXT("%d단계: 이벤트가 발생했습니다.!"), i + 1);
		}
		else
		{
			UE_LOG(LogTestPlay, Warning, TEXT("%d단계: 이벤트가 발생하지 않았습니다."), i + 1);
		}
	}
}


#pragma region Sample Code

// void ATestActor::TriggerEventWithProbability(float Probability)
// {
// 	int32 RandomValue = FMath::RandRange(1, 100); // 1 ~ 100의 난수 생성
// 	if (RandomValue <= Probability)
// 	{
// 		UE_LOG(LogTestPlay, Log, TEXT("Event Triggered!"));
// 	}
// 	else
// 	{
// 		UE_LOG(LogTestPlay, Log, TEXT("Event Not Triggered"));
// 	}
// }

// void ATestActor::PrintFVector2DArray()
// {
// 	// FVector2D 배열 생성
// 	TArray<FVector2D> VectorArray;
//
// 	// 데이터 추가
// 	for (int32 i = 0; i < 10; i++)
// 	{
// 		VectorArray.Add(FVector2D(i * 10.0f, i * 20.0f)); // X, Y 값을 임의로 설정
// 	}
//
// 	// 데이터 출력
// 	for (int32 i = 0; i < VectorArray.Num(); i++)
// 	{
// 		const FVector2D& Vec = VectorArray[i];
// 		UE_LOG(LogTestPlay, Warning, TEXT("Vector %d: X = %f, Y = %f"), i, Vec.X, Vec.Y);
// 	}
// }

// float ATestActor::Distance(FVector2D first, FVector2D second)
// {
// 	float dx = first.X - second.X;
// 	float dy = first.Y - second.Y;
// 	return FMath::Sqrt(dx * dx + dy * dy);
// }

#pragma endregion
