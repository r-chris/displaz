// Copyright 2015, Christopher J. Foster and the other displaz contributors.
// Use of this code is governed by the BSD-style license found in LICENSE.txt

#include "NGApplication.h"

#include "argparse.h"
// #include "config.h"
// #include "InterProcessLock.h"

class Geometry;

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

/// Run the main GUI window
int main(int argc, char* argv[])
{
    std::string lockName;
    std::string lockId;
    std::string socketName;

    ArgParse::ArgParse ap;
    ap.options(
        "displaz-gui - don't use this directly, use the displaz commandline helper instead)",
        "-instancelock %s %s", &lockName, &lockId, "Single instance lock name and ID to reacquire",
        "-socketname %s", &socketName,             "Local socket name for IPC",
        NULL
    );

    if(ap.parse(argc, const_cast<const char**>(argv)) < 0)
    {
        std::cerr << "ERROR: " << ap.geterror() << std::endl;
        return EXIT_FAILURE;
    }

    //TODO
    // Q_INIT_RESOURCE(resource);
    // qRegisterMetaType<std::shared_ptr<Geometry>>("std::shared_ptr<Geometry>");
    //TODO
    // InterProcessLock instanceLock(lockName);
    //
    // if (!lockId.empty())
    //     instanceLock.inherit(lockId);
    //
    // if (!socketName.empty())
    //     window.startIpcServer(QString::fromStdString(socketName));

    try {
        nanogui::init();

        {
            nanogui::ref<NGApplication> app = new NGApplication();
            app->drawAll();
            app->setVisible(true);
            nanogui::mainloop();
        }

        nanogui::shutdown();
    } catch (const std::runtime_error &e) {
        std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
        #if defined(_WIN32)
            MessageBoxA(nullptr, error_msg.c_str(), NULL, MB_ICONERROR | MB_OK);
        #else
            std::cerr << error_msg << endl;
        #endif
        return -1;
    }

    return 0;
}
