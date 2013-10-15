#include "core/application.h"
#include "core/defaultscene.h"
#include "core/manager/luamanager.h"

int main()
{
    using namespace Core;

    Application *app = Application::getInstance();
    app->setWindowTitle("Test");
    app->setFullScreen(false);
    app->setSize(glm::ivec2(800, 600));
    app->setColorDepth(EApplication::ColorDepth32);

    DefaultScene scene;
    app->setScene(&scene);

    if (app->init())
        app->exec();
    app->clear();

    return 0;
}
