#include <NDREngine.h>
#include <ExampleApplication.h>

void main()
{
    NDR::UPointer<ExampleApplication> app = NDR::CreateUnique<ExampleApplication>();
    app->Run();
}