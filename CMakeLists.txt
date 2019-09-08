cmake_minimum_required(VERSION 3.14)
project(Fistful_Of_Frags)

set(CMAKE_CXX_STANDARD 17)

list(APPEND SOURCES
        Sources/CSignature.cpp
        Sources/DLLMain.cpp

        Hooks/CreateMove/Client.cpp
        Hooks/Panels/Panels.cpp

        SDK/SDK.cxx
        SDK/CDrawManager/CDrawManager.cpp
        SDK/VMT/VMTHooks.cpp
        )

add_library(Fistful_Of_Frags SHARED ${SOURCES})