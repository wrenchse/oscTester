#include "faceVis.h"

faceVis::faceVis(){
    
    offset = 2;
}

void faceVis::setup(ofImage img){
    w = img.getWidth();
    h = img.getHeight();
    
    cellsize = 5;
    
    texImage = img;
    
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
    
	for(int y = 0; y < h; y+=  cellsize) {
		for(int x = 0; x < w; x+= cellsize) {
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
            
        case 4:
            ofNoFill();
        case 0:
        {
            int i = 0;
            
            for(int y = 0; y < h; y+= cellsize) {
                ofPushMatrix();
                ofBeginShape();
                ofTranslate(0, y*offset);
                ofRotateX(wave*20);
                for(int x = 0; x < w; x+= cellsize) {
                    ofVertex(x * offset, 0 ,size[i]);
                    i++;
                }
                ofEndShape();
                ofPopMatrix();
            };
        }
            ofFill();
            break;
            
            
        case 1:         {
            int i = 0;
            
            for(int y = 0; y < h; y+= cellsize) {
                ofPushMatrix();
                ofTranslate(0, y*offset);
                for(int x = 0; x < w; x+= cellsize) {
                    if(xx[x+(y*w)] > 0.8 ){
                        ofSetColor(250, 50, 50, size[i]);
                        ofCircle(x * offset, 0 ,size[i], cellsize);
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
            for(int y = 0; y < h; y+= cellsize*2) {
                for(int x = 0; x < w; x+= cellsize*2) {
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
            
            for(int y = 0; y < h; y+= cellsize) {
                ofPushMatrix();
                ofBeginShape();
                ofTranslate(0, y*offset);
                ofRotateX(wave*20);
                for(int x = 0; x < w; x+=cellsize) {
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
            for(int y = 0; y < h; y+= cellsize*2) {
                for(int x = w/2; x < w; x+= cellsize*2) {
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
            break;
            
        case 5: {
            triangulation.reset();
            int i = 0;
            for(int y = 0; y < h; y+= cellsize*2) {
                for(int x = 0; x < w; x+= cellsize*2) {
                    i = x+(y*w);
                    if(xx[i] > 0.8 ){
                        
                        triangulation.addPoint(ofPoint(x*offset,y*offset, xx[i]*2 * rms *200 ));
                        
                    };
                    
                }
            }
            
            triangulation.triangulate();
            for(int i=0;i<triangulation.triangleMesh.getNumVertices();i++) {
                triangulation.triangleMesh.addColor(ofColor(0,0,0));
            }
            
            for(int i=0;i<triangulation.triangleMesh.getNumIndices()/3;i+=1) {
                ofVec3f v = triangulation.triangleMesh.getVertex(triangulation.triangleMesh.getIndex(i*3));
                
                ofColor c = texImage.getColor(v.x/offset, v.y/offset);
                ofColor f(255,100,20);
                f.setBrightness(c.getBrightness());
                f.a = v.z/2.5;
                
                triangulation.triangleMesh.setColor(triangulation.triangleMesh.getIndex(i*3),f);
                triangulation.triangleMesh.setColor(triangulation.triangleMesh.getIndex(i*3+1),f);
                triangulation.triangleMesh.setColor(triangulation.triangleMesh.getIndex(i*3+2),f);
            }
            
            triangulation.draw();
            
            ofNoFill();
            ofSetColor(0,0,0,10);
            triangulation.triangulate();
            triangulation.draw();
            ofFill();
        }
            break;
            
            
        case 6:         {
            int i = 0;
            ofRectMode(center);
            for(int y = 0; y < h; y+= cellsize*2) {
                ofPushMatrix();
                ofTranslate(0, y*offset);
                for(int x = 0; x < w; x+= cellsize*2) {
                    int d = x+(y*w);
                    if(xx[d] > 0.7 ){
                        ofSetColor(250, 50, 50, xx[d]*rms*200);
                        ofRect(x * offset, 0 ,xx[d]*rms*200, cellsize*8, cellsize*8);
                    }
                    
                    i++;
                }
                ofPopMatrix();
            };
        }
            break;
            
            
        default:
            break;
    }
    
    ofPopMatrix();
    
}