#pragma once
#include "CorePlatform/CorePlatform.h"
#include "Proto/Server/Logic/BaseProperty.pb.h"
#include "Proto/Server/Config/BufferConfig.pb.h"

USING_MEDUSA;


class BufferProperty
{
public:
	BufferProperty();
public:
	BufferProperty& operator=(const BufferProperty& val);
public:
	uint GetBufferLevel() const;
	const ServerProto::Logic::BaseProperty& GetCurProperty() const;
	const ServerProto::Config::BufferConfigItem* GetBaseProperty() const;
public:
	void SetBaseProperty(uint bufferID,uint level);
	void UpdateResultProperty();
private:
	uint mBufferLevel;
	const ServerProto::Config::BufferConfigItem* mBaseProperty;
	ServerProto::Logic::BaseProperty mResultProperty;
};
