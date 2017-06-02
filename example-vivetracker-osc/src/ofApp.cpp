#include "ofMain.h"
#include "ofxViveTrackerOSC.h"

class ofApp : public ofBaseApp{
	ofxViveTracker::OSC vt;
	ofEasyCam cam;
	ofCamera vivecam;
	bool b_use_vivecam = false;
public:
    void setup()
    {
        ofSetVerticalSync(true);
        ofSetFrameRate(60);
        
		vt.setup(5005);
    }
    
    void update()
    {
		vt.update();

		auto gt = vt.getGenericTrackers();
		if (gt.size()) {
			vivecam.setTransformMatrix(gt.front().pose);
		}
    }
    
    void draw()
    {
        ofClear(0);
		auto& c = b_use_vivecam ? vivecam : cam;

		c.begin();
		ofPushMatrix();
		ofRotateZ(90);
		ofDrawGridPlane(50);
		ofPopMatrix();
		vt.debugDraw();
		ofDrawAxis(100);
		c.end();
    }
    
    void keyPressed(int key)
    {
        if (key == 'f') {
            ofToggleFullscreen();
        }
		if (key == 'v') {
			b_use_vivecam = !b_use_vivecam;
		}
	}
    
    void keyReleased(int key) {}
    void mouseMoved(int x, int y ) {}
    void mouseDragged(int x, int y, int button) {}
    void mousePressed(int x, int y, int button) {}
    void mouseReleased(int x, int y, int button) {}
    void windowResized(int w, int h) {}
    void dragEvent(ofDragInfo dragInfo) {}
    void gotMessage(ofMessage msg) {}
    
};

//========================================================================
int main( ){
    ofSetupOpenGL(1280,720,OF_WINDOW);            // <-------- setup the GL context
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
    
}
