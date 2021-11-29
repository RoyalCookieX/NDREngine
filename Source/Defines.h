#pragma once

#define BIT(bit) 1 << bit

#if defined(_MSC_VER)
    #define DEBUGBREAK __debugbreak()
#else
    #define DEBUGBREAK
#endif

namespace NDR
{
    using Int8 = char;
    using UInt8 = unsigned char;
    using Int16 = short;
    using UInt16 = unsigned short;
    using Int32 = int;
    using UInt32 = unsigned int;
    using Int64 = long;
    using UInt64 = unsigned long;

    using USize = unsigned long long;

    struct Int32Pair
    {
    public:
        Int32Pair(Int32 x, Int32 y): data{x, y} { }	
        union
        {
            struct { Int32 x, y; };
            struct { Int32 width, height; };
            struct { Int32 data[2]; };
        };
    };

    struct UInt32Pair
    {
    public:
        UInt32Pair(UInt32 x, UInt32 y): data{x, y} { }
        union
        {
            struct { UInt32 x, y; };
            struct { UInt32 width, height; };
            struct { UInt32 data[2]; };
        };
    };
    
    template<typename TType>
    using UPointer = std::unique_ptr<TType>;
    template<typename TType>
    using SPointer = std::shared_ptr<TType>;

    template<typename TType, typename... TArgs>
    UPointer<TType> CreateUnique(TArgs&&... args)
    {
        return std::make_unique<TType>(std::forward<TArgs>(args)...);
    }
    template<typename TType, typename... TArgs>
    SPointer<TType> CreateShared(TArgs&&... args)
    {
        return std::make_shared<TType>(std::forward<TArgs>(args)...);
    }
    
    using RendererID = UInt32;
}