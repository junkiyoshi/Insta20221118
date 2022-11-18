#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
	//ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(19);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int span = 20;
	int size = span * 0.75;

	vector<ofColor> color_list = { ofColor(255, 128, 0), ofColor(128, 255, 0), ofColor(0, 128, 255) };

	for (int i = 0; i < color_list.size(); i++) {

		auto color = color_list[i];
		auto noise_seed = ofRandom(1000);

		for (int x = span * 1.5 - ofGetWidth() * 0.5; x <= ofGetWidth() - span * 1.5 - ofGetWidth() * 0.5; x += span) {

			auto noise_y = ofMap(ofNoise(noise_seed, x * 0.003 + ofGetFrameNum() * 0.0025), 0, 1, ofGetHeight() * -0.5, ofGetHeight() * 0.5);

			for (int y = span * 1.5 - ofGetHeight() * 0.5; y <= ofGetWidth() - span * 1.5 - ofGetHeight() * 0.5; y += span) {

				auto gap_y = abs(noise_y - y);
				auto box_size = 0;
				if (gap_y <= span * 4) {

					box_size = ofMap(gap_y, 0, span * 4, size * 2, 0);
					box_size = box_size > size ? size : box_size;
				}

				if (box_size > 0) {

					ofFill();
					ofSetColor(color, 64);
					ofDrawBox(glm::vec3(x, y, 0), box_size);

					ofNoFill();
					ofSetColor(color);
					ofDrawBox(glm::vec3(x, y, 0), box_size);

					
				}
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}