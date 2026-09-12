#pragma once

#include "ofShader.h"
#include "ofEvents.h"
#include <filesystem>

#define OFX_GLSL(VERSION,CODE) "#version " #VERSION "\n" #CODE
//#define DISABLE_OFX_SHADER_ON_THE_FLY
#ifdef DISABLE_OFX_SHADER_ON_THE_FLY
typedef ofShader ofxShaderOnTheFly;
#else
class ofxShaderOnTheFly : public ofShader{
private:
    static bool is_active_all;
public:
    static void setIsActiveAll( bool b ) { is_active_all = b; }
    static bool getIsActiveAll() { return is_active_all; }
protected:
    std::filesystem::file_time_type lastFragTimestamp, lastVertTimestamp, lastGeomTimestamp;
    std::string fragFileName, vertFileName, geomFileName;
    GLenum geometry_input_type, geometry_output_type;
    int geomrty_output_count;
public:
    ofxShaderOnTheFly();
    ~ofxShaderOnTheFly();
    
    bool load(std::string shaderName);
    bool load(std::string vertName, std::string fragName, std::string geomName="");
    
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
