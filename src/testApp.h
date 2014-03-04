#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxPostGlitch.h"
#include "faceVis.h"
#include "wrBack.h"

#define HOST "localhost"
#define PORT 57110
#define NUM_MSG_STRINGS 20

//--------------------------------------------------------
class testApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
       

		ofTrueTypeFont font;
		ofxOscSender sender;
        ofxOscReceiver receiver;
    
        int current_msg_string;
//        string msg_strings[NUM_MSG_STRINGS];
    string msg_string;
        string msg_strings;
        
        float timers[NUM_MSG_STRINGS];
    
        int mouseX, mouseY;
        string mouseButtonState;
    
    float rms;
    float wave;
    int h;
    int w;
    float diameter = 10;
    int offset = 2;

vector<float> xx;
    vector<float> size;
    
    int picker = 0;
    
    
    ofImage img;       // The source image
    ofImage sig;
    faceVis fejsy;
    wrBack backy;
  
    
    int cellsize = 20; // Dimensions of each cell in the grid
    int columns, rows;   // Number of columns and rows in our system
    int direction = 2;

    ofLight pointLight;
    ofVec3f center;
    float radius;
    ofMaterial material;
    
    
    
    
    ofFbo			myFbo;
	    
	ofTexture		texture;
    
	/*Addon instance*/
	ofxPostGlitch	myGlitch;
};

