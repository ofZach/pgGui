#include "testApp.h"


// todo:

// better allocation
// button states
// drag bar state
// tool tip dynamic




spacer * tempSpacer;

//--------------------------------------------------------------
void testApp::setup(){

    
    
    font.loadFont("fonts/fgb.ttf", 16);
    mono.loadFont("fonts/LiberationMono-Regular.ttf", 12);
    rg.setBounds( ofRectangle( 50,0, 400,200));
    
    rg.bDrawOutline = false;
    rgTop.setBounds(ofRectangle( 0,0, 400,200));
    rgTop.bDrawOutline = true;
    rgAddons.setBounds(ofRectangle( 0,0, 400,100));
    rgAddons.bDrawOutline = true;

    rg.add(new imageButton("settings", "images/setting.png", margin(0,0,20,340)));
    rgTop.add(new textFieldWithLabel("projectName", "PROJECT NAME", "WHAT", &font, 350, margin(20,25,20,25)));
    rgTop.add(new textFieldWithLabel("projectLocation", "PROJECT LOCATION", "HOW", &font, 350, margin(20,25,20,25)));
    rg.add(&rgTop);
    rg.add(new spacer("space", 400, 30));
    rgAddons.add((new textLabel("addonsLabel", "ADDONS", &font, 300, false))->setMargin(10, 40, 20, 10));
    rgAddons.add((new imageButton("addons", "images/add.png"))->setMargin(10,30,0,0));
    rg.add(&rgAddons);
    rg.add(new spacer("space", 400, 30));
    rg.add(new textLabel("platform", "PLATFORM", &font, 400));
    rg.add(new textLabelToggle("osx", "OSX", &font, false, 0, margin(0,10,10,0)));
    rg.add(new textLabelToggle("linux", "LINUX", &font, false, 0, margin(0,10,10,0)));
    rg.add(new textLabelToggle("wincb", "WIN CB", &font, false, 0, margin(0,10,10,0)));
    rg.add(new textLabelToggle("winvs", "WIN VS2012", &font, false, 0, margin(0,10,10,0)));
    rg.add(new textLabelToggle("armv6", "ARMV6", &font, false, 0, margin(0,10,10,0)));
    rg.add(new textLabelToggle("ios", "IOS", &font, false, 0, margin(0,10,10,0)));
    rg.add(new textLabelToggle("android", "ANDROID", &font, false, 0, margin(0,10,10,0)));
    
    rg.setVisible(true);
    
    settings.add(new spacer("space", 300,30));
    
    settings.add(new textLabel("settingsBack", "< BACK", &font, 0, true));
    
    
    settings.add(new textFieldWithLabel("root", "OPENFRAMEWORKS ROOT", "", &font));
    
    settings.setBounds( ofRectangle( 50,50, 400,200));
    settings.bDrawOutline = false;
    settings.setupLayout();
    settings.setVisible(false);
    
    addons.add((new textLabel("addonsBack", "< BACK", &font, 0, true))->setMargin(20, 0,20,300));
    
    
    ofDirectory dir;
    dir.listDir("../../../../../addons");
    for (int i = 0; i < dir.size(); i++){
        addons.add((new textLabelToggle(dir.getName(i), dir.getName(i), &mono, false, 400))->setMargin(0, 0, 2, 0));
    }

    
    
    addons.setBounds( ofRectangle( 50,0, 400,200));
    addons.bDrawOutline = false;
    addons.setupLayout();
    addons.setVisible(false);
    
    
    rg.setupLayout();
    
    rg.setViewBounds( ofRectangle(0,0,ofGetWidth(), ofGetHeight()-50));
    addons.setViewBounds( ofRectangle(0,0,ofGetWidth(), ofGetHeight()-50));
    
    
}

//--------------------------------------------------------------
void testApp::update(){

    rg.setupLayout();
    settings.setupLayout();
    addons.setupLayout();
    
    rg.update();
    addons.update();
    
    
    //rg.setPosition( ofPoint(mouseX, mouseY));
    
}

//--------------------------------------------------------------
void testApp::draw(){

    //nd.draw();
    
    rg.draw();
    settings.draw();
    addons.draw();
    
    
    ofSetColor(ofColor::lightGoldenRodYellow);
    ofRect( ofRectangle(0,ofGetHeight()-50,ofGetWidth(), 50) );
 
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

    rg.handleMouse( ofPoint(mouseX, mouseY), ofGetMousePressed());
    settings.handleMouse( ofPoint(mouseX, mouseY), ofGetMousePressed());
    addons.handleMouse( ofPoint(mouseX, mouseY), ofGetMousePressed());
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

    
    rg.handleScroll( ofPoint(mouseX, mouseY), ofGetMousePressed());
    addons.handleScroll( ofPoint(mouseX, mouseY), ofGetMousePressed());
    
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    if (rg.bVisible) rg.handleMouse( ofPoint(mouseX, mouseY), ofGetMousePressed());
    else if (settings.bVisible) settings.handleMouse( ofPoint(mouseX, mouseY), ofGetMousePressed());
    else if (addons.bVisible) addons.handleMouse( ofPoint(mouseX, mouseY), ofGetMousePressed());

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

    
    vector < string > results = ofSplitString(msg.message, ",");
    
    if (results.size() > 1){
        cout << results[1] << endl;
        if (results[1] == "settings"){
            cout << " here " << endl;
            settings.setVisible(true);
            rg.setVisible(false);
        }
        
        if (results[1] == "settingsBack"){
            settings.setVisible(false);
            rg.setVisible(true);
        }
        
        if (results[1] == "addons"){
            addons.setVisible(true);
            rg.setVisible(false);
        }
        
        if (results[1] == "addonsBack"){
            
            
            vector < string > addonsNames;
            // TODO fix this
            for (int i = 0; i < addons.nodes.size(); i++){
                if (addons.nodes[i]->uniqueName != "addonsBack"){
                    if (((textLabelToggle*)addons.nodes[i])->bToggled){
                        addonsNames.push_back(addons.nodes[i]->uniqueName);
                    }
                }
            }
            
            
            vector < string > addonsInMainPanelNames;
            for (int i = 0; i < rgAddons.nodes.size(); i++){
                //cout << rgAddons.nodes[i]->uniqueName << endl;
                if (rgAddons.nodes[i]->uniqueName != "addonsLabel" || rgAddons.nodes[i]->uniqueName != "addons"){
                    addonsInMainPanelNames.push_back(rgAddons.nodes[i]->uniqueName);
                }
            }
            
            for (int i = 0; i < addonsNames.size(); i++){
                bool bInAlready = false;
                for (int j = 0; j < addonsInMainPanelNames.size(); j++){
                    if (addonsInMainPanelNames[j] == addonsNames[i]){
                        bInAlready = true;
                    }
                }
                if (!bInAlready){
                    rgAddons.add((new textLabelToggleWithImage(addonsNames[i], addonsNames[i], &mono, false, 350))->setMargin(0, 25, 2, 25));
                }
            }
            
            addons.setVisible(false);
            rg.setVisible(true);
        }
    }
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
