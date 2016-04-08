#include "Game/Battle/Data/BufferProperty.h"
#include "Game/Calculation.h"
#include "Config/BufferConfig.h"

BufferProperty::BufferProperty()
{
	mBufferLevel = 1;
	mBaseProperty = NULL;
}

BufferProperty& BufferProperty::operator=(const BufferProperty& val)
{
	this->mBufferLevel = val.mBufferLevel;
	this->mBaseProperty = val.mBaseProperty;
	this->mResultProperty = val.mResultProperty;
	return *this;
}

uint BufferProperty::GetBufferLevel() const
{
	return mBufferLevel;
}

const ServerProto::Logic::BaseProperty& BufferProperty::GetCurProperty() const
{
	return mResultProperty;
}

const ServerProto::Config::BufferConfigItem* BufferProperty::GetBaseProperty() const
{
	return mBaseProperty;
}

void BufferProperty::SetBaseProperty(uint bufferID,uint level)
{
	mBufferLevel = level;
	mBaseProperty = BufferConfig::Instance().GetBufferConfigItem(bufferID);
	UpdateResultProperty();
}

void BufferProperty::UpdateResultProperty()
{
	ServerProto::Logic::BaseProperty outBaseProperty;
	Calculation::Instance().BasePropertyMultiplicationLevel(mBaseProperty->deltaproperty(),mBufferLevel, outBaseProperty);
	Calculation::Instance().BasePropertyPlusBaseProperty(outBaseProperty,mBaseProperty->property(),&mResultProperty);
}
