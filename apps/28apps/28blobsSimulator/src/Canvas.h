#ifndef _CANVAS
#define _CANVAS

#include "ofMain.h"
#include "settings.h"
#include "ofxCvBlobTracker.h"
#include "ofxCvMain.h"
#include "blob.h"
#include "utils.h"

class Canvas: public ofxCvBlobListener{
	
public:
	void virtual setup();
	void virtual update();
	void virtual draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	
	//Blob Tracking
	void blobOn( int x, int y, int id, int order );
    void blobMoved( int x, int y, int id, int order );
    void blobOff( int x, int y, int id, int order );
	
	//Transformation
	int width;
	int height;
	ofPoint position;
	
	std::vector<Blob> blobs;
	
	//Attributes
	ofColor color;
	
	int blobId;

};

#endif