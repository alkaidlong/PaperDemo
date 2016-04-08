#pragma once
#include "CorePlatform/CorePlatform.h"
#include "Proto/Server/Logic/BaseProperty.pb.h"
#include "Proto/Server/Config/SkillConfig.pb.h"

USING_MEDUSA;


class SkillProperty
{
public:
	SkillProperty();
public:
	SkillProperty& operator=(const SkillProperty& val);
public:
	uint GetSkillLevel() const;
	const ServerProto::Logic::BaseProperty& GetCurProperty() const;
	const ServerProto::Config::SkillConfigItem* GetBaseProperty() const;
public:
	void SetBaseProperty(uint skillID,uint level);
	void UpdateResultProperty();
private:
	uint mSkillLevel;
	const ServerProto::Config::SkillConfigItem* mBaseProperty;
	ServerProto::Logic::BaseProperty mResultProperty;
};