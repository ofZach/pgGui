#pragma once




//------------------------------------------------------------------------------------------------------
class margin {
public:
    float t,l,r,b;
    margin(){
        t = 0;
        l = 0;
        r = 0;
        b = 0;
    }
    
    margin(float _t,float _r, float _b, float _l){
        t = _t;
        l = _l;
        r = _r;
        b = _b;
    }
};


//------------------------------------------------------------------------------------------------------
class node {
public:
    
    string uniqueName;
    ofRectangle bounds;
    ofPoint position;
    int state;
    bool bVisible;
    margin pad;
    bool bShouldBeDeleted;
    
    
    void add( node * newNode ){
        nodes.push_back(newNode);
    }
    
    void checkForDelete (){
        
        for (int i = 0; i < nodes.size(); i++){
            nodes[i]->checkForDelete();
        }
        
        
        vector < int > toDelete;
        for (int i = 0; i < nodes.size(); i++){
            if (nodes[i]->bShouldBeDeleted == true){
                toDelete.push_back(i);
            }
        }
        
        std::reverse(toDelete.begin(), toDelete.end());
        
        for (int i = 0; i < toDelete.size(); i++){
            nodes.erase( nodes.begin() + toDelete[i]);
        }
        
    }
    
    virtual void setVisible( bool _bVisible){
        bVisible =_bVisible;
        for (int i = 0; i < nodes.size(); i++){
            nodes[i]->setVisible(bVisible);
            
        }
    }
    
    
    void setBounds( ofRectangle _newBounds){
        bounds = _newBounds;
    }
    
    node(){
        bShouldBeDeleted = false;
    }
    
    // this is so I can chain things...
    node * setMargin(float t,float r, float b, float l){
        pad.t = t;
        pad.l = l;
        pad.b = b;
        pad.r = r;
        return this;
    }
    
    void setMargin(margin m){
        pad = m;
    }
    
    
    virtual void draw(){
        
        if (!bVisible) return;
        
        ofRectangle rect = bounds;
        rect.x += position.x;
        rect.y += position.y;
        ofRect(rect);
        
        for (int i = 0; i < nodes.size(); i++){
            nodes[i]->draw();
        }
    }
    
    // children:
    
    virtual bool handleMouse( ofPoint mouse, bool bPressed ){
        
        
        if (!bVisible) return;
        
        
        bool bAnyChildren = false;
        for (int i = 0; i < nodes.size(); i++){
            if (nodes[i]->handleMouse(mouse, bPressed)){
                bAnyChildren = true;
            }
        }
        
        if (bAnyChildren){
            state = 0;
            return true;
        }
        
        int prevState = state;
        if ( bounds.inside(mouse)){
            if (bPressed) state = 2;
            else state = 1;
            
            //cout << bAnyChildren << endl;
            if (prevState != 2 && state == 2){
                mousePressed();
                ofSendMessage("pressed," + uniqueName);
            }
            
            return true;
        } else {
            state = 0;
            return false;
        }
    }
    
    vector < node * > nodes;
    
    virtual void mousePressed(){
        
    }
    
    ofRectangle getBoundsPlusMargin(){
        ofRectangle temp = bounds;
        temp.x -= pad.l;
        temp.y -= pad.t;
        temp.width += pad.l + pad.r;
        temp.height += pad.t + pad.b;
        return temp;
        
    }
    
    virtual void setPosition( ofPoint newPosition){
        bounds.x = newPosition.x;
        bounds.y = newPosition.y;
        setupLayout();
    }
    
    void setupLayout(){
        
        checkForDelete();
        
        // let all subnode setup layour first.
        
        for (int i = 0; i < nodes.size(); i++){
            nodes[i]->setupLayout();
        }
        
        ofPoint pos (bounds.x, bounds.y);
        float maxHeightForThisLine = 0;
        
        for (int i = 0; i < nodes.size(); i++){
            
            if (pos.x + nodes[i]->bounds.width > bounds.x + bounds.width){
                pos.x = bounds.x;
                pos.y += maxHeightForThisLine; // 20?
                maxHeightForThisLine = nodes[i]->bounds.height + nodes[i]->pad.t + nodes[i]->pad.b;
            } else {
                maxHeightForThisLine = MAX(maxHeightForThisLine,nodes[i]->bounds.height + nodes[i]->pad.t + nodes[i]->pad.b);
            }
            
            nodes[i]->setPosition( ofPoint(pos.x + nodes[i]->pad.l, pos.y + nodes[i]->pad.t));
            
            //nodes[i]->bounds.x = pos.x;
            //nodes[i]->bounds.y = pos.y;
            pos.x += nodes[i]->bounds.width + nodes[i]->pad.l + nodes[i]->pad.r;
            
        }
        
        if (nodes.size() > 0){
            
            
            for (int i = 0; i < nodes.size(); i++){
                if (i == 0){
                    bounds = nodes[i]->getBoundsPlusMargin();
                } else {
                    bounds.growToInclude(nodes[i]->getBoundsPlusMargin());
                }
            }
            
        }
        
    }
    
    
    
};



//------------------------------------------------------------------------------------------------------
class spacer : public node {
public:
    
    spacer(){
        node::node();
    }
    spacer(string _uniqueName, float width, float height, margin m = margin()){
        setMargin(m);
        node::node();
        uniqueName = _uniqueName;
        setup(width, height);
        
    }
    
    void setup( float width, float height){
        bounds.set( 0,0,width, height );
    }
    
    void draw(){
        //        ofSetColor(ofColor::pink);
        //        ofRect(bounds);
        //        ofSetColor(ofColor::black);
        
    }
    
};




//------------------------------------------------------------------------------------------------------
class region : public node{
    
public:
    
    bool bDrawOutline;
    ofPolyline outline;
    
    
    region(margin m = margin()){
        setMargin(m);
        node::node();
        bDrawOutline = false;
    }
    
    virtual void draw(){
        
        if (!bVisible) return;
        
        for (int i = 0; i < nodes.size(); i++){
            nodes[i]->draw();
        }
        
        if (bDrawOutline){
            
            // dashed lines - this could be cached maybe ?
            
            ofPoint top (bounds.x, bounds.y);
            ofPoint bot (bounds.x + bounds.width, bounds.y + bounds.height);
            
            ofPolyline lines[4];
            lines[0].addVertex( top.x, top.y );
            lines[0].addVertex( top.x, bot.y);
            lines[1].addVertex( top.x, bot.y );
            lines[1].addVertex( bot.x, bot.y);
            lines[2].addVertex( bot.x, bot.y);
            lines[2].addVertex( bot.x, top.y);
            lines[3].addVertex( bot.x, top.y);
            lines[3].addVertex( top.x, top.y);
            
            for (int i = 0; i < 4; i++){
                lines[i] = lines[i].getResampledBySpacing(2);
            }
            
            outline.clear();
            outline.addVertices(lines[0].getVertices());
            outline.addVertices(lines[1].getVertices());
            outline.addVertices(lines[2].getVertices());
            outline.addVertices(lines[3].getVertices());
            
            
            bool bGood = false;
            
            
            ofSetLineWidth(2);
            ofNoFill();
            for (int i = 0; i < outline.size(); i++){
                bool bPrevGood = bGood;
                if (i / 5 % 2 == 0) bGood = true;
                else bGood  = false;
                if (bGood && !bPrevGood){
                    ofBeginShape();
                } else if (!bGood && bPrevGood){
                    ofEndShape();
                }
                if (bGood){
                    ofVertex(outline[i]);
                }
            }
            
            ofFill();
            
            ofSetLineWidth(1);
            
        }
    }
    
};


//------------------------------------------------------------------------------------------------------
class scrollableRegion : public region {
    
public:
    
    
    bool bDrawScrollbar;
    float scrollPct;
    ofRectangle viewBounds;
    ofRectangle scrollBounds;
    float scrollDiff;
    
    scrollableRegion(margin m = margin()){
        setMargin(m);
        node::node();
    }
    
    
    void setViewBounds(ofRectangle view){
        viewBounds = view;
        scrollPct = 0;
        scrollBounds = view;
        scrollBounds.x = scrollBounds.x + scrollBounds.width - 25;
        scrollBounds.width = 25;
        scrollDiff = 0;
    }
    
    void update(){
        if (bounds.height > viewBounds.height){
            bDrawScrollbar = true;
            scrollDiff = bounds.height - viewBounds.height;
        } else {
            bDrawScrollbar = false;
            scrollPct = 0;
        }
    }
    
    
    void handleScroll( ofPoint mouse, bool bPressed ){
        if (scrollBounds.inside(mouse)){
            if (bPressed){
                scrollPct = ofMap(mouse.y, scrollBounds.y, scrollBounds.y + scrollBounds.height, 0, 1);
                
                bounds.y = -scrollDiff * scrollPct;
            }
        }
    }
    
    
    virtual void draw(){
        
        //cout << bounds.y << endl;
        
        if (!bVisible) return;
        region::draw();
        
        if (bDrawScrollbar == true){
            ofSetColor(ofColor::darkGrey);
            ofRect(scrollBounds);
            ofSetColor(ofColor::seaShell);
            ofRect(scrollBounds.x, scrollPct * (scrollBounds.height - 20)   , scrollBounds.width, 20);
            
        }
    }
    
    
    
    
};



//------------------------------------------------------------------------------------------------------
class imageButton: public node {
    
public:
    
    ofImage img;
    
    imageButton(margin m = margin()){
        setMargin(m);
        node::node();
    }
    
    imageButton(string _uniqueName, string fileName,margin m = margin()){
        setMargin(m);
        uniqueName = _uniqueName;
        loadImage(fileName);
    }
    
    void loadImage(string filename){
        img.loadImage(filename);
        bounds.set(0,0,img.getWidth(), img.getHeight());
    }
    
    void draw(){
        if (!bVisible) return;
        ofSetColor(ofColor::white);
        img.draw(bounds.x, bounds.y, bounds.width, bounds.height);
        ofSetColor(ofColor::black);
    }
    
};



//------------------------------------------------------------------------------------------------------
class imageTextButton : public node{
    
};


//------------------------------------------------------------------------------------------------------
class toolTip : public node{
    
};


//------------------------------------------------------------------------------------------------------
class actionButton: public node {
    
};


//------------------------------------------------------------------------------------------------------
class logo {
    
    
};



//------------------------------------------------------------------------------------------------------
class textLabel : public node {
public:
    ofTrueTypeFont * font;
    string myLabel;
    float textmargin;
    ofPoint typeOffset;
    bool bDrawBackground;
    
    textLabel(margin m = margin()){
        setMargin(m);
        node::node();
        bDrawBackground = true;
    }
    
    textLabel( string _uniqueName, string str, ofTrueTypeFont * _font, int width = 0, bool bDrawBg = false,margin m = margin()){
        setMargin(m);
        node::node();
        uniqueName = _uniqueName;
        bDrawBackground = bDrawBg;
        font = _font;
        setString(str, width);
    }
    
    void setString( string newStr, int width = 0){
        textmargin = 8;
        myLabel = newStr;
        ofRectangle rect = font->getStringBoundingBox(myLabel, 0, 0);
        typeOffset = ofPoint(rect.x, rect.y);
        
        rect.width += textmargin*2;
        rect.height += textmargin*2;
        
        rect.width = MAX(width, rect.width);
        
        bounds.set( rect );
    }
    
    void draw(){
        if (!bVisible) return;
        if (bDrawBackground){
            
            if (state == 0)
                ofSetColor(ofColor::white);
            else
                ofSetColor(ofColor::cyan);
            
            ofRect(bounds);
        }
        ofSetColor(ofColor::black);
        font->drawString(myLabel, bounds.x + textmargin - typeOffset.x, bounds.y + textmargin - typeOffset.y);
        
        //        ofNoFill();
        //        ofSetColor(ofColor::green);
        //        ofRect( bounds.x - pad.l, bounds.y - pad.t, bounds.width + pad.l + pad.r, bounds.height + pad.t + pad.b);
        //        ofFill();
        
    }
};





//------------------------------------------------------------------------------------------------------
class textLabelToggle : public textLabel {
    
public:
    
    bool bToggled;
    
    textLabelToggle(margin m = margin()){
        setMargin(m);
        node::node();
        bDrawBackground = true;
        bToggled = false;
    }
    
    textLabelToggle(string _uniqueName, string label, ofTrueTypeFont * _font,  bool bState, int width = 0, margin m = margin()){
        setMargin(m);
        node::node();
        bDrawBackground = true;
        uniqueName = _uniqueName;
        bToggled = bState;
        font = _font;
        setString(label, width);
    }
    
    virtual void mousePressed(){
        bToggled = !bToggled;
    }
    
    virtual void draw(){
        
        if (!bVisible) return;
        if (bDrawBackground){
            
            if (bToggled == 0)
                ofSetColor(ofColor::white);
            else
                ofSetColor(ofColor::cyan);
            
            ofRect(bounds);
        }
        ofSetColor(ofColor::black);
        font->drawString(myLabel, bounds.x + textmargin - typeOffset.x, bounds.y + textmargin - typeOffset.y);  // this is weird!
        
        //        ofNoFill();
        //        ofSetColor(ofColor::green);
        //        ofRect( bounds.x - pad.l, bounds.y - pad.t, bounds.width + pad.l + pad.r, bounds.height + pad.t + pad.b);
        //        ofFill();
    }
    
    
    
};


class textLabelToggleWithImage : public textLabelToggle {
  
public:
    
    
    textLabelToggleWithImage(margin m = margin()){
        setMargin(m);
        node::node();
        bDrawBackground = true;
        bToggled = false;
    }
    
    textLabelToggleWithImage(string _uniqueName, string label, ofTrueTypeFont * _font,  bool bState, int width = 0, margin m = margin()){
        setMargin(m);
        node::node();
        bDrawBackground = true;
        uniqueName = _uniqueName;
        bToggled = bState;
        font = _font;
        setString(label, width);
    }
    
    virtual void draw(){
        
        if (!bVisible) return;
        if (bDrawBackground){
            
            if (bToggled == 0)
                ofSetColor(ofColor::white);
            else
                ofSetColor(ofColor::pink);
            
            ofRect(bounds);
        }
        ofSetColor(ofColor::black);
        font->drawString(myLabel, bounds.x + textmargin - typeOffset.x, bounds.y + textmargin - typeOffset.y);  // this is weird!
        
        ofDrawBitmapString("x", bounds.x + bounds.width - 10, bounds.y + bounds.height/2);
    }
    
    virtual void mousePressed(){
        bShouldBeDeleted = true;
    }

};



//------------------------------------------------------------------------------------------------------
class textFieldWithLabel : public node {
    
public:
    
    textLabel label;
    textLabel value;
    
    textFieldWithLabel( margin m = margin()){
        setMargin(m);
        node::node();
    }
    
    textFieldWithLabel( string _uniqueName, string labelName, string valueName, ofTrueTypeFont * _font, float width = 0, margin m = margin()){
        setMargin(m);
        node::node();
        setFont(_font);
        uniqueName = _uniqueName;
        setup(labelName, valueName, width);
    }
    
    void setup(string labelName, string valueName, float width = 0){
        label.setString(labelName, width);
        value.setString(valueName, width);
        bounds.set(label.bounds);
        bounds.height += value.bounds.height;
        label.bDrawBackground = false;
    }
    
    void setFont( ofTrueTypeFont * font){
        label.font = font;
        value.font = font;
    }
    
    void setPosition( ofPoint newPosition){
        
        bounds.x = newPosition.x;
        bounds.y = newPosition.x;
        label.setPosition( newPosition );
        newPosition.y += label.bounds.height;
        value.setPosition( newPosition  );
        bounds = label.bounds;
        bounds.growToInclude(value.bounds);
        
    }
    
    void setVisible( bool _bVisible){
        bVisible =_bVisible;
        label.setVisible(bVisible);
        value.setVisible(bVisible);
    }
    
    void draw(){
        if (!bVisible) return;
        label.draw();
        value.draw();
        
        
        //        ofNoFill();
        //        ofSetColor(ofColor::magenta);
        //        ofRect( bounds.x - pad.l, bounds.y - pad.t, bounds.width + pad.l + pad.r, bounds.height + pad.t + pad.b);
        //        ofFill();
        //
        //        ofNoFill();
        //        ofSetColor(ofColor::blue);
        //        ofRect( bounds );
        
        ofFill();
        
        ofSetColor(ofColor::black);
        
    }
    
    virtual bool handleMouse( ofPoint mouse, bool bPressed ){
        if (!bVisible) return;
        return value.handleMouse(mouse, bPressed);
    }
    
    
};