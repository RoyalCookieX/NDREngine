#include "ndrpch.h"
#include "EventDispatcher.h"

#define NDR_DISABLE_LOGDEBUG
#include "Core/Log.h"

namespace NDR
{
	static CallbackID GenerateCallbackID()
	{
		static CallbackID id = 0;
		return id++;
	}
	
	CallbackData::CallbackData(EventCategory category, EventFunc func):
		_id(GenerateCallbackID()),
		_category(category),
		_func(func)
	{
	}

	CallbackID EventDispatcher::AddCallback(EventCategory category, EventFunc&& func)
	{
		const auto pair = sCallbacks.emplace(category, std::move(func));
		return pair.first->GetCallbackID();
	}

	void EventDispatcher::RemoveCallback(CallbackID id)
	{
		const auto callbackIt = std::find_if(
			sCallbacks.begin(), sCallbacks.end(),
			[id](CallbackData data)
			{
				return data.GetCallbackID() == id;
			});
		
		if (callbackIt != sCallbacks.end())
			sCallbacks.erase(callbackIt);
	}
}

namespace std
{
	using namespace NDR;
	
	inline bool operator<(const CallbackData& lhs, const CallbackData& rhs)
	{
		return (UInt32)lhs.GetEventCategory() < (UInt32)rhs.GetEventCategory();
	}
}