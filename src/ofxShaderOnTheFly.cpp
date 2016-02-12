//
//  ofxShaderOnTheFly.cpp
//
//  Created by satcy on 2016/01/05.
//
//

#include "ofxShaderOnTheFly.h"
ofxShaderOnTheFly::ofxShaderOnTheFly() {
    ofShader::ofShader();
    fragFileName = "";
    vertFileName = "";
    geomFileName = "";
}

ofxShaderOnTheFly::~ofxShaderOnTheFly(){
    unload();
    disable();
}

bool ofxShaderOnTheFly::load(string shaderName){
    enable();
    fragFileName = shaderName + ".frag";
    vertFileName = shaderName + ".vert";
    geomFileName = "";
    return ofShader::load(shaderName);
}

bool ofxShaderOnTheFly::load(string vertName, string fragName, string geomName){
    enable();
    if(vertName.empty() == false) vertFileName = vertName;
    if(fragName.empty() == false) fragFileName = fragName;
    if(geomName.empty() == false) geomFileName = geomName;
    
    return ofShader::load(vertName, fragName, geomName);
}

void ofxShaderOnTheFly::enable(){
    ofAddListener(ofEvents().update, this, &ofxShaderOnTheFly::update);
}

void ofxShaderOnTheFly::disable(){
    ofRemoveListener(ofEvents().update, this, &ofxShaderOnTheFly::update);
}
void ofxShaderOnTheFly::update(){
    if ( ofGetFrameNum()%100 == 0 ) {
        ofFile fragFile(fragFileName), vertFile(vertFileName);
        
        std::time_t fragTimestamp = std::filesystem::last_write_time(fragFile);
        std::time_t vertTimestamp = std::filesystem::last_write_time(vertFile);
        
        
        if ( !geomFileName.empty() ) {
            ofFile geomFile(geomFileName);
            std::time_t geomTimestamp = std::filesystem::last_write_time(geomFile);
            
            if(fragTimestamp != lastFragTimestamp || vertTimestamp != lastVertTimestamp || geomTimestamp != lastGeomTimestamp ) {
                bool validShader = load(vertFileName, fragFileName, geomFileName);
            }
            lastGeomTimestamp = geomTimestamp;
        } else {
            if(fragTimestamp != lastFragTimestamp || vertTimestamp != lastVertTimestamp) {
                bool validShader = load(vertFileName, fragFileName);
            }
        }
        
        lastFragTimestamp = fragTimestamp;
        lastVertTimestamp = vertTimestamp;
    }
}

void ofxShaderOnTheFly::update(ofEventArgs &e){
    update();
}