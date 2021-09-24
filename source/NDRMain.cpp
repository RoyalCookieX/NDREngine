#include "ndrpch.h"
#include "NDREngine.h"

int NDRMain()
{
    NDR::Engine* engine = new NDR::Engine();
    engine->Run();
    delete engine;
    return 0;
}
