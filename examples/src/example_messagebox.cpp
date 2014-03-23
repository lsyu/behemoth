#include "core/application/application.h"
#include "layers/guilayer.h"

int main(int argc, char *argv[])
{
    using namespace behemoth;

    CApplication *app = CApplication::getInstance();
    app->initialize(argc, argv);
    app->setWindowTitle("MessageBox example");
    app->setFullScreen(false);
    app->setSize(glm::ivec2(800, 600));
    app->setColorDepth(EColorDepth::_32);

    GUILayer guiLayer("example_messagebox.lua");
    app->setGUILayer(&guiLayer);

    app->exec();

    return 0;
}