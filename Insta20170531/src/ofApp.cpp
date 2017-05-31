#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(30);
	ofBackground(255);
	ofSetWindowTitle("Box");

	int span = 70;
	for (int x = -ofGetWidth() / 2; x < ofGetWidth() / 2; x += span) {
		for (int y = -ofGetHeight() / 2; y < ofGetHeight() / 2; y += span) {
			for (int z = -ofGetWidth() / 2; z < ofGetWidth() / 2; z += span) {
				Particle p = Particle(x, y, z);
				this->particles.push_back(p);
			}
		}
	}

	this->noise_x = ofRandom(10);
	this->noise_y = ofRandom(10);
	this->noise_z = ofRandom(10);
}

//--------------------------------------------------------------
void ofApp::update(){
	
	this->light.setPosition(this->cam.getPosition());

	this->hate_x = ofGetWidth();
	this->hate_y = ofGetHeight();
	this->hate_z = ofGetWidth();

	//this->hate_x = ofMap(ofNoise(noise_x), 0, 1, -ofGetWidth(), ofGetWidth());
	//this->hate_y = ofMap(ofNoise(noise_y), 0, 1, -ofGetHeight(), ofGetHeight());
	//this->hate_z = ofMap(ofNoise(noise_z), 0, 1, -ofGetWidth(), ofGetWidth());
	//
	//this->noise_x += 0.005;
	//this->noise_y += 0.005;
	//this->noise_z += 0.005;

	//for (Particle& p : this->particles) {
	//	p.escape(ofVec3f(this->hate_x, this->hate_y, this->hate_z));
	//	p.update();
	//}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofEnableDepthTest();
	ofEnableLighting();
	this->light.enable();

	cam.begin();

	float pow = 800;

	Leap::Frame frame = leap.frame();
	Leap::HandList hands = frame.hands();
	for (int i = 0; i < hands.count(); i++) {
		if (hands[i].isRight()) {
			//this->drawHand(hands[i]);
			this->hate_x = hands[i].palmPosition().x * 2;
			this->hate_y = hands[i].palmPosition().y - ofGetHeight() / 2;
			this->hate_z = hands[i].palmPosition().z * 2;
			pow *= 1 - hands[i].pinchStrength();
		}
	}


	for (Particle& p : this->particles) {
		p.escape(ofVec3f(this->hate_x, this->hate_y, this->hate_z), pow);
		p.update();
		p.draw();
	}

	ofSetColor(0);
	//ofSphere(ofVec3f(this->hate_x, this->hate_y, this->hate_z), 30);

	cam.end();
}

//--------------------------------------------------------------
void ofApp::drawHand(Leap::Hand hand) {
	Leap::FingerList fingers = hand.fingers();
	for (int j = 0; j < fingers.count(); j++) {
		this->drawFinger(fingers[j]);
	}

	ofPushMatrix();
	ofVec3f palm_point = ofVec3f(hand.palmPosition().x, hand.palmPosition().y - ofGetHeight() / 2, hand.palmPosition().z);
	ofTranslate(palm_point);
	ofSphere(10);
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::drawFinger(Leap::Finger finger) {

	ofVec3f tip_point = ofVec3f(finger.tipPosition().x, finger.tipPosition().y - ofGetHeight() / 2, finger.tipPosition().z);
	ofPushMatrix();
	ofTranslate(tip_point);
	ofSphere(5);
	ofPopMatrix();

	ofVec3f base_point = ofVec3f(tip_point.x + finger.direction().x * finger.length(),// * -1,
		tip_point.y + finger.direction().y * finger.length() - 1,
		tip_point.z + finger.direction().z * finger.length() - 1);
	ofPushMatrix();
	ofTranslate(base_point);
	ofSphere(5);
	ofPopMatrix();

	ofLine(tip_point, base_point);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
