#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    grabber.initGrabber(640, 480);
    camImage.allocate(grabber.width, grabber.height, OF_IMAGE_COLOR);
    mapImage.loadImage("map.jpg");
    mapImage.allocate(mapImage.width, mapImage.height, OF_IMAGE_COLOR);
    

}

//--------------------------------------------------------------
void testApp::update(){
    grabber.update();
    camImage.grabScreen(0, 0, grabber.width/4, grabber.height/4);
    
    ofPixels pixels = grabber.getPixelsRef();
    
    int sumRed;
    int sumBlue;
    int sumGreen;
    
    // loop through video pixels and create RGB indices
    for (int y=grabber.height-camImage.height; y< grabber
         .height; y++){
        for (int x = 0; x < camImage.width; x++){
            ofColor color = pixels.getColor(x, y);
            int index = y* camImage.width + x;
            reds[index] = color.r;
            greens[index] = color.g;
            blues[index] = color.b;
            
            sumRed += color.r;
            sumGreen += color.g;
            sumBlue += color.b;
        }
    }
    
    ofPixels camPix = camImage.getPixelsRef();
    
    // Get the average pixel color from the bottom corner of video image
    ofColor avgColor;
    avgColor.r = sumRed/(camImage.width*camImage.height);
    avgColor.g = sumGreen/(camImage.width*camImage.height);
    avgColor.b = sumBlue/(camImage.width*camImage.height);
    
    for (int y=0; y< camImage.height; y++){
        for (int x = 0; x < camImage.width; x++){
         
            camPix.setColor(x, y, avgColor);
        }
    }
    camImage.setFromPixels(camPix);
    
    int avgSumColor = avgColor.r + avgColor.g + avgColor.b;
    
    ofLog() << "average color" << avgSumColor;
    
    if (avgSumColor > 600){
        displayMap = true;
    } else {
        displayMap = false;
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    if (DEBUG){
        camImage.draw(grabber.width, grabber.height);
    }
    grabber.draw(grabber.width,0, -grabber.width, grabber.height);
    
    ofNoFill();
    ofSetLineWidth(3);
    ofRect(grabber.width - camImage.width, grabber.height - camImage.height, camImage.width, camImage.height);
    ofDrawBitmapString("Place Ticket Here", grabber.width-camImage.width + 10, grabber.height-camImage.height + 60);
    
    if (displayMap){
        mapImage.draw(0, 0);
    }

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}