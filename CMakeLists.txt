cmake_minimum_required(VERSION 3.14)
project(Fistful_Of_Frags)

set(CMAKE_CXX_STANDARD 17)

list(APPEND HEADERS
        Headers/CGlobalVars.h
        Headers/CSignature.h
        Headers/dt_common2.h
        Headers/dt_recv2.h
        Headers/Vector.h
        Headers/WeaponList.h

        Hooks/CreateMove/Client.h
        Hooks/Panels/Panels.h

        SDK/SDK.h
        SDK/CDrawManager/CDrawManager.h
        SDK/VMT/VMTHooks.h
        SDK/VMT/getvfunc.h
        )

list(APPEND SOURCES
        Sources/CSignature.cpp
        Sources/DLLMain.cpp

        Hooks/CreateMove/Client.cpp
        Hooks/Panels/Panels.cpp

        SDK/CDrawManager/CDrawManager.cpp
        SDK/VMT/VMTHooks.cpp
        )

add_library(Fistful_Of_Frags SHARED ${SOURCES})