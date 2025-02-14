#
# SPDX-FileCopyrightText: 2022 naracanto https://naracanto.github.io
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

cmake_minimum_required(VERSION 3.16)

# Application version
set(RELEASE_SERVICE_VERSION_MAJOR "00")
set(RELEASE_SERVICE_VERSION_MINOR "01")
set(RELEASE_SERVICE_VERSION_PATCH "00")
set(RELEASE_SERVICE_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_PATCH}")

project(ktabelo VERSION ${RELEASE_SERVICE_VERSION} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Minimum versions
set(QT5_MIN_VERSION "5.15.2")
set(KF5_MIN_VERSION "5.83.0")

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

add_definitions(-DQT_NO_FOREACH)

# Qt modules
find_package(Qt5 ${QT5_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    Widgets
)

# KDE modules
find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    ConfigWidgets
    CoreAddons
    I18n
    WidgetsAddons
    XmlGui
)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)

# Source files
add_executable(ktabelo
    src/main.cpp
    src/main_window.cpp
    src/mdi_area.cpp
    src/mdi_document.cpp
    src/tabular_document.cpp
)

# Libraries to link
target_link_libraries(ktabelo
    Qt5::Core
    Qt5::Widgets
    KF5::ConfigWidgets
    KF5::CoreAddons
    KF5::I18n
    KF5::WidgetsAddons
    KF5::XmlGui
)

install(TARGETS ktabelo ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES
    src/ktabelo_ui.rc
    DESTINATION ${KDE_INSTALL_KXMLGUI5DIR}/ktabelo
)
