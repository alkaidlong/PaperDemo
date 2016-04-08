#include "MedusaCorePreCompiled.h"

#include "Core/Math/MathStrategy.h"
#include "Core/System/Environment.h"

/*
#ifdef __APPLE__
#if (TARGET_IPHONE_SIMULATOR == 0) && (TARGET_OS_IPHONE == 1)
#ifdef _ARM_ARCH_7
#include "neonmath/neon_matrix_impl.h"
#else
#include "vfpmath/matrix_impl.h"
#endif
#endif
#else
#endif
*/

MEDUSA_BEGIN;

MathStrategy::MathStrategy(void)
{
	mIsSupportNeon=Environment::Instance().IsArmV7();
	mIsSupportVFP=Environment::Instance().IsArmV6();
}


MathStrategy::~MathStrategy(void)
{
}

MEDUSA_END;
