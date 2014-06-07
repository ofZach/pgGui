//#include "ofApp.h"
//#include "Utils.h"
//#include <stdio.h>
//
//
//
//
//
////--------------------------------------------------------------
//void ofApp::setup(){
//    //ofSetLogLevel(OF_LOG_VERBOSE);
//	project = NULL;
//
//	
//	//setOFRoot(getOFRootFromConfig());
//
//	setupDrawableOFPath();
//
//	int targ = ofGetTargetPlatform();
//	//plat = OF_TARGET_IPHONE;
//
//    setupForTarget(targ);
//    if(projectPath!="" || buildAllExamples){
//    	for(int i = 0; i < (int)targetsToMake.size(); i++){
//			setupForTarget(targetsToMake[i]);
//			if(buildAllExamples){
//				generateExamples();
//			}else{
//				project->setup(target);
//				project->create(projectPath);
//				vector < string > addons;
//				parseAddonsDotMake(project->getPath() + "addons.make", addons);
//				for (int i = 0; i < (int)addons.size(); i++){
//					ofAddon addon;
//					addon.fromFS(ofFilePath::join(ofFilePath::join(getOFRoot(), "addons"), addons[i]),target);
//					project->addAddon(addon);
//				}
//				project->save(false);
//			}
//    	}
//        std::exit(0);
//    }
//
//	std::exit(0);
//}
//
//void ofApp::setupForTarget(int targ){
//
//    if(project){
//		delete project;
//	}
//
//    switch(targ){
//        case OF_TARGET_OSX:
//            project = new xcodeProject;
//            target = "osx";
//            break;
//        case OF_TARGET_WINGCC:
//            project = new CBWinProject;
//            target = "win_cb";
//            break;
//        case OF_TARGET_WINVS:
//            project = new visualStudioProject;
//            target = "vs";
//            break;
//        case OF_TARGET_IPHONE:
//            project = new xcodeProject;
//            target = "ios";
//            break;
//        case OF_TARGET_ANDROID:
//            break;
//        case OF_TARGET_LINUX:
//            project = new CBLinuxProject;
//            target = "linux";
//            break;
//        case OF_TARGET_LINUX64:
//            project = new CBLinuxProject;
//            target = "linux64";
//            break;
//        case OF_TARGET_LINUXARMV6L:
//            project = new CBLinuxProject;
//            target = "linuxarmv6l";
//            break;
//        case OF_TARGET_LINUXARMV7L:
//            project = new CBLinuxProject;
//            target = "linuxarmv7l";
//            break;
//    }
//}
//
//
//
//void ofApp::generateExamples(){
//    ofDirectory dir;
//    string examplesPath = ofFilePath::join(getOFRoot(),"examples");
//
//	ofLogNotice() << "Generating examples (from: " << examplesPath << ")";
//
//    dir.listDir(examplesPath);
//
//    for (int i = 0; i < (int)dir.size(); i++){
//
//        // don't check subdirectories that aren't directories! (eg., .gitignore etc)
//        if(!dir.getFile(i).isDirectory()) continue;
//
//		if( target == "ios" ){
//			if( dir.getName(i) != "ios" ) continue;
//		}else{
//			if (dir.getName(i) == "android" || dir.getName(i) == "ios") continue;
//        }
//
//        ofDirectory subdir;
//        string examplesPath = dir.getPath(i);
//
//		ofLogNotice() << "Generating examples in folder: " << examplesPath;
//
//        subdir.listDir(examplesPath);
//
//        for (int j = 0; j < (int)subdir.size(); j++){
//
//            // don't create projects that aren't directories! (eg., .gitkeep etc)
//            if(!subdir.getFile(j).isDirectory()) continue;
//
//			ofLogNotice() << "------------------------------------------------";
//			ofLogNotice() << "Generating example: " << subdir.getPath(j);
//			ofLogNotice() << "------------------------------------------------";
//
//            project->setup(target);
//            project->create(subdir.getPath(j));
//            vector < string > addons;
//            parseAddonsDotMake(project->getPath() + "addons.make", addons);
//            for (int i = 0; i < (int)addons.size(); i++){
//                ofAddon addon;
//                addon.pathToOF = getOFRelPath(subdir.getPath(j));
//                addon.fromFS(ofFilePath::join(ofFilePath::join(getOFRoot(), "addons"), addons[i]),target);
//                project->addAddon(addon);
//            }
//            project->save(false);
//
//        }
//    }
//    ofLogNotice() << " ";
//    ofLogNotice() << "Finished generating examples for " << target;
//}
////
////ofFileDialogResult ofApp::makeNewProjectViaDialog(){
////
////
////
////}
////
////ofFileDialogResult ofApp::updateProjectViaDialog(){
////
////
////
////}
//
////void ofApp::createProjectPressed(){
////	makeNewProjectViaDialog();
////}
////
////void ofApp::updateProjectPressed(){
////	updateProjectViaDialog();
////}
//
////void ofApp::createAndOpenPressed(){
////	ofFileDialogResult res = makeNewProjectViaDialog();
////	if(res.bSuccess){
////		#ifdef TARGET_LINUX
////			system(("/usr/bin/codeblocks " + ofFilePath::join(res.filePath, res.fileName+".workspace ") + "&").c_str());
////		#elif defined(TARGET_OSX)
////			system(("open " + ofFilePath::join(res.filePath, res.fileName+".xcodeproj ") + "&").c_str());
////		#elif defined(TARGET_WIN32)
////			system(("open " + ofFilePath::join(res.filePath, res.fileName+".workspace ") + "&").c_str());
////		#endif
////	}
////}
//
//
//
////--------------------------------------------------------------
//void ofApp::update(){
//
//
//
//}
//
////--------------------------------------------------------------
//void ofApp::draw(){
//
//}
//
////--------------------------------------------------------------
//void ofApp::keyPressed(int key){
//
//    
//
//
//}
//
////--------------------------------------------------------------
//void ofApp::keyReleased(int key){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseMoved(int x, int y ){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseDragged(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mousePressed(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::mouseReleased(int x, int y, int button){
//
//}
//
////--------------------------------------------------------------
//void ofApp::windowResized(int w, int h){
//	setupDrawableOFPath();
//}
//
////--------------------------------------------------------------
//void ofApp::gotMessage(ofMessage msg){
//
//}
//
////--------------------------------------------------------------
//void ofApp::dragEvent(ofDragInfo dragInfo){
//
//}
//
////--------------------------------------------------------------
//void ofApp::setupDrawableOFPath(){
//
//
//
//}
