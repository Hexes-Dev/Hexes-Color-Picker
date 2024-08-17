cmake_minimum_required(VERSION 3.21.1)
project(ColorPicker VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

include(CPack)

set(QT_PATH  /Users/nicholas/Qt/6.7.2/macos/lib/cmake)
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT_PATH} )


find_package(Qt6 6.7.2 REQUIRED COMPONENTS widgets gui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
# qt_standard_project_setup()

add_executable(ColorPicker MACOSX_BUNDLE
src/main.cpp
src/resources.qrc
src/gui/colorFinderWidget.cpp
src/gui/colorPreviewWidget.cpp
src/gui/mainWidget.cpp
src/gui/widgetFactory.cpp
src/utilities/colorSpace.cpp
)

target_link_libraries(${PROJECT_NAME} 
PRIVATE Qt6::Widgets 
PRIVATE Qt6::Core
PRIVATE Qt6::Gui
)

set_property(TARGET ColorPicker PROPERTY CXX_STANDARD 20)
