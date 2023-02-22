#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	
	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;
	modeVal = ogMode;

	updateTracker = true;
	keyRecord = false; 
	
	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 

	resetParticles();

}

//--------------------------------------------------------------
void ofApp::resetParticles(){

	//these are the attraction points used in the fourth demo 
	attractPoints.clear();
	for(int i = 0; i < 4; i++){
		attractPoints.push_back( glm::vec3( ofMap(i, 0, 4, 100, ofGetWidth()-100) , ofRandom(100, ofGetHeight()-100) , 0) );
	}
	
	attractPointsWithMovement = attractPoints;
	
	for(unsigned int i = 0; i < p.size(); i++){
		p[i].setMode(currentMode);		
		p[i].setAttractPoints(&attractPointsWithMovement);;
		p[i].reset();
		p[i].setKey(modeVal);
	}	

	drawParticles.clear();

	color.set(ofRandom(255), ofRandom(255), ofRandom(255));
}

//--------------------------------------------------------------
void ofApp::update(){
	if (updateTracker){
		
		for(unsigned int i = 0; i < p.size(); i++){
			p[i].setMode(currentMode);
			p[i].update();
			p[i].setKey(modeVal);	
		} 

		if (currentMode == PARTICLE_MODE_DRAW){
			for (unsigned int i = 0; i < drawParticles.size(); i++){
				drawParticles[i].update();
			}
		}

	//lets add a bit of movement to the attract points
	for(unsigned int i = 0; i < attractPointsWithMovement.size(); i++){
		attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
		attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
	}	

	}

	if (keyReplay){
		count++;

		if(count != 100){ 
			notKeyPress = false;
		}
		
		if (count == 100 && RecordKey <= record.size()){
			notKeyPress = true;
			keyPressed(record[RecordKey]);
			RecordKey++;

			endReplay--;

			count = 0;
		}
	}

	if (drawParticles.size() > 1500){
		drawParticles.erase(drawParticles.begin());
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackgroundGradient(ofColor(21,3,103), ofColor(0,0,0));

	if (!modeDraw){
		for(unsigned int i = 0; i < p.size(); i++){
			p[i].draw();
		}
	}
	ofSetColor(190);
	if( currentMode == PARTICLE_MODE_NEAREST_POINTS ){
		for(unsigned int i = 0; i < attractPoints.size(); i++){
			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}

	if (!keyRecord || stopReplay == true){
		ofSetColor(230);
		ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-5 to change mode.", 10, 20);
	}
	
	else if (keyRecord){
		ofSetColor(255, 0, 0);
		ofDrawCircle(ofGetWidth() - 35, 35, 15);
		ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-5 to change mode.", 10, 20);
	}
	if (keyReplay){
		ofSetColor(0, 0, 255);
		ofDrawTriangle(ofGetWidth() - (40 + 70), 50, ofGetWidth() - (40 + 70), 10, ofGetWidth() - 70, 30);
		ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-5 to change mode.", 10, 20);
	}

	if (currentMode == PARTICLE_MODE_DRAW){
		if (!keyReplay){
			for (unsigned int i = 0; i < drawParticles.size(); i++){
				drawParticles[i].draw();
				ofSetColor(color);
			
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (notKeyPress){
		if( key == '1'){
			currentMode = PARTICLE_MODE_ATTRACT;
			currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse"; 		
		}
		if( key == '2'){
			currentMode = PARTICLE_MODE_REPEL;
			currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse"; 				
		}
		if( key == '3'){
			currentMode = PARTICLE_MODE_NEAREST_POINTS;
			currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS:"; 						
		}
		if( key == '4'){
			currentMode = PARTICLE_MODE_NOISE;
			currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation"; 						
			resetParticles();
		}	
		if (key == '5'){
			currentMode = 	PARTICLE_MODE_DRAW;
			currentModeStr = "5 - PARTICLE_MODE_DRAW: press and drag mouse arround to create particles"; 	
			drawParticles.clear();	
			modeDraw = true;				
		}	

		if (currentMode != PARTICLE_MODE_DRAW){
			modeDraw = false;
		}

		if( key == ' ' ){
			resetParticles();
		}

		if (key == 'A' || key == 'a'){
			updateTracker = !updateTracker; 
			currentModeStr = "PAUSE_MODE: Press A or a in order to pause the program, press again to unpause"; 

		}

		if(key == 'I' || key == 'i'){
			currentModeStr = "Particle Size Increased "; 
			for (unsigned int i=0; i<p.size(); i++){
				p[i].increaseSize(); 
			}
			for (unsigned int i = 0; i < drawParticles.size(); i++){
				drawParticles[i].increaseSize();
			}
		}

		if(key == 'D' || key == 'd'){
			currentModeStr = "Particle Size Decreased "; 
			for (unsigned int i=0; i<p.size(); i++){
				p[i].decreaseSize(); 
			}
			for (unsigned int i = 0; i < drawParticles.size(); i++){
				drawParticles[i].decreaseSize();
			}
		}

		if (key == 'F' || key == 'f'){  
			currentModeStr = "Particle Velocity Increase"; 
			for (unsigned int i=0; i<p.size(); i++){
				p[i].increaseVelocity(); 
			}
			for (unsigned int i = 0; i < drawParticles.size(); i++){
				drawParticles[i].increaseVelocity();
			}
		}

		if (key == 'S' || key == 's'){  
			currentModeStr = "Particle Velocity Decrease"; 
			for (unsigned int i=0; i<p.size(); i++){
				p[i].decreaseVelocity(); 
			}
			for (unsigned int i = 0; i < drawParticles.size(); i++){
				drawParticles[i].decreaseVelocity();
			}
		}

		// Record is not available for mode 5: draw particles.
		if (key == 'R' || key == 'r'){  

			if (stopReplay){
				on_offRecording = 0;
			}

			on_offRecording++;

			if (on_offRecording == 1){
				stopReplay = false;
				count = 0;
				RecordKey = 1;
				currentModeStr = "Currently Recording: Press R or r again in order to stop de recording.";
				keyRecord = true;
				keyReplay = false;
				if (keyRecord == true){
					record.clear();
				}
			}

			if (on_offRecording == 2){
				keyRecord = false;
				currentModeStr = "Recording Endded";
				on_offRecording = 0;
			}
		}

		if (key == 'P' || key == 'p'){
			resetParticles();
			updateTracker = true;
			stopReplay = false;
			keyRecord = false;
			currentModeStr = "Currently Replaying: Press C or c in order to stop de playback.";
			keyReplay = true;
		}

		if (keyRecord){ 
			record.push_back(key);
			endReplay = record.size();
		}
	}

	// Doesn't playback if record vector is empty and it cancels playback when all the keys in record are pressed.
	if (key == 'C' || key == 'c' || (keyReplay && record.empty()) || (keyReplay && endReplay == 1) ){ 
		// stops playback
		record.clear();
		updateTracker = true;
		keyReplay = false;
		stopReplay = true;
		currentModeStr = "Playback Stopped";
		resetParticles();
		notKeyPress = true;
	}
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

	if (currentMode == PARTICLE_MODE_DRAW){
		Particle particles(mouseX, mouseY);
		drawParticles.push_back(particles);
	}
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
