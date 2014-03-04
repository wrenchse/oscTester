#include "faceVis.h"

faceVis::faceVis(){
       
    dim = 20;
    offset = 2;
    
}

void faceVis::setup(ofImage img){
    w = img.getWidth();
    h = img.getHeight();
    
    xx.resize(w*h);
    size.resize(w*h);
    
    int i = 0;
    for(int y = 0; y < h; y++) {
		for(int x = 0; x < w; x++) {
			ofColor cur = img.getColor(x, y);
			xx[i] = (cur.getBrightness() / 255);
            i++;
		}
	}

}


void faceVis::update(float trigger){
    
    rms = trigger;
    int i = 0;
    
	for(int y = 0; y < h; y+=  5) {
		for(int x = 0; x < w; x+=5) {
            size[i] = xx[x+(y*w)] * trigger * 200;
            i++;
		}
	}

}

void faceVis::draw(int picky, int wave){
    
    ofPushMatrix();
    ofEnableAlphaBlending();
    ofSetColor(sin(rms)*195, sin(rms/2.3)*55, sin(rms/3.14), 155*rms);
    
    ofTranslate(ofGetWidth()/2-w*offset/2, ofGetHeight()/2-h*offset/2,0);
   
    switch (picky) {
            
        case 0:
        {
            int i = 0;
           
            for(int y = 0; y < h; y+= 5) {
                ofPushMatrix();
                ofBeginShape();
                ofTranslate(0, y*offset);
                ofRotateX(wave*20);
                for(int x = 0; x < w; x+=5) {
                    ofVertex(x * offset, 0 ,size[i]);
                    i++;
                }
                ofEndShape();
                ofPopMatrix();
            };
        }
            break;
            
        case 1:         {
            int i = 0;
               
            for(int y = 0; y < h; y+= 5) {
                ofPushMatrix();
                ofTranslate(0, y*offset);
                for(int x = 0; x < w; x+=5) {
                   if(xx[x+(y*w)] > 0.8 ){
                        ofSetColor(250, 50, 50, size[i]);
                        ofCircle(x * offset, 0 ,size[i],5);
                    }
                    
                    i++;
                }
                ofPopMatrix();
            };
        }
            break;
        
        case 2: {
           
            triangulation.reset();
            
            int i = 0;
            for(int y = 0; y < h; y+= 10) {
                for(int x = 0; x < w; x+= 10) {
                    i = x+(y*w);
                    if(xx[i] > 0.8 ){
                        triangulation.addPoint(ofPoint(x*offset,y*offset, xx[i] * rms *200 ));
                    };
                    
                }
            }
            triangulation.triangulate();
            ofNoFill();
            triangulation.draw();
            ofFill();
        }
            break;
            
            
        case 3:{
            
            int i = 0;
            ofNoFill();
            
            for(int y = 0; y < h; y+= 5) {
                ofPushMatrix();
                ofBeginShape();
                ofTranslate(0, y*offset);
                ofRotateX(wave*20);
                for(int x = 0; x < w; x+=5) {
                    if (x < w/2) {
                         ofVertex(x * offset, 0 ,size[i]);
                    }
                   
                    i++;
                }
                ofEndShape();
                ofPopMatrix();
            };          
            
            triangulation.reset();
            
            int d = 0;
            for(int y = 0; y < h; y+= 10) {
                for(int x = w/2; x < w; x+= 10) {
                    d = x+(y*w);
                    if(xx[d] > 0.8 ){
                        triangulation.addPoint(ofPoint(x*offset,y*offset, xx[d] * rms *200 ));
                    };
                    
                }
            }
            triangulation.triangulate();
            
            
            
            triangulation.draw();
            ofFill();
            
            
        }
            default:
            break;
    }
    
    ofPopMatrix();
    
}