#ifndef ALTIRC_TOLUATEST_H
#define ALTIRC_TOLUATEST_H


class ToluaTest { // tolua_export
public:
    // tolua_begin
    ToluaTest();
    
    ~ToluaTest();
    
    void setBlah(int blah);
    int blah();
    // tolua_end
private:
    int blah_;
}; // tolua_export


#endif //ALTIRC_TOLUATEST_H
