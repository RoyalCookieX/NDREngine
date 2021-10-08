#pragma once
#include "ButtonCodes.h"

namespace NDR
{
    class Input
    {
    public:
        static NDRButtonAction GetKey(NDRKey keyCode);
        static NDRButtonAction GetMouseButton(NDRMouseButton button);
    };
}
