#include "ofxARToolkitPlusSimple.h"



ofxARToolkitPlusSimple::ofxARToolkitPlusSimple()
{
}


ofxARToolkitPlusSimple::~ofxARToolkitPlusSimple()
{
}


//--------------------------------------------------
void ofxARToolkitPlusSimple::setup(int w, int h, string camParamFile, string markerFile)
{
	width = w;
	height = h;
	useBCH = false;
	
	tracker = new ARToolKitPlus::TrackerSingleMarker(width, height, 8, 16, 16, 16, 8);
	
	
	tracker->setPixelFormat(ARToolKitPlus::PIXEL_FORMAT_LUM);

	tracker->setImageProcessingMode(ARToolKitPlus::IMAGE_FULL_RES);


	if (!tracker->init(ofToDataPath("Logitech_Notebook_Pro.cal").c_str(), 1.0f, 1000.0f)) // load MATLAB file
	{
		ofLogError("ofxARToolkitPlusSimple") << "init() failed";
		delete tracker;
		
		return;
	}

	// define size of the marker
	//tracker->setPatternWidth(80);

	// the marker in the BCH test image has a thin border...
	tracker->setBorderWidth(useBCH ? 0.125f : 0.250f);

	// set a threshold. alternatively we could also activate automatic thresholding
	tracker->setThreshold(85);

	// let's use lookup-table undistortion for high-speed
	// note: LUT only works with images up to 1024x1024
	tracker->setUndistortionMode(ARToolKitPlus::UNDIST_LUT);

	// RPP is more robust than ARToolKit's standard pose estimator
	tracker->setPoseEstimator(ARToolKitPlus::POSE_ESTIMATOR_RPP);

	// switch to simple ID based markers
	// use the tool in tools/IdPatGen to generate markers
	tracker->setMarkerMode(useBCH ? ARToolKitPlus::MARKER_ID_BCH : ARToolKitPlus::MARKER_ID_SIMPLE);
	tracker->setMarkerMode(ARToolKitPlus::MARKER_TEMPLATE);
	tracker->setPatternWidth(80);
	/*int pattId = tracker->addPattern((char *)ofToDataPath("hiro.patt").c_str());
	pattId = tracker->addPattern((char *)ofToDataPath("kanji.patt").c_str());
	pattId = tracker->addPattern((char *)ofToDataPath("M1.patt").c_str());

	ofLogVerbose("ofxARToolkitPlusSimple") << "patno = " << pattId;*/
}

//--------------------------------------------------
int ofxARToolkitPlusSimple::loadPatt(string filename)
{
	
	//char *patt_name = "data/hiro.patt";
	char * writable = new char[filename.size() + 1];
	std::copy(filename.begin(), filename.end(), writable);
	writable[filename.size()] = '\0'; // don't forget the terminating 0

	int pattId = tracker->arLoadPatt(writable);
	// don't forget to free the string after finished using it
	delete[] writable;

	ofLogVerbose("ofxARToolkitPlusSimple") << "Loading patt file \"" << filename << "\", id=" << pattId;


	// Return result
	return pattId;
}

//--------------------------------------------------
vector<int> ofxARToolkitPlusSimple::update(unsigned char *pixels) {
	/*vector<int> dectected = tracker->calc(pixels);
	tracker->selectBestMarkerByCf();
	return dectected;*/
	return tracker->calc(pixels);
}

//--------------------------------------------------
float ofxARToolkitPlusSimple::getConfidence()
{
	return tracker->getConfidence();
}


//--------------------------------------------------
void ofxARToolkitPlusSimple::setThreshold(int threshold) {
	tracker->activateAutoThreshold(false);
	tracker->setThreshold(threshold);
}