#include <iostream>

#include "Network/TcpSocket.h"
#include "Plugin/ToluaTest.h"
#include "AltIrc.h"
#include "LuaState.h"
#include <csignal>

#include <execinfo.h>
#include <stdlib.h>
#include <limits>

void segHandler(int param) {
    std::cerr << "Segmentation fault :(" << "\n" << "Stack trace:\n";
    void *traces[30];
    int size = backtrace(traces, 30);
    char **symbols = backtrace_symbols(traces, size);
    for (int i = 0; i < size; i++) {
        std::cerr << symbols[i] << "\n";
    }
    free(symbols);
    std::cout << std::flush;

    std::signal(param, SIG_DFL);
    std::raise(param);
}

void termHandler(int param) {
    std::cout << "Terminated" << std::endl;
    
    AltIrc::close();
    
    exit(1);
}

int main(int argc, char *argv[]) {
    std::signal(SIGSEGV, segHandler);
    std::signal(SIGTERM, termHandler);
    std::signal(SIGINT, termHandler);
    
    AltIrc::create();
    AltIrc::get().run();
    
    return 0;
}