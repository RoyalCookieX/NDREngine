#include "ExampleApplication.h"

void ExampleApplication::Initialize()
{
    NDR_LOGINFO("Example Application!");
    NDR_LOGDEBUG("DEBUG MODE");
}

void ExampleApplication::Tick()
{
    if(NDR::Input::OnKeyPressed(NDR::Keycode::ESCAPE))
        GetWindow()->Close();
}

void ExampleApplication::Shutdown()
{
}