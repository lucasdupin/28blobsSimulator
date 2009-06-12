#include "blob.h"

Blob::Blob(){
	size = 20;
	dragging = false;	
	dragged = true;
}

void Blob::draw(){
	ofSetColor(100,0,130);
	ofCircle(position.x, position.y, size/2);
	
	ofSetColor(255,255,255);
	ofDrawBitmapString(ofToString(id, 0), position.x, position.y);
}