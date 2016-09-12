#pragma once

#include "ofShader.h"

#ifdef DISABLE_OFX_SHADER_ON_THE_FLY
typedef ofShader ofxShaderOnTheFly;
#else
class ofxShaderOnTheFly : public ofShader{
protected:
    std::time_t lastFragTimestamp, lastVertTimestamp, lastGeomTimestamp;
    string fragFileName, vertFileName, geomFileName;
public:
    ofxShaderOnTheFly();
    ~ofxShaderOnTheFly();
    
    bool load(string shaderName);
    bool load(string vertName, string fragName, string geomName="");
    
    void enable();
    void disable();
    
    void update();
protected:
    void update(ofEventArgs &e);
};

#endif