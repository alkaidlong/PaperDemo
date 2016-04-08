#include "MedusaCorePreCompiled.h"
#include "Core/Utility/Utility.h"
#include "Core/Math/MathHeader.h"

MEDUSA_BEGIN;


bool Utility::IsLittleEndian()
{
	static bool isLittleEndian;
	static bool isInit = false;

	if(!isInit)
	{
		short word = 0x0001;
		char *byte = (char*) &word;
		isLittleEndian = byte[0] ? true : false;
		isInit = true;
	}

	return isLittleEndian;
}

/*
	volatile float x=1.f;
	volatile float y=0.f;
	x=x/y;

	EM_ZERODIVIDE: /0.f error
	EM_OVERFLOW: overflow error
	EM_INVALID: exception
	*/
void Utility::EnableFloatPointException( bool isEnable )
{
#ifdef MEDUSA_WINDOWS
	uint32 currentState;
	uint32 newState;
	//get current state
	_controlfp_s(&currentState,0,0);
	newState=currentState;
	if (isEnable)
	{
		newState&=~(EM_ZERODIVIDE|EM_OVERFLOW|EM_INVALID);
	}
	else
	{
		newState|=(EM_ZERODIVIDE|EM_OVERFLOW|EM_INVALID);
	}

	_controlfp_s(&currentState,newState,MCW_EM);
#else
    
#endif
}

uint32 Utility::SwapUInt32( uint32 val )
{
	return ((val&0x000000FF)<<24) + ((val&0x0000FF00)<<8) + ((val&0x00FF0000)>>8) + ((val&0xFF000000) >> 24);
}

uint64 Utility::SwapUInt64( uint64 val )
{
	unsigned char* bytes=(unsigned char*)&val;

	Math::Swap(bytes[0],bytes[7]);
	Math::Swap(bytes[1],bytes[6]);
	Math::Swap(bytes[2],bytes[5]);
	Math::Swap(bytes[3],bytes[4]);
	return val;
}

void Utility::SwapBytes( unsigned char* data,size_t size )
{
	size_t i = 0, j = size - 1;
	while(i < j)
	{
		Math::Swap(data[i++],data[j--]);
	}
}

bool Utility::HasBit( size_t val,byte index )
{
	return (val&((intp)1<<index))!=0;
}


MEDUSA_END;