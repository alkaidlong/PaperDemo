#pragma once

enum class RoleType
{
	Player,//可操作的玩家
	NPC,//不可操作的玩家
	Monster,//怪物
	Boss//王
};

enum class BasePropertyType
{
	HP,
	HpRegeneration,
	PhysicalAttack,
	PhysicalDefense,
	PhysicalDefensePenetration,
	PhysicalLifeSteal,
	PhysicalCritical,
	PhysicalCriticalDamage,
	PhysicalToughness,
	MP,
	MPRegeneration,
	MagicalAttack,
	MagicalDefense,
	MagicalDefensePenetration,
	MagicalLifeSteal,
	MagicalCritical,
	MagicalCriticalDamage,
	MagicalToughness,
	CoolingReduction,
	AttackSpeed,
	MoveSpeed
};