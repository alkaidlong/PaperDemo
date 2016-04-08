#include "Game/Battle/Data/SkillProperty.h"
#include "Game/Calculation.h"
#include "Config/SkillConfig.h"


SkillProperty::SkillProperty()
{
	mSkillLevel = 1;
	mBaseProperty = NULL;
}

SkillProperty& SkillProperty::operator=(const SkillProperty& val)
{
	mSkillLevel = val.mSkillLevel;
	mBaseProperty = val.mBaseProperty;
	mResultProperty = val.mResultProperty;
	return *this;
}

uint SkillProperty::GetSkillLevel() const
{
	return mSkillLevel;
}

const ServerProto::Logic::BaseProperty& SkillProperty::GetCurProperty() const
{
	return mResultProperty;
}

const ServerProto::Config::SkillConfigItem* SkillProperty::GetBaseProperty() const
{
	return mBaseProperty;
}

void SkillProperty::SetBaseProperty(uint skillID,uint level)
{
	mSkillLevel = level;
	mBaseProperty = SkillConfig::Instance().GetSkillConfigItem(skillID);
	UpdateResultProperty();
}

void SkillProperty::UpdateResultProperty()
{
	::ServerProto::Logic::CommonProperty outPhyProperty;
	Calculation::Instance().CommonPropertyMultiplicationLevel(mBaseProperty->deltaphysicalproperty(),mSkillLevel,&outPhyProperty);
	Calculation::Instance().CommonPropertyPlusCommonProperty(outPhyProperty, mBaseProperty->physicalproperty(),mResultProperty.mutable_physicalproperty());

	::ServerProto::Logic::CommonProperty outMagicProperty;
	Calculation::Instance().CommonPropertyMultiplicationLevel(mBaseProperty->deltamagicalproperty(),mSkillLevel,&outMagicProperty);
	Calculation::Instance().CommonPropertyPlusCommonProperty(outMagicProperty, mBaseProperty->magicalproperty(),mResultProperty.mutable_magicalproperty());

	::ServerProto::Logic::CommonProperty outHolyPyhProperty;
	::ServerProto::Logic::CommonProperty outHolyMagProperty;
	::ServerProto::Logic::CommonProperty outDelatProperty;
	Calculation::Instance().CommonPropertyMultiplicationLevel(mBaseProperty->deltaholyphysicaldamage(),mSkillLevel,&outHolyPyhProperty);
	Calculation::Instance().CommonPropertyMultiplicationLevel(mBaseProperty->deltaholymagicaldamage(),mSkillLevel,&outHolyMagProperty);
	Calculation::Instance().CommonPropertyPlusCommonProperty(outHolyPyhProperty, outHolyMagProperty,&outDelatProperty);
	Calculation::Instance().CommonPropertyPlusCommonProperty(outDelatProperty, mBaseProperty->magicalproperty(),mResultProperty.mutable_magicalproperty());


}