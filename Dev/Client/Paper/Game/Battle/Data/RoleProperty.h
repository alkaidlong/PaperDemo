#pragma once
#include "CorePlatform/CorePlatform.h"
#include "Core/Collection/List.h"
#include "Proto/Server/Logic/BaseProperty.pb.h"
#include "Proto/Server/Config/RoleConfig.pb.h"
#include "Proto/Server/Config/BufferConfig.pb.h"

USING_MEDUSA;

class BufferProperty;
class RoleProperty
{
public:
	RoleProperty();
public:
	RoleProperty& operator=(const RoleProperty& val);
public:
	uint GetRoleLevel() const;
	const ServerProto::Logic::BaseProperty& GetCurProperty() const;
	const ServerProto::Config::RoleConfigItem* GetBaseProperty() const;
	const List<const BufferProperty*>& GetBuffers() const;
public:
	void AddBuffer(const BufferProperty* bufferProperty);
	void RemoveBuffer(const BufferProperty* bufferProperty);
	void SetBaseProperty(uint roleID,uint level);
	void UpdateResultProperty();
private:
	uint mRoleLevel;
	const ServerProto::Config::RoleConfigItem* mBaseProperty;
	ServerProto::Logic::BaseProperty mResultProperty;
	List<const BufferProperty*> mBuffers;
};