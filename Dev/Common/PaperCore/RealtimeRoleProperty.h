#pragma once
#include "CorePlatform/CorePlatform.h"
#include "Proto/Server/Logic/RoleProperty.pb.h"
#include "Proto/Server/Logic/Equip.pb.h"
#include "Proto/Server/Logic/Aura.pb.h"
#include "Proto/Server/Logic/ServerPlayer.pb.h"
#include "Proto/Server/Logic/Pet.pb.h"
#include "Proto/Server/Logic/Rune.pb.h"
#include "Proto/Server/Logic/Hero.pb.h"
#include "Proto/Server/Logic/RoleBuffer.pb.h"


#include "Config/EquipConfig.h"
#include "Config/RuneConfig.h"
#include "Config/PetConfig.h"
#include "Config/AuraConfig.h"
#include "Config/HeroConfig.h"
#include "Config/MonsterConfig.h"



#include "Core/Collection/Array.h"
#include "Core/Collection/List.h"
#include "Core/Collection/Dictionary.h"
#include "Core/Pattern/EnumPattern.h"
#include "Core/Pattern/FlagsPattern.h"

USING_MEDUSA;

STRONG_ENUM_12(RolePropertyType,Life,PhysicalAttack,PhysicalDefense,MagicalAttack,MagicalDefense,Critical,Toughness,Hit,Miss,AttackSpeed,Magic,MagicInit);
STRONG_FLAGS_7(RoleBufferState,Dizziness,Silence,Asshole,DamageReduction,Defense,Stealth,Blinding);

/************************************************************************/
/*
影响英雄属性的有：
装备+
符文+
天赋+
缘分,系统内先+后*
光环,系统内先+后*

关卡buffer*

其他Buffer,系统内先+后*
*/
/************************************************************************/



class RealtimeRoleProperty
{
public:
	const static RealtimeRoleProperty Zero;
	const static RealtimeRoleProperty One;

	typedef Array<float,RolePropertyType::Size> ArrayType;
	typedef List<float> ListType;
	typedef Dictionary<RolePropertyType,float> DictionaryType;
public:
	RealtimeRoleProperty(float life,float physicalAttack,float physicalDefense,float magicalAttack,float magicalDefense,float attackSpeed,float critical,float toughness,float hit,float miss,float magic,float magicInit,
		RoleBufferState bufferState,float physicalWeakFactor,float magicalWeakFactor,float allWeakFactor,float physicalSuckPercent, float magicalSuckPercent , float physicalReflectionDamage, float magicalReflectionDamage,float criticalDamagePercent ,ServerProto::Logic::RoleCareer career=(ServerProto::Logic::RoleCareer)0);
	RealtimeRoleProperty(const ArrayType& item,RoleBufferState bufferState=RoleBufferState::None,float physicalWeakFactor=0.f,float magicalWeakFactor=0.f,float allWeakFactor=0.f,float physicalSuckPercent=0.f, float magicalSuckPercent=0.f, float physicalReflectionDamage=0.f, float magicalReflectionDamage=0.f,float criticalDamagePercent=0.f,ServerProto::Logic::RoleCareer career=(ServerProto::Logic::RoleCareer)0);
	RealtimeRoleProperty(const ListType& item,RoleBufferState bufferState=RoleBufferState::None,float physicalWeakFactor=0.f,float magicalWeakFactor=0.f,float allWeakFactor=0.f,float physicalSuckPercent=0.f, float magicalSuckPercent=0.f, float physicalReflectionDamage=0.f, float magicalReflectionDamage=0.f,float criticalDamagePercent=0.f,ServerProto::Logic::RoleCareer career=(ServerProto::Logic::RoleCareer)0);
	RealtimeRoleProperty(const DictionaryType& item,RoleBufferState bufferState=RoleBufferState::None,float physicalWeakFactor=0.f,float magicalWeakFactor=0.f,float allWeakFactor=0.f,float physicalSuckPercent=0.f, float magicalSuckPercent=0.f, float physicalReflectionDamage=0.f, float magicalReflectionDamage=0.f,float criticalDamagePercent=0.f,ServerProto::Logic::RoleCareer career=(ServerProto::Logic::RoleCareer)0);
	RealtimeRoleProperty(const ServerProto::Logic::RoleProperty& base,RoleBufferState bufferState=RoleBufferState::None,float physicalWeakFactor=0.f,float magicalWeakFactor=0.f,float allWeakFactor=0.f,float physicalSuckPercent=0.f, float magicalSuckPercent=0.f, float physicalReflectionDamage=0.f, float magicalReflectionDamage=0.f,float criticalDamagePercent=0.f,ServerProto::Logic::RoleCareer career=(ServerProto::Logic::RoleCareer)0);
	RealtimeRoleProperty(const ServerProto::Logic::RoleBuffer& item,ServerProto::Logic::RoleCareer career=(ServerProto::Logic::RoleCareer)0);

	RealtimeRoleProperty();
	RealtimeRoleProperty(const RealtimeRoleProperty& val);
	RealtimeRoleProperty& operator=(const RealtimeRoleProperty& val);

public:
	static RealtimeRoleProperty ParseFromMonster(uint monsterId);
	static RealtimeRoleProperty ParseFromMonster(const ::ServerProto::Config::MonsterConfigItem& monster);

	static RealtimeRoleProperty ParseFrom(const ::ServerProto::Logic::ServerPlayer& serverPlayer,uint64 heroId);
	static RealtimeRoleProperty ParseFrom(const ::ServerProto::Logic::ServerPlayer& serverPlayer,const ServerProto::Logic::Hero& hero);
	static RealtimeRoleProperty ParseFromWithoutAura(const ::ServerProto::Logic::ServerPlayer& serverPlayer,const ServerProto::Logic::Hero& hero);

	static List<const ServerProto::Config::LoveConfigItem*> GetReachedLoves(const ::ServerProto::Logic::ServerPlayer& serverPlayer,const ServerProto::Logic::Hero& hero);

	static bool IsLoveReached( const ::ServerProto::Logic::ServerPlayer& serverPlayer, const ServerProto::Logic::Hero& hero,const ServerProto::Config::LoveConfigItem &loveConfig );
	static bool IsLoveFactorReached(const ServerProto::Logic::ServerPlayer& serverPlayer,const ServerProto::Logic::Hero& hero,::ServerProto::Logic::IdType targetType,uint targetId );

	static StringRef GetPropertyName(RolePropertyType type);
public:
	ArrayType ToArray()const;
	ListType ToList()const;
	DictionaryType ToDictionary()const;
	ListType ToListExcludeZero()const;
	DictionaryType ToDictionaryExcludeZero()const;

	void CopyTo(ArrayType& outArray)const;
	void CopyTo(ListType& outList)const;
	void CopyTo(DictionaryType& outDict)const;
	void CopyToExcludeZero(ListType& outList)const;
	void CopyToExcludeZero(DictionaryType& outDict)const;

	void PrintAll()const;
	void PrintExcludeZero()const;

public:
	const ServerProto::Logic::RoleProperty& GetProperty()const{ return mProperty; }

	RoleBufferState GetBufferState() const { return mBufferState; }
	float GetPhysicalWeakFactor() const { return mPhysicalWeakFactor; }
	float GetMagicalWeakFactor() const { return mMagicalWeakFactor; }
	float GetAllWeakFactor() const { return mAllWeakFactor; }
	float GetPhysicalSuckPercent() const { return mPhysicalSuckPercent; }
	float GetMagicalSuckPercent() const { return mMagicalSuckPercent; }
	float GetPhysicalReflectionDamage() const { return mPhysicalReflectionDamage; }
	float GetMagicalReflectionDamage() const { return mMagicalReflectionDamage; }
	float GetCriticalDamagePercent() const { return mCriticalDamagePercent; }
	const List<uint>& GetSkillList() const { return mEquipSkillIDs; };

	ServerProto::Logic::RoleCareer GetCareer() const { return mCareer; }
	void SetCareer(ServerProto::Logic::RoleCareer val) { mCareer = val; }
	bool HasCareer()const{return mCareer!=(ServerProto::Logic::RoleCareer)0;}
public:

	void Set(float life,float physicalAttack,float physicalDefense,float magicalAttack,float magicalDefense,float attackSpeed,float critical,float toughness,float hit,float miss,float magic,float magicInit,
		RoleBufferState bufferState,float physicalWeakFactor,float magicalWeakFactor,float allWeakFactor,float physicalSuckPercent, float magicalSuckPercent , float physicalReflectionDamage, float magicalReflectionDamage,float criticalDamagePercent ,ServerProto::Logic::RoleCareer career=(ServerProto::Logic::RoleCareer)0);

	void Set(const ArrayType& item,RoleBufferState bufferState=RoleBufferState::None,float physicalWeakFactor=0.f,float magicalWeakFactor=0.f,float allWeakFactor=0.f,float physicalSuckPercent=0.f, float magicalSuckPercent=0.f, float physicalReflectionDamage=0.f, float magicalReflectionDamage=0.f,float criticalDamagePercent=0.f,ServerProto::Logic::RoleCareer career=(ServerProto::Logic::RoleCareer)0);
	void Set(const ListType& item,RoleBufferState bufferState=RoleBufferState::None,float physicalWeakFactor=0.f,float magicalWeakFactor=0.f,float allWeakFactor=0.f,float physicalSuckPercent=0.f, float magicalSuckPercent=0.f, float physicalReflectionDamage=0.f, float magicalReflectionDamage=0.f,float criticalDamagePercent=0.f,ServerProto::Logic::RoleCareer career=(ServerProto::Logic::RoleCareer)0);
	void Set(const DictionaryType& item,RoleBufferState bufferState=RoleBufferState::None,float physicalWeakFactor=0.f,float magicalWeakFactor=0.f,float allWeakFactor=0.f,float physicalSuckPercent=0.f, float magicalSuckPercent=0.f, float physicalReflectionDamage=0.f, float magicalReflectionDamage=0.f,float criticalDamagePercent=0.f,ServerProto::Logic::RoleCareer career=(ServerProto::Logic::RoleCareer)0);
	void Set(const ServerProto::Logic::RoleProperty& base,RoleBufferState bufferState=RoleBufferState::None,float physicalWeakFactor=0.f,float magicalWeakFactor=0.f,float allWeakFactor=0.f,float physicalSuckPercent=0.f, float magicalSuckPercent=0.f, float physicalReflectionDamage=0.f, float magicalReflectionDamage=0.f,float criticalDamagePercent=0.f,ServerProto::Logic::RoleCareer career=(ServerProto::Logic::RoleCareer)0);


	void Set(const RealtimeRoleProperty& val);
	void SetSingle(RolePropertyType type,float val);

	void Add(const ServerProto::Logic::RoleProperty& base);
	void Add(const RealtimeRoleProperty& val);

	void Substract(const ServerProto::Logic::RoleProperty& base);
	void Substract(const RealtimeRoleProperty& val);

	void Multiply(const ServerProto::Logic::RoleProperty& buffer);
	void Multiply(const RealtimeRoleProperty& val);

	void Multiply(float factor);


	RealtimeRoleProperty& operator+=(const ServerProto::Logic::RoleProperty& val){Add(val);return *this;}
	RealtimeRoleProperty& operator-=(const ServerProto::Logic::RoleProperty& val){Substract(val);return *this;}
	RealtimeRoleProperty& operator*=(const ServerProto::Logic::RoleProperty& val){Multiply(val);return *this;}

	RealtimeRoleProperty& operator+=(const RealtimeRoleProperty& val){Add(val);return *this;}
	RealtimeRoleProperty& operator-=(const RealtimeRoleProperty& val){Substract(val);return *this;}
	RealtimeRoleProperty& operator*=(const RealtimeRoleProperty& val){Multiply(val);return *this;}


	RealtimeRoleProperty& operator*=(float factor){Multiply(factor);return *this;}
	RealtimeRoleProperty& operator/=(float factor){Multiply(1.f/factor);return *this;}


public:
	void AddEquipSkillID(uint skillID);
	
	void AddEquip(const ServerProto::Logic::Equip& equip);
	void AddEquips(const ::google::protobuf::RepeatedPtrField< ::ServerProto::Logic::Equip >& equips);

	void AddRune(const ServerProto::Logic::Rune& item);
	void AddRunes(const ::google::protobuf::RepeatedPtrField< ::ServerProto::Logic::Rune >& items);

	void MultiplyLove(const ServerProto::Config::LoveConfigItem& item);
	void MultiplyLoves(const List<const ServerProto::Config::LoveConfigItem*>& items);


	RealtimeRoleProperty MultiplyAura(const ServerProto::Logic::Aura& aura);
	void MultiplyAuras(const ::google::protobuf::RepeatedPtrField< ::ServerProto::Logic::Aura >& auras);

	void AddPet(const ServerProto::Logic::Pet& item,int forceIndex);
	void AddPets(const ::google::protobuf::RepeatedPtrField< ::ServerProto::Logic::Pet >& items,int forceIndex);
protected:
	ServerProto::Logic::RoleProperty mProperty;

	RoleBufferState mBufferState;	//角色战斗状态
	float mPhysicalWeakFactor;	//物理易伤
	float mMagicalWeakFactor;	//魔法易伤
	float mAllWeakFactor;	//全局易伤
	float mPhysicalSuckPercent;//物理吸血
	float mMagicalSuckPercent;//魔法吸血
	float mPhysicalReflectionDamage;//物理反伤
	float mMagicalReflectionDamage;//魔法反伤
	float mCriticalDamagePercent;//暴击伤害

	ServerProto::Logic::RoleCareer mCareer;	//0 means unknown career
	List<uint> mEquipSkillIDs;
	
};