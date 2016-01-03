#include "ofxPiMapper.h"

ofxPiMapper::ofxPiMapper(){
	bShowInfo = false;
	isSetUp = false;
	_gui = new ofx::piMapper::SurfaceManagerGui();
	_cmdManager = new ofx::piMapper::CmdManager();
	_mediaServer = new ofx::piMapper::MediaServer();
	_info = new ofx::piMapper::Info();
}

void ofxPiMapper::setup(){
	ofLogNotice("ofxPiMapper") << "Setting up...";

	surfaceManager.setMediaServer(_mediaServer);
	_gui->setMediaServer(_mediaServer);
	_gui->setCmdManager(_cmdManager);

	if(!loadXmlSettings(PIMAPPER_USER_SURFACES_XML_FILE)){
		ofLogWarning("ofxPiMapper::setup()") << "Failed to load user settings, go with default" << endl;
		if(!loadXmlSettings(PIMAPPER_DEF_SURFACES_XML_FILE)){
			ofLogError("ofxPiMapper::setup()") << "Failed to load default settings, exit" << endl;
			ofExit(EXIT_FAILURE);
		}
	}

	_gui->setSurfaceManager(&surfaceManager);
	isSetUp = true;
	ofLogNotice("ofxPiMapper") << "Done setting up";
	_application = new ofx::piMapper::Application(this);
}

void ofxPiMapper::draw(){
	if(!isSetUp){
		return;
	}
	_gui->draw();
	_application->draw();
	_info->draw();
}

void ofxPiMapper::registerFboSource(ofx::piMapper::FboSource & fboSource){
	_mediaServer->addFboSource(fboSource);
}

bool ofxPiMapper::loadXmlSettings(string fileName){
	if(!ofFile::doesFileExist(fileName)){
		ofLogError("ofxPiMapper::loadXmlSettings()") << fileName << " does not exist";
		return false;
	}
	if(!surfaceManager.loadXmlSettings(fileName)){
		ofLogError("ofxPiMapper::loadXmlSettings()") << "Failed to load " << fileName << endl;
		return false;
	}
	return true;
}

ofx::piMapper::CmdManager * ofxPiMapper::getCmdManager(){
	return _cmdManager;
}

ofx::piMapper::SurfaceManagerGui * ofxPiMapper::getGui(){
	return _gui;
}

ofx::piMapper::SurfaceManager & ofxPiMapper::getSurfaceManager(){
	return surfaceManager;
}

ofx::piMapper::Info * ofxPiMapper::getInfo(){
	return _info;
}