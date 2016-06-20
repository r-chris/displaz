
#include "NGPluginLoader.h"

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

#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <iostream>
#include <fstream>

#include <unordered_set>

using namespace nanogui;
using namespace rapidjson;

static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };

static const std::unordered_set<std::string> kWidgetNames({ "widget", "window", "label", "button", "slider", "textBox", "toolButton", "popupButton", "checkBox", "comboBox", "messageDialog", "vScrollPanel", "imagePanel", "imageView", "graph", "colorWheel" });

static const std::unordered_set<std::string> kWidgetProperties({ "title", "modal", "drag", "position", "layout" });

static const std::unordered_set<std::string> kLayouts({ "groupLayout", "boxLayout", "gridLayout" });

NGPluginLoader::NGPluginLoader()
{
}

NGPluginLoader::~NGPluginLoader()
{
}

void NGPluginLoader::load(Screen * screen, const std::string & filePath)
{
    // printf("Loading Plugin %s\n", filePath.c_str());

    std::vector<std::string> fileContent;
    if (!loadFile(fileContent, filePath))
        return;

    std::stringstream joinedJson;
    for (const auto & value : fileContent)
    {
        joinedJson << value << " ";
    }
    std::string json = joinedJson.str().substr(0,joinedJson.str().size()-1);

    // printf("Parsin JSON: %s\n", json.c_str());

    Document document;
    document.Parse(json.c_str());

    assert(document.IsObject());

    parseJson(screen, document);
}

bool NGPluginLoader::loadFile(std::vector<std::string> & fileContent, const std::string & filePath)
{
    std::ifstream infile(filePath, std::ifstream::in);

    if (!infile.is_open())
        return false;

    // char c = ifs.get();
    // while (infile.good())

    std::string line;

    while(getline(infile, line))
    {
        fileContent.push_back(line);
    }

    infile.close();

    return true;

}

void NGPluginLoader::parseJson(Widget * parent, const Value & value)
{
    Widget * localParent = parent;

    // TODO can we use auto here ?
    // https://github.com/miloyip/rapidjson/issues/162

    if (value.IsArray())
    {
        printf("Parsing ARRAY\n");
        std::string name = value.GetString();
        printf("JSON: %s\n", name.c_str());

        for (Value::ConstValueIterator itr = value.Begin(); itr != value.End(); ++itr)
        {
            // we will not really pay attention to the name of arrays ...
            // printf("Name of array member is: %s\n", itr->name.GetString());
            parseJson(parent, *itr);
        }
    }
    else if (value.IsObject())
    {
        printf("Parsing OBJECT\n");

        std::string name = value.GetString();

        printf("JSON: %s type: %s\n", name.c_str(), kTypeNames[value.GetType()]);

        bool isWidget = kWidgetNames.find(name) != kWidgetNames.end();
        if (isWidget)
        {
            localParent = createWidget(parent, value);
        }
        else
        {
            bool isWidgetProperty = kWidgetProperties.find(name) != kWidgetProperties.end();
            bool isLayout = kLayouts.find(name) != kLayouts.end();

            if (isWidgetProperty || isLayout)
            {
            }
            else
            {
                // printf("Invalid item in JSON: %s\n", name.c_str());
            }
        }

        // for (Value::ConstValueIterator itr = value.Begin(); itr != value.End(); ++itr)
        // {
        //     parseJson(localParent, *itr);
        // }

        // for (Value::ConstMemberIterator itr = value.MemberBegin(); itr != value.MemberEnd(); ++itr)
        // {
        //     parseJson(localParent, itr->value);
        // }
    }
    else if (value.IsString())
    {
        std::string s = value.GetString();
        printf("JSON string value: %s\n", s.c_str());
    }
    else if (value.IsNumber())
    {
        // Value of member is passed in here ... this is the end of the recursion
        if (value.IsUint())
        {
            unsigned int n = value.GetUint();
            printf("JSON uint value: %i\n", n);
        }
        else if (value.IsInt())
        {
            int n = value.GetInt();
            printf("JSON int value: %i\n", n);
        }
        else if (value.IsDouble())
        {
            double n = value.GetDouble();
            printf("JSON double value: %d\n", n);
        }
    }
    else if (value.IsBool())
    {
        printf("JSON bool value: %s\n", value.GetBool() ? "true" : "false");
    }
    else
    {
        printf("JSON value: %s\n", value.IsNull() ? "null" : "?");
    }
}

Widget * NGPluginLoader::createWidget(Widget * parent, const Value & value)
{
    printf("Create Widget: %s\n", value.GetString());

    return parent;
}
