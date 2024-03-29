// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "S5_TestingGroundsHUD.generated.h"

UCLASS()
class AS5_TestingGroundsHUD : public AHUD
{
	GENERATED_BODY()

public:
	AS5_TestingGroundsHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

