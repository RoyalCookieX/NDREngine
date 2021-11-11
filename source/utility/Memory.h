#pragma once

namespace NDR
{
    template<typename TType>
    using UniquePtr = std::unique_ptr<TType>;
    template<typename TType>
    using SharedPtr = std::shared_ptr<TType>;

    template<typename TType, typename... TArgs>
    UniquePtr<TType> CreateUniquePtr(TArgs&&... args)
    {
        return std::make_unique<TType>(std::forward<TArgs>(args)...);
    }
    template<typename TType, typename... TArgs>
    SharedPtr<TType> CreateSharedPtr(TArgs&&... args)
    {
        return std::make_shared<TType>(std::forward<TArgs>(args)...);
    }
}