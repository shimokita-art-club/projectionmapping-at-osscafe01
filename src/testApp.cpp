#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	 
	
	ofSetVerticalSync(true);
	ofSetCircleResolution(80);
	ofBackground(0, 0, 0);
	
	// 0 output channels, 
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)
	
	soundStream.listDevices();
	
	//if you want to set a different device id 
	//soundStream.setDeviceID(0); //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.
    soundStream.setDeviceID(0);
	
	int bufferSize = 256;
	//soundStream.setDeviceID(2);
	
	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	volHistory.assign(400, 0.0);
	
	bufferCounter	= 0;
	drawCounter		= 0;
	smoothedVol     = 0.0;
	scaledVol		= 0.0;
	//soundStream.setup(this, 0, 2, 32000, bufferSize, 4);
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);

}

//--------------------------------------------------------------
void testApp::update(){
	//lets scale the vol up to a 0-1 range 
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);

	//lets record the volume into an array
	volHistory.push_back( scaledVol );
	
	//if we are bigger the the size we want to record - lets drop the oldest value
	if( volHistory.size() >= 400 ){
		volHistory.erase(volHistory.begin(), volHistory.begin()+1);
	}
}

//--------------------------------------------------------------
void testApp::draw(){
    static double maxRight = 0;
    static double maxLeft = 0;

    //right
	if(maxRight < right[0]){
        maxRight = right[0];
    }
    
    //*
    int color;
    int r;
    int g;
    int b;
    color = int(256*256*256*((maxRight+right[0])/maxRight*2));
    int mask = 255;
    r = mask&(color >> 16);
    g = mask&(color >> 8);
    b = mask&(color);
//    ofSetColor(225);
    ofSetColor(r, g, b);
//    ofFill();
    //ofCircle(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), scaledVol * 190.0f);
    //*/
    
    { // ぱーてぃくるついか
        p.push_back(P(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), r, g, b, scaledVol * 190.0f));
    }
    
    { // 表示
        for( list<P>::iterator it = p.begin(); it != p.end(); it ++) {
            ofEnableAlphaBlending();
            ofSetColor(it->cr, it->cg, it->cb, (it->t / 10) * exp(- it->t / 10) * 255 / 0.4);
            ofCircle(it->x, it->y, it->r);
            if (it->ay < it->r / 10) it->ay ++;
            it->y += it->ay;
            it->t ++;
            if (it->t > 100)p.erase(it);
        }
    }
}

//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){	
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;	

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
		right[i]	= input[i*2+1]*0.5;

		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :) 
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :) 
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
	
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	if( key == 's' ){
		soundStream.start();
	}
	
	if( key == 'e' ){
		soundStream.stop();
	}

    if (key == ' '){
            ofToggleFullscreen();
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 
	if (key == 't'){
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

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

