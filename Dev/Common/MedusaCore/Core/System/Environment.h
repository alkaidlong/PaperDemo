#pragma once
#include "MedusaCorePreCompiled.h"
#include "Core/String/StringRef.h"
#include "Core/String/HeapString.h"
#include "Core/String/StackString.h"
#include "Core/Pattern/Singleton.h"
#include "Core/System/EnvironmentTag.h"
#include "Core/Proto/Client/EnvironmentTag.pb.h"

MEDUSA_BEGIN;


namespace DeviceType
{
	enum DeviceType_t
	{
		Unknown,

		Simulator,
		iPhoneSimulator, // both regular and iPhone 4 devices
		iPadSimulator,

		iPhone2G,
		iPhone3G,
		iPhone3GS,
		iPhone4,
		iPhone4S,
		iPhone5,


		iPod1G,
		iPod2G,
		iPod3G,
		iPod4G,
		iPod5G,

		iPad1G, // both regular and 3G
		iPad2G,
		iPad3G,
		iPad4G,
		iPadMini,

		UnknowniPhone,
		UnknowniPod,
		UnknowniPad,

	};
}

class Environment:public Pattern::Singleton<Environment>
{
	friend class Pattern::Singleton<Environment>;
private:
	Environment()
	{
		mDeviceType=GetDeviceType();
		mIsJailBreak=IsJailBreakHelper();
		InitailizeEnvironment();
	}

	~Environment()
	{
	}

public:
	HeapString GetDeviceTypeString() const
	{
		return GetSystemInfoByName("hw.machine");
	}
	HeapString GetHwModel() const
	{
		return GetSystemInfoByName("hw.model");
	}

	DeviceType::DeviceType_t GetDeviceType()
	{
		HeapString deviceType=GetDeviceTypeString();
		HeapString prefix;
		if (deviceType.IsEmpty())
		{
			mDeviceType= DeviceType::Unknown;
			return mDeviceType;
		}

		if (deviceType=="iPhone1,1")
		{
			mDeviceType= DeviceType::iPhone2G;
			return mDeviceType;
		}
		if (deviceType=="iPhone1,2")
		{
			mDeviceType= DeviceType::iPhone3G;
			return mDeviceType;
		}
		if (deviceType=="iPhone2,1")
		{
			mDeviceType= DeviceType::iPhone3GS;
			return mDeviceType;
		}
		if (deviceType=="iPhone3,1")
		{
			mDeviceType= DeviceType::iPhone4;
			return mDeviceType;
		}
		if (deviceType=="iPhone4,1")
		{
			mDeviceType= DeviceType::iPhone4S;
			return mDeviceType;
		}
		if (deviceType=="iPhone5,1")
		{
			mDeviceType= DeviceType::iPhone5;
			return mDeviceType;
		}
		if (deviceType=="iPhone5,2")
		{
			mDeviceType= DeviceType::iPhone5;
			return mDeviceType;
		}
        if (deviceType=="iPhone6,1")
		{
			mDeviceType= DeviceType::iPhone5;
			return mDeviceType;
		}
        if (deviceType=="iPhone6,2")
		{
			mDeviceType= DeviceType::iPhone5;
			return mDeviceType;
		}
		prefix=deviceType.SubString(0,6);
		if (prefix=="iPhone")
		{
			mDeviceType= DeviceType::UnknowniPhone;
			return mDeviceType;
		}

		if (deviceType=="iPod1,1")
		{
			mDeviceType= DeviceType::iPod1G;
			return mDeviceType;
		}
		if (deviceType=="iPod2,1")
		{
			mDeviceType= DeviceType::iPod2G;
			return mDeviceType;
		}
		if (deviceType=="iPod3,1")
		{
			mDeviceType= DeviceType::iPod3G;
			return mDeviceType;
		}
		if (deviceType=="iPod4,1")
		{
			mDeviceType= DeviceType::iPod4G;
			return mDeviceType;
		}
		if (deviceType=="iPod5,1")
		{
			mDeviceType= DeviceType::iPod5G;
			return mDeviceType;
		}
		prefix=deviceType.SubString(0,4);
		if (prefix=="iPod")
		{
			mDeviceType= DeviceType::UnknowniPod;
			return mDeviceType;
		}
		

		if (deviceType=="iPad1,1"||deviceType=="iPad1,2")
		{
			mDeviceType= DeviceType::iPad1G;
			return mDeviceType;
		}
		if (deviceType=="iPad2,1"||deviceType=="iPad2,2"||deviceType=="iPad2,3"||deviceType=="iPad2,4")
		{
			mDeviceType= DeviceType::iPad2G;
			return mDeviceType;
		}
		if (deviceType=="iPad2,5"||deviceType=="iPad2,6"||deviceType=="iPad2,7")
		{
			mDeviceType= DeviceType::iPadMini;
			return mDeviceType;
		}

		if (deviceType=="iPad3,1"||deviceType=="iPad3,2"||deviceType=="iPad3,3")
		{
			mDeviceType= DeviceType::iPad3G;
			return mDeviceType;
		}

		if (deviceType=="iPad3,4"||deviceType=="iPad3,5"||deviceType=="iPad3,6")
		{
			mDeviceType= DeviceType::iPad4G;
			return mDeviceType;
		}

		prefix=deviceType.SubString(0,4);
		if (prefix=="iPad")
		{
			mDeviceType= DeviceType::UnknowniPad;
			return mDeviceType;
		}

		HeapString suffix=deviceType.SubString(deviceType.Length()-2,2);
		if (suffix=="86"||deviceType=="x86_64")
		{
			int width=GetUIScreenWidth();
			if(width<768)
			{
				mDeviceType= DeviceType::iPhoneSimulator;
				return mDeviceType;
			}
			else
			{
				mDeviceType= DeviceType::iPadSimulator;
				return mDeviceType;
			}

			mDeviceType= DeviceType::Simulator;
			return mDeviceType;
		}

		mDeviceType= DeviceType::Unknown;
		return mDeviceType;
	}
	bool IsSupportAd()
	{
		switch(mDeviceType)
		{
		case DeviceType::iPhone4:
		case DeviceType::iPhone4S:
		case DeviceType::iPhone5:
		case DeviceType::iPod4G:
		case DeviceType::iPad2G:
		case DeviceType::iPad3G:
		case DeviceType::iPad4G:
		case DeviceType::iPadMini:
		case DeviceType::iPhoneSimulator:
			return true;
		default:
			return false;
		}
	}

	bool IsiPad()
	{
		switch(mDeviceType)
		{
		case DeviceType::iPad1G:
		case DeviceType::iPad2G:
		case DeviceType::iPad3G:
		case DeviceType::iPad4G:
		case DeviceType::iPadMini:
		case DeviceType::iPadSimulator:
		case DeviceType::UnknowniPad:
			return true;
		default:
			return false;
		}
	}

	bool IsiPhone()
	{
		switch(mDeviceType)
		{
		case DeviceType::iPhone2G:
		case DeviceType::iPhone3G:
		case DeviceType::iPhone3GS:
		case DeviceType::iPhone4:
		case DeviceType::iPhone4S:
		case DeviceType::iPhone5:
		case DeviceType::iPhoneSimulator:
		case DeviceType::UnknowniPhone:
			return true;
		default:
			return false;
		}
	}

	bool IsJailBreak()
	{
		
		
		return mIsJailBreak;
	}

	bool IsArmV6()
	{

#ifdef __APPLE__
#if (TARGET_IPHONE_SIMULATOR == 0) && (TARGET_OS_IPHONE == 1)
#if defined(_ARM_ARCH_7) && defined(_ARM_ARCH_6)
		switch(mDeviceType)
		{
		case DeviceType::iPhone2G:
		case DeviceType::iPod1G:
		case DeviceType::iPod2G:

			return true;
			break;
		default:
			return false;
			break;
		}
#elif defined(_ARM_ARCH_6)
		return true;
#endif
#endif
#endif
		return false;
	}

	bool IsArmV7()
	{
#ifdef __APPLE__
#if (TARGET_IPHONE_SIMULATOR == 0) && (TARGET_OS_IPHONE == 1)
#if defined(_ARM_ARCH_7) && defined(_ARM_ARCH_6)
		switch(mDeviceType)
		{
		case DeviceType::iPhone3G:
		case DeviceType::iPhone3GS:
		case DeviceType::iPhone4:
		case DeviceType::iPhone4S:
		case DeviceType::iPhone5:
		case DeviceType::iPod3G:
		case DeviceType::iPod4G:
		case DeviceType::iPod5G:
		case DeviceType::iPad1G:
		case DeviceType::iPad2G:
		case DeviceType::iPad3G:
		case DeviceType::iPad4G:
		case DeviceType::iPadMini:
			return true;
			break;
		default:
			return false;
			break;
		}
#elif defined(_ARM_ARCH_7)
		return true;
#endif
#endif
#endif
		return false;
	}
	void SetDeviceType(DeviceType::DeviceType_t inDebugDeviceType) {mDeviceType = inDebugDeviceType; InitailizeEnvironment();}
	void SetIsJailBreak(bool val) {mIsJailBreak = val; }

	HeapString GetMacAddress();
	bool IsNetworkAvailable();
	EnvironmentTag& GetTag() { return mTag; }
	void SetTag(const EnvironmentTag& val) { mTag = val; }	//for debug case

private:
	HeapString GetSystemInfoByName(const StringRef& inName) const;
	int GetUIScreenWidth()const;
	bool IsJailBreakHelper()const;

	void InitailizeEnvironment()
	{
		mTag.Version=PublishVersions::main;
		mTag.Language=PublishLanguages::zhcn;

		switch(mDeviceType)
		{
		case DeviceType::iPhone2G:
		case DeviceType::iPhone3G:
		case DeviceType::iPhone3GS:
		case DeviceType::iPod1G:
		case DeviceType::iPod2G:
		case DeviceType::iPod3G:
			mTag.Device=PublishDevices::sd;
			break;
		case DeviceType::iPod4G:
		case DeviceType::iPhone4:
		case DeviceType::iPhone4S:
			mTag.Device=PublishDevices::hd;
			break;
		case DeviceType::iPhone5:
		case DeviceType::iPod5G:
			mTag.Device=PublishDevices::hd5;
			break;
		case DeviceType::iPad1G:
		case DeviceType::iPad2G:
		case DeviceType::iPadMini:
			mTag.Device=PublishDevices::ipad;
			break;
		case DeviceType::iPad3G:
		case DeviceType::iPad4G:
			mTag.Device=PublishDevices::ipad3;
			break;
		default:
			mTag.Device=PublishDevices::hd;
			break;
		}
	}


private:
	DeviceType::DeviceType_t mDeviceType;
	bool mIsJailBreak;
	EnvironmentTag mTag;
};
MEDUSA_END;
