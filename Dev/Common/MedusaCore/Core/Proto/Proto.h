#pragma once
#include "Core/Memory/MemoryData.h"
#include "Core/Log/Log.h"
#include "Core/String/StringRef.h"
#include "MedusaCorePreCompiled.h"

#define ENABLE_PROTO_ASSERT
MEDUSA_BEGIN;

namespace Proto
{
	//************************************
	// 名称:    	Serialize
	// 返回:   	void	
	// 参数: 	const T & item		
	// 参数: 	MemoryByteData outData		It must be deleted!
	// 功能:		Serialize a proto struct to memory data
	// 描述:		
	// 例子:		
	//************************************
	template<typename T>
	MemoryByteData Serialize(const T& item,bool isBinaryFormat=true)
	{
		if (isBinaryFormat)
		{
			int size= item.ByteSize();
			if (size<=0)
			{
				return MemoryByteData::Empty;
			}
			byte* buffer=new byte[size];
			bool isSuccess=item.SerializeToArray(buffer,size);
			if (!isSuccess)
			{
				SAFE_DELETE_ARRAY(buffer);
#ifdef ENABLE_PROTO_ASSERT
				Log::LogError("Failed to invoke Proto::ParseFrom");
#endif
				return MemoryByteData::Empty;
			}
			return MemoryByteData::Take(buffer,size);
		}
		else
		{
			std::string outString;
			google::protobuf::TextFormat::PrintToString(item,&outString);
			size_t size= outString.size()+1;
			if (size<=1)
			{
#ifdef ENABLE_PROTO_ASSERT
				Log::LogError("Failed to invoke Proto::ParseFrom");
#endif
				return MemoryByteData::Empty;
			}
			byte* buffer=new byte[size];
			StdString::CopyString((char*)buffer,size,outString.c_str());
			return MemoryByteData::Take(buffer,size-1);
		}
	}

	template<typename T>
	bool SerializeToString(const T& item,std::string& outStr)
	{
		bool isSuccess= google::protobuf::TextFormat::PrintToString(item,&outStr);
#ifdef ENABLE_PROTO_ASSERT
		if (!isSuccess)
		{
			Log::LogError("Failed to invoke Proto::ParseFrom");
		}
#endif
		return isSuccess;
	}

	template<typename T>
	void Print(const T& item)
	{
		std::string outStr;
		google::protobuf::TextFormat::PrintToString(item,&outStr);
		Log::LogInfo(outStr.c_str());
	}

	template<typename T>
	std::string PrintToString(const T& item)
	{
		std::string outStr;
		google::protobuf::TextFormat::PrintToString(item,&outStr);
		return outStr;
	}

	//************************************
	// 名称:    	ParseFrom
	// 返回:   	void	
	// 参数: 	T & outItem		
	// 参数: 	MemoryByteData data		it won't be deleted in this method
	// 功能:		Parse a proto struct from memory data
	// 描述:		
	// 例子:		
	//************************************
	template<typename T>
	bool ParseFrom(T& outItem,MemoryByteData data,bool isBinaryFormat=true)
	{
		if (data.IsNull())
		{
			return false;
		}
		bool isSuccess=false;
		if (isBinaryFormat)
		{
			isSuccess= outItem.ParseFromArray(data.GetData(),static_cast<int>(data.GetSize()));
		}
		else
		{
			const char* str=(const char*)data.GetData();
			std::string inStr(str);
			isSuccess= google::protobuf::TextFormat::ParseFromString(inStr,&outItem);
		}
#ifdef ENABLE_PROTO_ASSERT
		if (!isSuccess)
		{
			Log::LogError("Failed to invoke Proto::ParseFrom");
		}
#endif
		return isSuccess;
	}

	template<typename T>
	bool ParseFromString(T& outItem,const StringRef& input)
	{
		bool isSuccess= google::protobuf::TextFormat::ParseFromString(input.c_str(),&outItem);
#ifdef ENABLE_PROTO_ASSERT
		if (!isSuccess)
		{
			Log::LogError("Failed to invoke Proto::ParseFrom");
		}
#endif
		return isSuccess;

	}

	template<typename T>
	void RemoveItem(::google::protobuf::RepeatedPtrField< T >* items,int index)
	{
		int size= items->size();
		assert(index<=size-1);
		if (index<size-1)
		{
			items->SwapElements(index,size-1);
		}
		items->RemoveLast();
	}

	template<typename T>
	void RemoveItem(::google::protobuf::RepeatedField< T >* items,int index)
	{
		int size= items->size();
		assert(index<=size-1);
		if (index<size-1)
		{
			items->SwapElements(index,size-1);
		}
		items->RemoveLast();
	}

	template<typename T>
	T* CreateMessage(StringRef typeName)
	{
		const google::protobuf::Descriptor* descriptor = google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(typeName.c_str());
		if (descriptor)
		{
			const google::protobuf::Message* prototype = google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
			if (prototype)
			{
				return dynamic_cast<T*>(prototype->New());
			}
		}
		return NULL;
	}
}

MEDUSA_END;
