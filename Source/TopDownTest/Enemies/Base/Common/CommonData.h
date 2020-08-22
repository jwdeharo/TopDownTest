#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CommonData.generated.h"

/**
* Enum that identifies where the attack come from.
*/
UENUM()
namespace EPartAttack
{
	enum Type
	{
		LeftArm, //!< From left arm.
		RightArm, //!< From right arm.
		BothArms	//!< From both arms.
	};
}