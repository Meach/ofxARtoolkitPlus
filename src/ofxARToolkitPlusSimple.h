#pragma once

#include "ofMain.h"
#include <ar.h>
#include "ARToolKitPlus/TrackerSingleMarker.h"

class ofxARToolkitPlusSimple
{
public:
	ofxARToolkitPlusSimple();
	~ofxARToolkitPlusSimple();

	/* Setup ARToolKitPlus with the width and height of the image */
    void setup(int w, int h, string camParamFile);


	/* Load additional .patt marker file */
	int loadPatt(string filename);
	/* Free loaded .pakk marker */
	int freePatt(int patno);


	///////////////////////////////////////////
	// UPDATE
	///////////////////////////////////////////
	/* Find the marker and get back the confidence */
	vector<int> update(unsigned char *pixels);

	///////////////////////////////////////////
	// DRAW
	///////////////////////////////////////////
	/* Draw the marker center, outline, and id at the origin */
	//void draw();
	/* Draw the marker center, outline, and id at the given position */
	//void draw(int x, int y);
	/* Draw the marker center, outline, and id at the given position with the given size */
	//void draw(int x, int y, int width, int height);


	///////////////////////////////////////////
	// MARKER INFO
	///////////////////////////////////////////
	/* Return the number of detected markers */
	//int getNumDetectedMarkers();
	/* Get the index of the marker if found, else return -1 */
	//int getMarkerIndex(int markerID);
	/* Get the marker ID of the given index - returns -1 if out of range */
	//int getMarkerID(int markerIndex);

    float getConfidence(int pattId);


	///////////////////////////////////////////
	// SETTINGS
	///////////////////////////////////////////
	/* Set the threshold manually */
	void setThreshold(int threshold);
	/* Enables usage of arDetectMarkerLite. Otherwise arDetectMarker is used */
	void setUseDetectLite(bool doUse);

	///////////////////////////////////////////
	// 2D GEOMETRY
	///////////////////////////////////////////
	/* Return the center of the detected marker in screen coordinates */
	//ofPoint getDetectedMarkerCenter(int markerIndex);

private:
	ARToolKitPlus::TrackerSingleMarker *tracker;


protected:

	int width, height;
	bool useBCH;
};

