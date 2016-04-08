#pragma once
#include "MedusaCorePreDeclares.h"
#include "IScrollMathModel.h"

MEDUSA_BEGIN;

class SpringScrollMathModel:public IScrollMathModel
{
public:
	SpringScrollMathModel(DirectionMask direction=DirectionMask::All);
	virtual ~SpringScrollMathModel(void);

public:
	virtual bool Update(float dt);
protected:
	virtual void OnUpdateSpringLimit();
	virtual Point2F CalculateSpringAccelerate()const;
	virtual Point2F CalculateScrollAccelerate()const;

protected:
	//spring effect
	Point2F mSpringSizePercent;	//

	float mSpringFactor;

	float mDampingStartFactor;
	float mDampingFactor;
};

MEDUSA_END;
