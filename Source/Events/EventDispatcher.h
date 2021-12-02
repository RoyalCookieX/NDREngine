#pragma once
#include "Defines.h"
#include "Event.h"

#define NDR_BIND_STATIC_EVENTFUNC(func) func
#define NDR_BIND_NONSTATIC_EVENTFUNC(func) [this](auto&&... args) -> decltype(auto) { return this->func(std::forward<decltype(args)>(args)...); }
#define NDR_CAST_EVENT(eventPtr, outType, name) SPointer<outType> name = std::dynamic_pointer_cast<outType>(eventPtr)

namespace NDR
{
	using EventFunc = std::function<void(SPointer<Event>)>;
	using CallbackID = UInt32;

	struct CallbackData
	{
	public:
		CallbackData(EventCategory category, EventFunc func);

		CallbackID GetCallbackID() const { return _id; }
		EventCategory GetEventCategory() const { return _category; }
		const EventFunc& GetEventFunc() const { return _func; }
	private:
		CallbackID _id;
		EventCategory _category;
		EventFunc _func;
	};

	class EventDispatcher
	{
	public:
		template<typename TEventType, typename... TEventArgs>
		void Brodcast(TEventArgs&&... args)
		{
			const SPointer<Event> ePtr = CreateShared<TEventType>(std::forward<TEventArgs>(args)...);
			for (const CallbackData& callback : sCallbacks)
			{
				if (ePtr->IsCategory(callback.GetEventCategory()))
					callback.GetEventFunc()(ePtr);
	
				if (ePtr->IsHandled())
					break;
			}
		}
		CallbackID AddCallback(EventCategory category, EventFunc&& func);
		void RemoveCallback(CallbackID id);
	private:
		std::set<CallbackData> sCallbacks;
	};
}