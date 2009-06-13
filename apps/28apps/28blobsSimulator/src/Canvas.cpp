/*
 Copyright (c) 2009 sala28 - Lucas Dupin
 
 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without
 restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following
 conditions:
 
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 */

#include "Canvas.h"

void Canvas::setup(){
	//My size
	width = settings.getValue("teBlobs:canvas:width", 400);
	height = settings.getValue("teBlobs:canvas:height", 300);
	
	//My color
	color.r = settings.getValue("teBlobs:application:canvasColor:r",30);
	color.g = settings.getValue("teBlobs:application:canvasColor:g",30);
	color.b = settings.getValue("teBlobs:application:canvasColor:b",30);
	
	blobId = 0;
}

void Canvas::draw(){
	
	glPushMatrix();
	glTranslated(position.x, position.y, 0);
	
	//Black background
	ofFill();
	ofSetColor(0,0,0);
	ofRect(0,0, width, height);
	
	
	for (vector<Blob>::iterator b = blobs.begin(); b != blobs.end(); b++) {

		b->draw();
		//ofDrawBitmapString(ofToString(b->id), b->position.x-5, b->position.y-5);
	}
	ofDisableAlphaBlending();
	
	//Drawing the canvas limit
	ofSetColor(color.r, color.g, color.b);
	ofNoFill();
	ofRect(0,0, width, height);
		
	glPopMatrix();
}
void Canvas::update(){
	
}

//--------------------------------------------------------------
void Canvas::keyPressed(int key){
}

//--------------------------------------------------------------
void Canvas::keyReleased(int key){
}

//--------------------------------------------------------------
void Canvas::mouseMoved(int x, int y ){
	x-= position.x;
	y-= position.y;
}

//--------------------------------------------------------------
void Canvas::mouseDragged(int x, int y, int button){
	for (vector<Blob>::iterator b = blobs.begin(); b != blobs.end(); b++) {
		if(b->dragging){
		    b->position.x = x - position.x;
			b->position.y = y - position.y;
			b->dragged = true;
			
			sendOSC("/update", b->id, b->position.x/width, b->position.y/height);
		}
	}
}

//--------------------------------------------------------------
void Canvas::mousePressed(int x, int y, int button){
	x-= position.x;
	y-= position.y;
	
	for (vector<Blob>::iterator b = blobs.begin(); b != blobs.end(); b++) {
		if(hitRect(ofPoint(x,y), ofRectangle(b->position.x-b->size/2,b->position.y-b->size/2,b->size,b->size))){
		   b->dragging = true;			
			return;
		}
	}
	
	
	//Not hitting anyone, clicked to create a blob
	Blob newB;
	newB.position.set(x,y);
	newB.id = blobId++;
	newB.dragging=true;
	blobs.push_back(newB);
	sendOSC("/create", newB.id, newB.position.x/width, newB.position.y/height);

}

//--------------------------------------------------------------
void Canvas::mouseReleased(int x, int y, int button){
	x-= position.x;
	y-= position.y;
	
	for (vector<Blob>::iterator b = blobs.begin(); b != blobs.end(); b++) {
		
		if(b->dragging && !b->dragged){
			sendOSC("/destroy", b->id, b->position.x/width, b->position.y/height);
			blobs.erase(b--);
		} else {
			b->dragging = false;
			b->dragged = false;
		}
	}
}