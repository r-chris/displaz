#include "NGApplication.h"

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

NGApplication::NGApplication() : nanogui::Screen(Eigen::Vector2i(1024, 768), "Displaz"),
mProgress(NULL),
mShaderEditor(NULL),
mShaderProgram(NULL),
mPluginLoader(NULL)
{
    using namespace nanogui;

    /* Create an OpenGL shader to draw the main window contents.

       NanoGUI comes with a simple Eigen-based wrapper around OpenGL 3,
       which eliminates most of the tedious and error-prone shader and
       buffer object management.
    */

    mLogViewer = new NGLogViewer(this);
    mShaderEditor = new NGShaderEditor(this);

    mPluginLoader = new NGPluginLoader();
    // DEBUG TESTING
    mPluginLoader->load(this, "plugins/segmentation.json");

    performLayout(mNVGContext);

    mShaderProgram = new NGShaderProgram();
    mShaderProgram->init();
    mShaderProgram->bind();
    mShaderProgram->setup();
}

NGApplication::~NGApplication()
{
    delete mShaderProgram;
    delete mShaderEditor;
    delete mLogViewer;
}

bool NGApplication::keyboardEvent(int key, int scancode, int action, int modifiers)
{
    if (Screen::keyboardEvent(key, scancode, action, modifiers))
        return true;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        setVisible(false);
        return true;
    }
    return false;
}

void NGApplication::draw(NVGcontext *ctx)
{
    /* Animate the scrollbar */
    if(mProgress)
        mProgress->setValue(std::fmod((float) glfwGetTime() / 10, 1.0f));

    /* Draw the user interface */
    Screen::draw(ctx);
}

void NGApplication::drawContents()
{
    using namespace nanogui;

    /* Draw the window contents using OpenGL */
    mShaderProgram->bind();
    mShaderProgram->draw(mSize.x(), mSize.y());
}
