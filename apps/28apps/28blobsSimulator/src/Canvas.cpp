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
			
			sendOSC("/update", b->id, b->position.x, b->position.y);
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
	sendOSC("/create", newB.id, newB.position.x, newB.position.y);

}

//--------------------------------------------------------------
void Canvas::mouseReleased(int x, int y, int button){
	x-= position.x;
	y-= position.y;
	
	for (vector<Blob>::iterator b = blobs.begin(); b != blobs.end(); b++) {
		
		if(b->dragging && !b->dragged){
			blobs.erase(b--);
		} else {
			b->dragging = false;
			b->dragged = false;
		}
	}
}

void Canvas::blobOn( int x, int y, int id, int order ) {
    sendOSC("/create", id, x, y);
}
void Canvas::blobMoved( int x, int y, int id, int order) {
    sendOSC("/update", id, x, y);	
}
void Canvas::blobOff( int x, int y, int id, int order ) {
    sendOSC("/destroy", id, x, y);
}