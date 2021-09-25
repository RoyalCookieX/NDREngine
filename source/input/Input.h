#pragma once
#include "ButtonCodes.h"

namespace NDR
{
    class Input
    {
    public:
        static NDRButtonAction GetKey(NDRKey keyCode) { return _instance->GetKey_Impl(keyCode); }
        static NDRButtonAction GetMouseButton(NDRMouseButton button) { return _instance->GetMouseButton_Impl(button); }
    private:
        Input() { }
        ~Input() { }

        NDRButtonAction GetKey_Impl(NDRKey keycode) const;
        NDRButtonAction GetMouseButton_Impl(NDRMouseButton button) const;

        Input(const Input& other) = delete;
        Input(Input&& other) = delete;
        Input& operator =(const Input& other) = delete;
        Input& operator =(Input&& other) = delete;

        static Input* _instance;
    };
}
