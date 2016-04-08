#include "Game/Battle/Logic/Role.h"
#include "Game/PaperScript.h"

Role::Role(uint id)
{
	PaperScript::Instance().LoadRoleScript(id);
	mScript = PaperScript::Instance().NewRoleScriptObject(id);
	mScript->SetMemberValue("ScriptAdd",(int)mScript);
	mScript->SetMemberValue("CppAdd",(int)this);
	uint propertyID = mScript->GetMemberValue<uint>("PropertyID");
	uint propertyLevel = mScript->GetMemberValueOrDefault<uint>("PropertyLevel",1);
	mProperty.SetBaseProperty(propertyID,propertyLevel);
}

Role::~Role(void)
{
	SAFE_DELETE(mScript);
}

void Role::LoadResource()
{
	mScript->Invoke("LoadResource");
}

void Role::Initialize()
{
	mScript->Invoke("Initialize");
}

void Role::Uninitialize()
{
	mScript->Invoke("Uninitialize");
}

// void Role::Update(float dt)
// {
// 	mScript->Invoke("Update",dt);
// }

void Role::SetPause(bool isPause)
{
	mScript->Invoke("SetPause",isPause);
}

void Role::IntoBattle()
{
	mScript->Invoke("IntoBattle");
}

void Role::OutBattle()
{
	mScript->Invoke("OutBattle");
}

float Role::GetRoleProperty(BasePropertyType type)
{
	switch (type)
	{
	case BasePropertyType::HP:
		return mProperty.GetCurProperty().physicalproperty().maxvalue();
	case BasePropertyType::HpRegeneration:
		return mProperty.GetCurProperty().physicalproperty().valueregeneration();
	case BasePropertyType::PhysicalAttack:
		return mProperty.GetCurProperty().physicalproperty().attack();
	case BasePropertyType::PhysicalDefense:
		return mProperty.GetCurProperty().physicalproperty().defense();
	case BasePropertyType::PhysicalDefensePenetration:
		return mProperty.GetCurProperty().physicalproperty().defensepenetration();
	case BasePropertyType::PhysicalLifeSteal:
		return mProperty.GetCurProperty().physicalproperty().lifesteal();
	case BasePropertyType::PhysicalCritical:
		return mProperty.GetCurProperty().physicalproperty().critical();
	case BasePropertyType::PhysicalCriticalDamage:
		return mProperty.GetCurProperty().physicalproperty().criticaldamage();
	case BasePropertyType::PhysicalToughness:
		return mProperty.GetCurProperty().physicalproperty().toughness();
	case BasePropertyType::MP:
		return mProperty.GetCurProperty().magicalproperty().maxvalue();
	case BasePropertyType::MPRegeneration:
		return mProperty.GetCurProperty().magicalproperty().valueregeneration();
	case BasePropertyType::MagicalAttack:
		return mProperty.GetCurProperty().magicalproperty().attack();
	case BasePropertyType::MagicalDefense:
		return mProperty.GetCurProperty().magicalproperty().defense();
	case BasePropertyType::MagicalDefensePenetration:
		return mProperty.GetCurProperty().magicalproperty().defensepenetration();
	case BasePropertyType::MagicalLifeSteal:
		return mProperty.GetCurProperty().magicalproperty().lifesteal();
	case BasePropertyType::MagicalCritical:
		return mProperty.GetCurProperty().magicalproperty().critical();
	case BasePropertyType::MagicalCriticalDamage:
		return mProperty.GetCurProperty().magicalproperty().criticaldamage();
	case BasePropertyType::MagicalToughness:
		return mProperty.GetCurProperty().magicalproperty().toughness();
	case BasePropertyType::CoolingReduction:
		return mProperty.GetCurProperty().coolingreduction();
	case BasePropertyType::AttackSpeed:
		return mProperty.GetCurProperty().attackspeed();
	case BasePropertyType::MoveSpeed:
		return mProperty.GetCurProperty().movespeed();
	default:
		Log::AssertFailedFormat("No property %d",type);
		return 0.0f;
	}
		
}
