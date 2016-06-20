#pragma once

#include <string>

#include <nanogui/nanogui.h>
#include <nanogui/window.h>
#include <nanogui/layout.h>
#include <nanogui/label.h>
#include <nanogui/checkbox.h>
#include <nanogui/button.h>
#include <nanogui/toolbutton.h>
#include <nanogui/popupbutton.h>
#include <nanogui/combobox.h>
#include <nanogui/progressbar.h>
#include <nanogui/entypo.h>
#include <nanogui/messagedialog.h>
#include <nanogui/textbox.h>
#include <nanogui/slider.h>
#include <nanogui/imagepanel.h>
#include <nanogui/imageview.h>
#include <nanogui/vscrollpanel.h>
#include <nanogui/colorwheel.h>
#include <nanogui/graph.h>
#include <nanogui/glutil.h>

class NGShaderEditor : public nanogui::Window
{
public:
    NGShaderEditor(nanogui::Screen* parent);
    ~NGShaderEditor();

private:
    void addParameter(Widget * panel, const std::string & label, const std::string & value);
    void addDropDown(Widget * panel, const std::string & label, const std::vector<std::string> & values);

    double mPointRadius;

    nanogui::ProgressBar * mProgress;

};
