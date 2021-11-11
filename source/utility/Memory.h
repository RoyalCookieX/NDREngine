#pragma once

namespace NDR
{
   
    struct RefCounter
    {
        RefCounter(): _refCount(0) { }

        uint32_t AddRef() { return ++_refCount; }
        uint32_t RemoveRef() { return --_refCount; }

        uint32_t GetRefCount() const { return _refCount; }

    private:
        uint32_t _refCount;
    };
    
    template<typename TType>
    class UniquePtr
    {
    public:
        using PtrType = TType*;
        using RefType = TType&;

        UniquePtr(): _ptr(nullptr) { }
        UniquePtr(PtrType ptr): _ptr(ptr) { }

        ~UniquePtr() { delete _ptr; }

        UniquePtr(const UniquePtr&) = delete;
        UniquePtr& operator=(const UniquePtr&) = delete;

        UniquePtr(UniquePtr&& other) noexcept:
            _ptr(other._ptr)
        {
            other._ptr = nullptr;
        }

        UniquePtr& operator=(UniquePtr&& other) noexcept
        {
            if(*this != other)
            {
                _ptr = other._ptr;

                other._ptr = nullptr;
            }
            return *this;
        }

        bool operator==(const UniquePtr& other) const { return *_ptr == *other._ptr; }
        bool operator!=(const UniquePtr& other) const { return !(*this == other); }

        PtrType GetPtr() { return _ptr; }
        PtrType operator->() const { return _ptr; }
        RefType operator*() { return *_ptr; }
    private:
        PtrType _ptr;
    };

    template<typename TType>
    class SharedPtr
    {
    public:        
        using PtrType = TType*;
        using RefType = TType&;

        SharedPtr(): _ptr(nullptr), _refCounter(nullptr) { }
        SharedPtr(PtrType ptr): _ptr(ptr), _refCounter(new RefCounter())
        {
            _refCounter->AddRef();
        }
        
        ~SharedPtr()
        {
            if(_refCounter == nullptr)
                return;
            
            if(_refCounter->RemoveRef() == 0)
            {
                delete _ptr;
                delete _refCounter;
            }
        }

        SharedPtr(const SharedPtr& other):
            _ptr(other._ptr),
            _refCounter(other._refCounter)
        {
            _refCounter->AddRef();
        }
        SharedPtr& operator=(const SharedPtr& other)
        {
            if(*this != other)
            {
                _ptr = other._ptr;
                _refCounter = other._refCounter;
                
                _refCounter->AddRef();
            }
            return *this;
        }

        SharedPtr(SharedPtr&& other) noexcept:
            _ptr(other._ptr),
            _refCounter(other._refCounter)
        {
            other._ptr = nullptr;
            other._refCounter = nullptr;
        }

        SharedPtr& operator=(SharedPtr&& other) noexcept
        {
            if(*this != other)
            {
                _ptr = other._ptr;
                _refCounter = other._refCounter;

                other._ptr = nullptr;
                other._refCounter = nullptr;
            }
            return *this;
        }

        bool operator==(const SharedPtr& other) const { return *_ptr == *other._ptr; }
        bool operator!=(const SharedPtr& other) const { return !(*this == other); }

        PtrType GetPtr() { return _ptr; }
        PtrType operator->() const { return _ptr; }
        RefType operator*() { return *_ptr; }    
    private:
        PtrType _ptr;
        RefCounter* _refCounter;
    };

    template<typename TType, typename... TArgs>
    UniquePtr<TType> CreateUniquePtr(TArgs&&... args)
    {
        TType* ptr = new TType(args...);
        return UniquePtr<TType>(ptr);
    }
    template<typename TType, typename... TArgs>
    SharedPtr<TType> CreateSharedPtr(TArgs&&... args)
    {
        TType* ptr = new TType(args...);
        return SharedPtr<TType>(ptr);
    }
}