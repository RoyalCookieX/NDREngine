#include <NDREngine.h>
#include <ExampleApplication.h>

int main()
{
    NDR::UniquePtr<ExampleApplication> app = NDR::CreateUniquePtr<ExampleApplication>();
    app->Run();
    return 0;
}