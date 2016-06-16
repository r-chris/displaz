# Find NanoGUI
#
# This sets:
#   - NANOGUI_FOUND:  system has NanoGUI
#   - NANOGUI_INCLUDE_DIRS: the NanoGUI include directories
#   - NANOGUI_LIBRARIES: the NanoGUI library

find_path (NANOGUI_INCLUDE_DIRS NAMES nanogui/nanogui.h)
find_library (NANOGUI_LIBRARY NAMES nanogui)

set (NANOGUI_LIBRARIES ${NANOGUI_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(NanoGUI
    REQUIRED_VARS NANOGUI_INCLUDE_DIRS NANOGUI_LIBRARY
    VERSION_VAR NANOGUI_VERSION_STRING
)

mark_as_advanced(NANOGUI_LIBRARY NANOGUI_LIBRARIES NANOGUI_INCLUDE_DIRS)
