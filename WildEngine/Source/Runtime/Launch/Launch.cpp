#include "LaunchEngineLoop.h"
#include <memory>

int main(int argc, char** argv)
{
#ifdef _DEBUG
    // Detect memory leak
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // _CrtSetBreakAlloc(972);
#endif

    std::unique_ptr<LaunchEngineLoop> App = std::make_unique<LaunchEngineLoop>();
    return App->Run();
}