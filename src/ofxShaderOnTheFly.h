#pragma once

#include "ofShader.h"

#define OFX_GLSL(VERSION,CODE) "#version " #VERSION "\n" #CODE

#ifdef DISABLE_OFX_SHADER_ON_THE_FLY
typedef ofShader ofxShaderOnTheFly;
#else
class ofxShaderOnTheFly : public ofShader{
protected:
    std::time_t lastFragTimestamp, lastVertTimestamp, lastGeomTimestamp;
    string fragFileName, vertFileName, geomFileName;
    GLenum geometry_input_type, geometry_output_type;
    int geomrty_output_count;
public:
    ofxShaderOnTheFly();
    ~ofxShaderOnTheFly();
    
    bool load(string shaderName);
    bool load(string vertName, string fragName, string geomName="");
    
    void setGeometryInputType(GLenum type);
    void setGeometryOutputType(GLenum type);
    void setGeometryOutputCount(int count);
    
    void enable();
    void disable();
    
    void update();
protected:
    void update(ofEventArgs &e);
};

#endif