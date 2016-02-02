#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxARtoolkitPlus.h"

// Uncomment this to use a camera instead of a video file
//#define CAMERA_CONNECTED

class ofApp : public ofBaseApp{
    
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
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    // Size of the image
    int width, height;
    
    // Use either camera or a video file
#ifdef CAMERA_CONNECTED
    ofVideoGrabber vidGrabber;
#else
    ofVideoPlayer vidPlayer;
#endif
    
    // ARToolKitPlus class
    ofxARToolkitPlus artk;
    int threshold;
    
    // OpenCV images
    ofxCvColorImage colorImage;
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage	grayThres;
    
    // Image to distort on to the marker
    ofImage displayImage;
    // The four corners of the image
    vector<ofPoint> displayImageCorners;
};
