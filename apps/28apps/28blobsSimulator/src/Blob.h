#ifndef _BLOB_
#define _BLOB_

#include "ofMain.h"

class Blob {
	
public:
	
	Blob();
	
	int id;
	ofPoint position;	
	int size;
	bool dragging;
	bool dragged;
	
	void draw();
};

#endif