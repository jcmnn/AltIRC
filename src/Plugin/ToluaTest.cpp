#include <iostream>
#include "ToluaTest.h"

int ToluaTest::blah() {
    return blah_;
}

void ToluaTest::setBlah(int blah) {
    blah_ = blah;
}

ToluaTest::ToluaTest() : blah_(0) {

}

ToluaTest::~ToluaTest() {
    std::cout << "deconstructed" << std::endl;
}
