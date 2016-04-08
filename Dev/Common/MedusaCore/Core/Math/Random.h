#pragma once
#include "MedusaCorePreCompiled.h"

MEDUSA_BEGIN;

class Random
{
public:
	Random(uint32 seed=0){if(seed==0){StaticSrand();}else{srand(seed);}}
	~Random(void);
public:
	int Next()const{return rand();}
	int Next(int min,int max)const{return min+rand()%(max-min+1);}
	int Next(int max)const{return rand()%(max+1);}
	float NextFloat()const{return (float)rand()/RAND_MAX;}
	byte NextByte()const{return (byte)(rand()%256);}
	bool NextBool()const{return rand()%2==0;}
	bool NextBool(float prob)const{return (float)rand()<=prob*RAND_MAX;}
	void NextBytes(MemoryByteData& outData)const;
public:
	static void StaticSrand(){srand((uint32)Platform::GetTicks());}
	static void StaticSrandSeed(uint32 seed){srand(seed);}
	static int StaticNext(){StaticSrand();return rand();}
	static int StaticNext(int min,int max){StaticSrand();return min+rand()%(max-min+1);}
	static int StaticNext(int max){StaticSrand();return rand()%(max+1);}
	static float StaticNextFloat(){StaticSrand();return (float)rand()/RAND_MAX;}
	static byte StaticNextByte(){StaticSrand();return (byte)(rand()%256);}
	static bool StaticNextBool(){StaticSrand();return rand()%2==0;}
	static bool StaticNextBool(float prob){StaticSrand();return (float)rand()<=prob*RAND_MAX;}
	static void StaticNextBytes(MemoryByteData& outData);

	static int StaticNextWithoutSeed(){return rand();}
	static int StaticNextWithoutSeed(int min,int max){return min+rand()%(max-min+1);}
	static int StaticNextWithoutSeed(int max){return rand()%(max+1);}
	static float StaticNextFloatWithoutSeed(){return (float)rand()/RAND_MAX;}
	static byte StaticNextByteWithoutSeed(){return (byte)(rand()%256);}
	static bool StaticNextBoolWithoutSeed(){return rand()%2==0;}
	static bool StaticNextBoolWithoutSeed(float prob){return (float)rand()<=prob*RAND_MAX;}
	static void StaticNextBytesWithoutSeed(MemoryByteData& outData);
};

MEDUSA_END;
