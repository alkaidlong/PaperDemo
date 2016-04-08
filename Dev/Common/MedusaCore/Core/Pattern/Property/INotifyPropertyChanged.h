#pragma  once
#include "MedusaCorePreCompiled.h"
#include "Core/Pattern/Event.h"
#include "Core/Pattern/Property/PropertyChangedEventArg.h"

MEDUSA_BEGIN;

namespace Pattern
{
	template<typename T>
	struct INotifyPropertyChanged
	{
		Pattern::Event<void (T& sender,PropertyChangedEventArg e)> PropertyChanged;
	};
}

MEDUSA_END;