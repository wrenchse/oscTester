#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    
    img.loadImage("face.jpg");  // Load the image
    
    fejsy.setup(img);
    
    rows = img.width / cellsize;  // Calculate # of columns
    columns = img.height / cellsize;  // Calculate # of rows
    

    //ofSetVerticalSync(0);
    //qofSetFrameRate(600);

     
	ofBackground(40, 10, 90);
    //ofSetBackgroundAuto(false);
	// open an outgoing connection to HOST:PORT
	sender.setup(HOST, 57110);
    
    cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(9000);
    
    current_msg_string = 0;
	mouseX = 0;
	mouseY = 0;
	mouseButtonState = "";
    
    ofxOscMessage m;
    m.setAddress("/notify");
    m.addIntArg(1);
    sender.sendMessage(m);
    
    sender.sendMessage(m);
   //ofEnableAlphaBlending();
   // ofEnableDepthTest();

    w = img.getWidth();
    h = img.getHeight();
   
    
    xx.resize(w*h);
    size.resize(w*h);
    
 //   ofEnableLighting();

//    ofSetGlobalAmbientColor(ofColor(0, 0, 0));
//    ofSetSmoothLighting(false);
    
//    
//    radius		= 300.f;
//	center.set(ofGetWidth()*.5, ofGetHeight()*.5, 0);
//    
//    // Point lights emit light in all directions //
//    // set the diffuse color, color reflected from the light source //
//    pointLight.setSpotlight();
//    pointLight.setSpotConcentration(255);
//    pointLight.setDiffuseColor( ofColor(0.f, 255.f, 0.f));
//    pointLight.setAttenuation(1.5);
//    
//    // specular color, the highlight/shininess color //
//	pointLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
//    pointLight.setPosition(center.x, center.y, 200);
//    material.setShininess( 120 );
//    
    
    
    
    
    
    myFbo.allocate(ofGetWidth(), ofGetHeight());
    
	myGlitch.setup(&myFbo);
}

//--------------------------------------------------------------
void testApp::update(){

	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);
        rms = m.getArgAsFloat(0);
        string msg_string;
	
		msg_string += ofToString(m.getArgAsFloat(0));
		msg_strings = msg_string;
        
	}
    
        
        
    myFbo.begin();
	ofClear(0, 0, 0,255);
    fejsy.update(rms);
    backy.draw();
    fejsy.draw(picker,wave);
    myFbo.end();
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    string buf;
	buf = "listening for osc messages on port" + ofToString(PORT);
	ofDrawBitmapString(buf, 10, 20);
    
    ofDrawBitmapString(msg_strings, 10, 40);

    
       
    wave = sin(ofGetElapsedTimef()/10)-1;
    
    cout << ofGetFrameRate() << endl;
  //  ofDisableLighting();
	  
   
    
    
    myGlitch.generateFx();
    myFbo.draw(0,0);

//    
//    ofNoFill();
//    ofScale(3,3);
//    ofEnableLighting();
//    pointLight.enable();
//    material.begin();
//    ofSetColor(pointLight.getDiffuseColor());    
//   
//    material.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == 'a' || key == 'A'){
		ofxOscMessage m;
		m.setAddress("/test");
		m.addIntArg(1);
		m.addFloatArg(3.5f);
		m.addStringArg("hello");
		m.addFloatArg(ofGetElapsedTimef());
		sender.sendMessage(m);
	}
    
    
    switch (key) {
        case 'a':
            picker = 0;
            break;
        case 's':
            picker = 1;
            break;
        case 'd':
            picker = 2;
            break;
        case 'f':
            picker = 3;
        default:
            break;
    }
    
    
    if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, true);
	if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW			, true);
	if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, true);
	if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, true);
	if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST			, true);
	if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, true);
	if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE			, true);
	if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, true);
	if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL			, true);
	if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT			, true);
    
	if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, true);
	if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, true);
	if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, true);
	if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, true);
	if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, true);
	if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, true);
	if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, true);

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if (key == '1') myGlitch.setFx(OFXPOSTGLITCH_CONVERGENCE	, false);
	if (key == '2') myGlitch.setFx(OFXPOSTGLITCH_GLOW			, false);
	if (key == '3') myGlitch.setFx(OFXPOSTGLITCH_SHAKER			, false);
	if (key == '4') myGlitch.setFx(OFXPOSTGLITCH_CUTSLIDER		, false);
	if (key == '5') myGlitch.setFx(OFXPOSTGLITCH_TWIST			, false);
	if (key == '6') myGlitch.setFx(OFXPOSTGLITCH_OUTLINE		, false);
	if (key == '7') myGlitch.setFx(OFXPOSTGLITCH_NOISE			, false);
	if (key == '8') myGlitch.setFx(OFXPOSTGLITCH_SLITSCAN		, false);
	if (key == '9') myGlitch.setFx(OFXPOSTGLITCH_SWELL			, false);
	if (key == '0') myGlitch.setFx(OFXPOSTGLITCH_INVERT			, false);
    
	if (key == 'q') myGlitch.setFx(OFXPOSTGLITCH_CR_HIGHCONTRAST, false);
	if (key == 'w') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUERAISE	, false);
	if (key == 'e') myGlitch.setFx(OFXPOSTGLITCH_CR_REDRAISE	, false);
	if (key == 'r') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENRAISE	, false);
	if (key == 't') myGlitch.setFx(OFXPOSTGLITCH_CR_BLUEINVERT	, false);
	if (key == 'y') myGlitch.setFx(OFXPOSTGLITCH_CR_REDINVERT	, false);
	if (key == 'u') myGlitch.setFx(OFXPOSTGLITCH_CR_GREENINVERT	, false);


}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
//	ofxOscMessage m;
//	m.setAddress("/mouse/position");
//	m.addIntArg(x);
//	m.addIntArg(y);
//	sender.sendMessage(m);
        pointLight.setPosition(x, y, 5000);
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	ofxOscMessage m;
	m.setAddress("/mouse/button");
	m.addStringArg("down");
	sender.sendMessage(m);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	ofxOscMessage m;
	m.setAddress("/mouse/button");
	m.addStringArg("up");
	sender.sendMessage(m);

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

