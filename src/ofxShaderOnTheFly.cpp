//
//  ofxShaderOnTheFly.cpp
//
//  Created by satcy on 2016/01/05.
//
//
#include "ofxShaderOnTheFly.h"
#ifdef DISABLE_OFX_SHADER_ON_THE_FLY
#else

bool ofxShaderOnTheFly::is_active_all = true;

using namespace std;

ofxShaderOnTheFly::ofxShaderOnTheFly() : ofShader() {
    fragFileName = "";
    vertFileName = "";
    geomFileName = "";
}

ofxShaderOnTheFly::~ofxShaderOnTheFly(){
    unload();
    disable();
}

bool ofxShaderOnTheFly::load(string shaderName){
    return load(shaderName + ".vert", shaderName + ".frag");
}

bool ofxShaderOnTheFly::load(string vertName, string fragName, string geomName){
    if(vertName.empty() == false) {
        vertFileName = vertName;
        ofFile file(vertFileName);
        lastVertTimestamp = std::filesystem::last_write_time(file);
    }
    if(fragName.empty() == false) {
        fragFileName = fragName;
        ofFile file(fragFileName);
        lastFragTimestamp = std::filesystem::last_write_time(file);
    }
    if(geomName.empty() == false) {
        geomFileName = geomName;
        ofFile file(geomFileName);
        lastGeomTimestamp = std::filesystem::last_write_time(file);
    }
    enable();
    return ofShader::load(vertName, fragName, geomName);
}

void ofxShaderOnTheFly::setGeometryInputType(GLenum type) {
    geometry_input_type = type;
    ofShader::setGeometryInputType(type);
}

void ofxShaderOnTheFly::setGeometryOutputType(GLenum type) {
    geometry_output_type = type;
    ofShader::setGeometryOutputType(type);
}

void ofxShaderOnTheFly::setGeometryOutputCount(int count) {
    geomrty_output_count = count;
    ofShader::setGeometryOutputCount(count);
}

void ofxShaderOnTheFly::enable(){
    ofAddListener(ofEvents().update, this, &ofxShaderOnTheFly::update);
}

void ofxShaderOnTheFly::disable(){
    ofRemoveListener(ofEvents().update, this, &ofxShaderOnTheFly::update);
}
void ofxShaderOnTheFly::update(){
    if ( isLoaded() && !is_active_all ) return;

    if ( ofGetFrameNum()%100 == 1 ) {
        ofFile fragFile(fragFileName), vertFile(vertFileName);
        
        std::time_t fragTimestamp = std::filesystem::last_write_time(fragFile);
        std::time_t vertTimestamp = std::filesystem::last_write_time(vertFile);
        
        if ( !geomFileName.empty() ) {
            ofFile geomFile(geomFileName);
            std::time_t geomTimestamp = std::filesystem::last_write_time(geomFile);
            
            if(fragTimestamp != lastFragTimestamp || vertTimestamp != lastVertTimestamp || geomTimestamp != lastGeomTimestamp ) {
                unload();
                ofShader::setGeometryInputType(geometry_input_type);
                ofShader::setGeometryOutputType(geometry_output_type);
                ofShader::setGeometryOutputCount(geomrty_output_count);
                bool validShader = ofShader::load(vertFileName, fragFileName, geomFileName);
            }
            lastGeomTimestamp = geomTimestamp;
        } else {
            if(fragTimestamp != lastFragTimestamp || vertTimestamp != lastVertTimestamp) {
                bool validShader = ofShader::load(vertFileName, fragFileName);
            }
        }
        
        lastFragTimestamp = fragTimestamp;
        lastVertTimestamp = vertTimestamp;
    }
}

void ofxShaderOnTheFly::update(ofEventArgs &e){
    update();
}
#endif
