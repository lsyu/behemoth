#include "core/application/application.h"
#include "layers/guilayer.h"
#include "core/application/basicscene3dlayer.h"

int main(int argc, char *argv[])
{
    using namespace core;

    CApplication *app = CApplication::getInstance();
    app->initialize(argc, argv);
    app->setWindowTitle("MessageBox example");
    app->setFullScreen(false);
    app->setSize(glm::ivec2(800, 600));
    app->setColorDepth(EColorDepth::_32);

    GUILayer guiLayer;
    app->setGUILayer(&guiLayer);
    CBasicScene3dLayer sceneLayer;
    app->setScene3DLayer(&sceneLayer);

    app->exec();

    return 0;
}
