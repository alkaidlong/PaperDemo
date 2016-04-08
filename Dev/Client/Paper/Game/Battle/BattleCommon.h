#pragma once

enum class RoleType
{
	Player,//�ɲ��������
	NPC,//���ɲ��������
	Monster,//����
	Boss//��
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