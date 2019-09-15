cmake_minimum_required(VERSION 3.14)
project(Fistful_Of_Frags)

set(CMAKE_CXX_STANDARD 17)

list(APPEND SOURCES
        Menu/MenuRewrite.cxx
        Menu/BoolItem.cxx
        Menu/SwitchItem.cxx

        Features/SpecList/SpecList.cxx

        Sources/Signature.cxx
        Sources/DLLMain.cxx

        Hooks/KeyEvent/KeyEvent.cxx
        Hooks/NetVar/NetVar.cxx
        Hooks/CreateMove/CreateMove.cxx
        Hooks/Panels/Panels.cxx

        SDK/SDK.cxx
        SDK/CDrawManager/DrawManager.cxx
        SDK/VMT/VMTHooks.cxx
        )

add_library(Fistful_Of_Frags SHARED ${SOURCES})