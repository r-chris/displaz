// Copyright 2015, Christopher J. Foster and the other displaz contributors.
// Use of this code is governed by the BSD-style license found in LICENSE.txt
#pragma once

#include <nanogui/nanogui.h>
#include <nanogui/window.h>

#include <rapidjson/document.h>

#include <map>
#include <vector>
#include <string>

/// Very basic shader editor widget
class NGPluginLoader
{
    public:
        NGPluginLoader();
        ~NGPluginLoader();

        void load(nanogui::Screen * screen, const std::string & filePath);

    private:
        bool loadFile(std::vector<std::string> & fileContent, const std::string & filePath);

        void parseJson(nanogui::Widget * parent, const rapidjson::Value & value);

        nanogui::Widget * createWidget(nanogui::Widget * parent, const rapidjson::Value & value);

        std::vector<std::string> plugins;

};
