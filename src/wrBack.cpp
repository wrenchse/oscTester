//
//  wrBack.cpp
//  oscTester
//
//  Created by Jonas Kjellberg on 3/3/14.
//
//

#include "wrBack.h"


wrBack::wrBack(){

    
    
}

void wrBack::setup(){

    
}


void wrBack::update(){
    

    
}

void wrBack::draw(){
    ofPushMatrix();
    ofFill();
//    ofRotateZ(45);
    for(int i = 0; i<w+200; i+= 200){
        for(int o = 0; o<h; o+= 200){
        //ofDrawCone(i, o, 200, 200);
//            ofTriangle(i, 200/2, o, i+200, o+200, i+200);
           
            ofSetColor(i/20, 0, 10);
            ofTriangle(i+100, o, i, o+200, i+200, o+200);
            ofSetColor(i/20+5, 0, o/20);
            ofTriangle(i-100, o, i+100, o, i, o+200);
            

            
        };
    };
    
    ofPopMatrix();
}