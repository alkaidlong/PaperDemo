#pragma once
#include "Proto/Server/Logic/BaseProperty.pb.h"
#include "Core/Pattern/Singleton.h"

USING_MEDUSA;

class Calculation:public Pattern::Singleton<Calculation>
{
	friend class Pattern::Singleton<Calculation>;
private:
	Calculation(void);
	~Calculation(void){}
public:
	bool Initialize();
	bool Uninitialize();
public:
	void BasePropertyPlusBaseProperty(const ServerProto::Logic::BaseProperty& p1,const ServerProto::Logic::BaseProperty& p2,ServerProto::Logic::BaseProperty* result) const;
	void BasePropertyMultiplicationBaseProperty(const ServerProto::Logic::BaseProperty& p1,const ServerProto::Logic::BaseProperty& p2,ServerProto::Logic::BaseProperty& result) const;
	void BasePropertyMultiplicationLevel(const ServerProto::Logic::BaseProperty& prop,uint level,ServerProto::Logic::BaseProperty& result) const;

	void CommonPropertyPlusCommonProperty(const ServerProto::Logic::CommonProperty& p1,const ServerProto::Logic::CommonProperty& p2,::ServerProto::Logic::CommonProperty* result) const;
	void CommonPropertyMultiplicationCommonProperty(const ServerProto::Logic::CommonProperty& p1,const ServerProto::Logic::CommonProperty& p2,::ServerProto::Logic::CommonProperty* result) const;
	void CommonPropertyMultiplicationLevel(const ServerProto::Logic::CommonProperty& prop,uint level,::ServerProto::Logic::CommonProperty* result) const;
};

