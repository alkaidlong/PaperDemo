#pragma once

#include "MedusaCorePreCompiled.h"
#include "Core/Assertion/CommonAssert.h"



MEDUSA_BEGIN;

//should be column major order to fit OpenGL

/*
if compiled using ARMv6, then use vfp
	if compiled using ARMv7, then use Neon.

		If you are shipping fat binaries (ARMv6 + ARMv7), then it will use vfp in iPhone 1st and 2nd gen, and Neon on iPad, iPhone 3rd and 4th gen.

*/


class MathStrategy
{
public:
	static MathStrategy& Instance()
	{
		static MathStrategy strategy;
		return strategy;
	}
private:
	MathStrategy(void);
	~MathStrategy(void);

private:
	bool mIsSupportNeon;
	bool mIsSupportVFP;
};

MEDUSA_END;
