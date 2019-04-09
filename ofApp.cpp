#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	int span = 144;
	int len = 120;
	bool flag = true;
	for (int location_y = span * 0.5; location_y < ofGetHeight(); location_y += span) {

		for (int location_x = span * 0.5; location_x < ofGetWidth(); location_x += span) {

			ofPushMatrix();
			ofTranslate(location_x, location_y);

			float noise_seed = ofRandom(100);
			vector<glm::vec2> top, noise, bottom;
			for (int x = -len * 0.5; x <= len * 0.5; x += 1) {

				if (ofRandom(100) < 3 && bottom.size() > 30 && x < len * 0.4) {

					this->draw_shape(bottom, noise);
				}

				noise.push_back(glm::vec2(x, ofMap(ofNoise(location_y, (location_x + x) * 0.005, ofGetFrameNum() * 0.005), 0, 1, -len * 0.35, len * 0.35) + 1));
				bottom.push_back(glm::vec2(x, len * 0.5));
			}

			if (bottom.size() > 0) {

				this->draw_shape(bottom, noise);
			}

			for (int x = -len * 0.5; x <= len * 0.5; x += 1) {

				if (ofRandom(100) < 3 && top.size() > 30 && x < len * 0.4) {

					this->draw_shape(top, noise);
				}

				noise.push_back(glm::vec2(x, ofMap(ofNoise(location_y , (location_x + x) * 0.005, ofGetFrameNum() * 0.005), 0, 1, -len * 0.35, len * 0.35) - 1));
				top.push_back(glm::vec2(x, len * -0.5));
			}

			if (top.size() > 0) {

				this->draw_shape(top, noise);
			}

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw_shape(vector<glm::vec2>& side, vector<glm::vec2>& noise){

	ofColor color;
	color.setHsb(ofRandom(255), 180, 235);
	ofSetColor(color);

	std::reverse(noise.begin(), noise.end());

	ofBeginShape();
	ofVertices(side);
	ofVertices(noise);
	ofEndShape(true);

	side.clear();
	noise.clear();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}