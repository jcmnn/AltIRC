#include "AltIrc.h"

AltIrc::AltIrc() {

}

void AltIrc::run() {
    pluginManager_.initialize();
    connectionHandler_.run();
}

void AltIrc::create() {
    altIrc_ = std::unique_ptr<AltIrc>(new AltIrc);
}

std::unique_ptr<AltIrc> AltIrc::altIrc_;

void AltIrc::close() {
    altIrc_.reset();
}
