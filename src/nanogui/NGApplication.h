#pragma once

#include <nanogui/screen.h>
// #if defined(_WIN32)
//     #include <windows.h>
// #endif

#include "NGShaderEditor.h"
#include "NGShaderProgram.h"
#include "NGLogViewer.h"
#include "NGPluginLoader.h"

class NGApplication : public nanogui::Screen
{
public:
    NGApplication();
    ~NGApplication();

    virtual bool keyboardEvent(int key, int scancode, int action, int modifiers);
    virtual void draw(NVGcontext *ctx);
    virtual void drawContents();

private:
    NGShaderEditor * mShaderEditor;
    NGShaderProgram * mShaderProgram;
    NGLogViewer * mLogViewer;
    NGPluginLoader * mPluginLoader;
    nanogui::ProgressBar * mProgress;

};
