#include "Game/Battle/Data/RoleProperty.h"
#include "Game/Calculation.h"
#include "Config/RoleConfig.h"
#include "Game/Battle/Data/BufferProperty.h"

RoleProperty::RoleProperty()
{
	mBaseProperty = NULL;
	mRoleLevel = 1;
}

RoleProperty& RoleProperty::operator=(const RoleProperty& val)
{
	mRoleLevel = val.mRoleLevel;
	mBaseProperty = val.mBaseProperty;
	mResultProperty = val.mResultProperty;
	mBuffers=val.mBuffers;
	return *this;
}

uint RoleProperty::GetRoleLevel() const
{
	return mRoleLevel;
}

const ServerProto::Logic::BaseProperty& RoleProperty::GetCurProperty() const
{
	return mResultProperty;
}

const ServerProto::Config::RoleConfigItem* RoleProperty::GetBaseProperty() const
{
	return mBaseProperty;
}

const List<const BufferProperty*>& RoleProperty::GetBuffers() const
{
	return mBuffers;
}

void RoleProperty::AddBuffer(const BufferProperty* bufferProperty)
{
	mBuffers.Add(bufferProperty);
	UpdateResultProperty();
}

void RoleProperty::RemoveBuffer(const BufferProperty* bufferProperty)
{
	mBuffers.Remove(bufferProperty);
	UpdateResultProperty();
}

void RoleProperty::SetBaseProperty(uint roleID,uint level)
{
	mRoleLevel = level;
	mBaseProperty = RoleConfig::Instance().GetRoleConfigItem(roleID);
	UpdateResultProperty();
}

void RoleProperty::UpdateResultProperty()
{
	ServerProto::Logic::BaseProperty outBaseProperty;
	Calculation::Instance().BasePropertyMultiplicationLevel(mBaseProperty->deltaproperty(),mRoleLevel, outBaseProperty);
	Calculation::Instance().BasePropertyPlusBaseProperty(outBaseProperty,mBaseProperty->property(),&mResultProperty);
	FOR_EACH_COLLECTION(i,mBuffers)
	{
		ServerProto::Logic::BaseProperty tmp = mResultProperty;
		const BufferProperty* buffer = *i;
		Calculation::Instance().BasePropertyPlusBaseProperty(tmp,buffer->GetCurProperty(),&mResultProperty);
	}
}
