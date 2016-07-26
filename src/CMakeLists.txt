cmake_minimum_required(VERSION 2.7)
project(AltIRC)

set(SOURCES
        main.cpp
        Plugin/Bind.cpp
        Network/TcpSocket.cpp
        Network/Socket.cpp
        Network/IPSocket.cpp
        Network/SocketAddress.cpp
        Network/NetworkBuffer.cpp
        AltIrc.cpp
        IrcConnection.cpp
        ProtocolHandler.cpp
        IrcMessage.cpp
        Logger.cpp
        ConnectionHandler.cpp
        LuaState.cpp
        Plugin/CallbackHandler.cpp
        Plugin/PluginManager.cpp
)

set(HEADERS
        Plugin/Bind.h
        Network/TcpSocket.h
        Network/Socket.h
        Network/IPSocket.h
        Network/SocketAddress.h
        Network/NetworkBuffer.h
        AltIrc.h
        IrcConnection.h
        ProtocolHandler.h
        IrcMessage.h
        Logger.h
        ConnectionHandler.h
        LuaState.h
        Plugin/CallbackHandler.h
        Plugin/PluginManager.h
)

set(CMAKE_CXX_FLAGS "--std=c++11 -rdynamic")

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/Plugin/Bind.cpp
        COMMAND toluapp -o Bind.cpp -n binds Bind.pkg
        DEPENDS ${HEADERS} Plugin/Bind.pkg Plugin/Commands.lua
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Plugin
        VERBATIM)

add_executable(AltIRC ${SOURCES})

set_target_properties(AltIRC PROPERTIES OUTPUT_NAME ../AltIRC/AltIRC)

target_link_libraries(AltIRC Lua toluapp_lib)