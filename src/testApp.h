#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"

class testApp : public ofBaseApp{
private:
    
    struct P {
        P(int x_, int y_, int cr_, int cg_, int cb_, float r_) {
            x = x_;
            y = y_;
            t = 0;
            ay = 0;
            cr = cr_;
            cg = cg_;
            cb = cb_;
            r = r_;
        }
        int x;
        int y;
        int cr;
        int cg;
        int cb;
        float t;
        float ay;
        float r;
    };
    
    // 周波数分解
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
				
		void audioIn(float * input, int bufferSize, int nChannels); 
	
		vector <float> left;
		vector <float> right;
		vector <float> volHistory;
    
    list <P> p;
		
		int 	bufferCounter;
		int 	drawCounter;
		
		float smoothedVol;
		float scaledVol;
		
		ofSoundStream soundStream;
};

#endif	

