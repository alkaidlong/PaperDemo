#include "Game/Calculation.h"

Calculation::Calculation(void)
{

}

bool Calculation::Initialize()
{
	return true;
}

bool Calculation::Uninitialize()
{
	return true;
}

void Calculation::BasePropertyPlusBaseProperty(const ServerProto::Logic::BaseProperty& p1,const ServerProto::Logic::BaseProperty& p2,ServerProto::Logic::BaseProperty* result) const
{
	result->set_coolingreduction(p1.coolingreduction() + p2.coolingreduction());
	result->set_attackspeed(p1.attackspeed() + p2.attackspeed());
	result->set_movespeed(p1.movespeed() + p2.movespeed());
	CommonPropertyPlusCommonProperty(p1.physicalproperty(), p2.physicalproperty(), result->mutable_physicalproperty());
	CommonPropertyPlusCommonProperty(p1.magicalproperty(), p2.magicalproperty(), result->mutable_magicalproperty());
}

void Calculation::BasePropertyMultiplicationBaseProperty(const ServerProto::Logic::BaseProperty& p1,const ServerProto::Logic::BaseProperty& p2,ServerProto::Logic::BaseProperty& result) const
{
	result.set_coolingreduction(p1.coolingreduction() * p2.coolingreduction());
	result.set_attackspeed(p1.attackspeed() * p2.attackspeed());
	result.set_movespeed(p1.movespeed() * p2.movespeed());
	CommonPropertyMultiplicationCommonProperty(p1.physicalproperty(), p2.physicalproperty(), result.mutable_physicalproperty());
	CommonPropertyMultiplicationCommonProperty(p1.magicalproperty(), p2.magicalproperty(), result.mutable_magicalproperty());
}

void Calculation::BasePropertyMultiplicationLevel(const ServerProto::Logic::BaseProperty& prop,uint level,ServerProto::Logic::BaseProperty& result) const
{
	result.set_coolingreduction(prop.coolingreduction() * level);
	result.set_attackspeed(prop.attackspeed() * level);
	result.set_movespeed(prop.movespeed() * level);
	CommonPropertyMultiplicationLevel(prop.physicalproperty(), level, result.mutable_physicalproperty());
	CommonPropertyMultiplicationLevel(prop.magicalproperty(), level, result.mutable_magicalproperty());
}

void Calculation::CommonPropertyPlusCommonProperty(const ServerProto::Logic::CommonProperty& p1,const ServerProto::Logic::CommonProperty& p2,::ServerProto::Logic::CommonProperty* result) const
{
	result->set_maxvalue(p1.maxvalue() + p2.maxvalue());
	result->set_valueregeneration(p1.valueregeneration() + p2.valueregeneration());
	result->set_attack(p1.attack() + p2.attack());
	result->set_defense(p1.defense() + p2.defense());
	result->set_defensepenetration(p1.defensepenetration() + p2.defensepenetration());
	result->set_lifesteal(p1.lifesteal() + p2.lifesteal());
	result->set_critical(p1.critical() + p2.critical());
	result->set_criticaldamage(p1.criticaldamage() + p2.criticaldamage());
	result->set_toughness(p1.toughness() + p2.toughness());
}

void Calculation::CommonPropertyMultiplicationCommonProperty(const ServerProto::Logic::CommonProperty& p1,const ServerProto::Logic::CommonProperty& p2,::ServerProto::Logic::CommonProperty* result) const
{
	result->set_maxvalue(p1.maxvalue() * p2.maxvalue());
	result->set_valueregeneration(p1.valueregeneration() * p2.valueregeneration());
	result->set_attack(p1.attack() * p2.attack());
	result->set_defense(p1.defense() * p2.defense());
	result->set_defensepenetration(p1.defensepenetration() * p2.defensepenetration());
	result->set_lifesteal(p1.lifesteal() * p2.lifesteal());
	result->set_critical(p1.critical() * p2.critical());
	result->set_criticaldamage(p1.criticaldamage() * p2.criticaldamage());
	result->set_toughness(p1.toughness() * p2.toughness());
}

void Calculation::CommonPropertyMultiplicationLevel(const ServerProto::Logic::CommonProperty& prop,uint level,::ServerProto::Logic::CommonProperty* result) const
{
	result->set_maxvalue(prop.maxvalue() * level);
	result->set_valueregeneration(prop.valueregeneration() * level);
	result->set_attack(prop.attack() * level);
	result->set_defense(prop.defense() * level);
	result->set_defensepenetration(prop.defensepenetration() * level);
	result->set_lifesteal(prop.lifesteal() * level);
	result->set_critical(prop.critical() * level);
	result->set_criticaldamage(prop.criticaldamage() * level);
	result->set_toughness(prop.toughness() * level);
}

