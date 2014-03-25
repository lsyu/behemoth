#include "core/application/application.h"
#include "core/application/basicguilayer.h"
#include "core/application/basicscene3dlayer.h"

int main(int argc, char *argv[])
{
    using namespace behemoth;

    CApplication *app = CApplication::getInstance();
    app->initialize(argc, argv);
    app->setWindowTitle("Cube with label example");
    app->setFullScreen(false);
    app->setSize(glm::ivec2(800, 600));
    app->setColorDepth(EColorDepth::_32);

    CBasicGUILayer guiLayer("example_cube_with_label.lua");
    app->setGUILayer(&guiLayer);
    CBasicScene3dLayer sceneLayer;
    app->setScene3DLayer(&sceneLayer);

    app->exec();

    return 0;
}
