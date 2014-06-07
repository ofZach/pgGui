#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"
#include "ofAppNoWindow.h"







#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/AutoPtr.h"
#include <iostream>

#include "ofMain.h"
#include "CBLinuxProject.h"
#include "CBWinProject.h"
#include "visualStudioProject.h"
#include "xcodeProject.h"
#include <Poco/Path.h>



using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::AutoPtr;


class commandLineProjectGenerator: public Application{
public:
    
    baseProject * project;
    string projectPath;
    string target;
    vector <int> targetsToMake;
    vector <string> addons;
    
    void setupForTarget(int targ){

        if(project){
            delete project;
        }

        switch(targ){
            case OF_TARGET_OSX:
                project = new xcodeProject;
                target = "osx";
                break;
            case OF_TARGET_WINGCC:
                project = new CBWinProject;
                target = "win_cb";
                break;
            case OF_TARGET_WINVS:
                project = new visualStudioProject;
                target = "vs";
                break;
            case OF_TARGET_IPHONE:
                project = new xcodeProject;
                target = "ios";
                break;
            case OF_TARGET_ANDROID:
                break;
            case OF_TARGET_LINUX:
                project = new CBLinuxProject;
                target = "linux";
                break;
            case OF_TARGET_LINUX64:
                project = new CBLinuxProject;
                target = "linux64";
                break;
            case OF_TARGET_LINUXARMV6L:
                project = new CBLinuxProject;
                target = "linuxarmv6l";
                break;
            case OF_TARGET_LINUXARMV7L:
                project = new CBLinuxProject;
                target = "linuxarmv7l";
                break;
        }
    }

    
    
	commandLineProjectGenerator(): _helpRequested(false){
	}
    
protected:
    
	void initialize(Application& self){
		loadConfiguration(); // load default configuration files, if present
		Application::initialize(self);
		// add your own initialization code here
	}
	
	void uninitialize(){
		Application::uninitialize();
	}
	
	void reinitialize(Application& self){
		Application::reinitialize(self);
	}
	
	void defineOptions(OptionSet& options){
		Application::defineOptions(options);
        
		options.addOption(
                          Option("help", "h", "")
                          .required(false)
                          .repeatable(false)
                          .callback(OptionCallback<commandLineProjectGenerator>(this, &commandLineProjectGenerator::handleHelp)));
        
		options.addOption(
                          Option("name", "n", "")
                          .required(false)
                          .repeatable(false)
                          .argument("\"project name\"")
                          .callback(OptionCallback<commandLineProjectGenerator>(this, &commandLineProjectGenerator::handleName)));
        
        options.addOption(
                          Option("platforms", "x", "")
                          .required(false)
                          .repeatable(false)
                          .argument("\"comma seperated platforms\"")
                          .callback(OptionCallback<commandLineProjectGenerator>(this, &commandLineProjectGenerator::handlePlatforms)));
        
        
        options.addOption(
                          Option("addons", "a", "")
                          .required(false)
                          .repeatable(false)
                          .argument("\"comma seperated addons\"")
                          .callback(OptionCallback<commandLineProjectGenerator>(this, &commandLineProjectGenerator::handleAddons)));
        
		options.addOption(
                          Option("ofPath", "op", "")
                          .required(true)
                          .repeatable(true)
                          .argument("\"path to openframeworks\"")
                          .callback(OptionCallback<commandLineProjectGenerator>(this, &commandLineProjectGenerator::handleOFPath)));
        
		options.addOption(
                          Option("projectPath", "p", "")
                          .required(false)
                          .repeatable(false)
                          .argument("\"path to project\"")
                          .callback(OptionCallback<commandLineProjectGenerator>(this, &commandLineProjectGenerator::handleProjectPath)));
	}
	
	void handleHelp(const std::string& name, const std::string& value){
		_helpRequested = true;
		displayHelp();
		stopOptionsProcessing();
	}
    

    
    void handlePlatforms(const std::string& name, const std::string& value){

        vector < string > platforms = ofSplitString(value, ",");
        for (int i = 0; i < platforms.size(); i++){
            
            if( platforms[i]=="linux"){
                targetsToMake.push_back( OF_TARGET_LINUX );
            }else if(platforms[i]=="linux64"){
                targetsToMake.push_back( OF_TARGET_LINUX64 );
            }else if(platforms[i]=="linuxarmv6l"){
                targetsToMake.push_back( OF_TARGET_LINUXARMV6L );
            }else if(platforms[i]=="linuxarmv7l"){
                targetsToMake.push_back( OF_TARGET_LINUXARMV7L );
            }else if(platforms[i]=="win_cb"){
                targetsToMake.push_back( OF_TARGET_WINGCC );
            }else if(platforms[i]=="vs"){
                targetsToMake.push_back( OF_TARGET_WINVS );
            }else if(platforms[i]=="osx"){
                targetsToMake.push_back( OF_TARGET_OSX );
            }else if(platforms[i]=="ios"){
                targetsToMake.push_back( OF_TARGET_IPHONE );
            }else if(platforms[i]=="android"){
                ofLogError() << "android platform not supported yet" << endl;
                std::exit(1);
            }else if(platforms[i]=="allplatforms"){
                targetsToMake.push_back( OF_TARGET_LINUX );
                targetsToMake.push_back( OF_TARGET_LINUX64 );
                targetsToMake.push_back( OF_TARGET_LINUXARMV6L );
                targetsToMake.push_back( OF_TARGET_LINUXARMV7L );
                targetsToMake.push_back( OF_TARGET_WINGCC );
                targetsToMake.push_back( OF_TARGET_WINVS );
                targetsToMake.push_back( OF_TARGET_OSX );
                targetsToMake.push_back( OF_TARGET_IPHONE );
            }
        }
	}
	
	void handleName(const std::string& name, const std::string& value){
		// ??
	}
	
	void handleOFPath(const std::string& name, const std::string& value){
		cout << "setting root of OF to " << value << endl;
        
        setOFRoot(value);
	}
    
    void handleProjectPath(const std::string& name, const std::string& value){
		
        cout << "setting project path to " << value << endl;
        
        projectPath = value;
	}
    
    void handleAddons(const std::string& name, const std::string& value){
		
        addons = ofSplitString(value, ",", true, true);
    }
    
	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("\n\n\n\n\nOPTIONS");
		helpFormatter.setHeader("A command line project generator");
        helpFormatter.setFooter("\n\n\n\n\n");
		helpFormatter.format(std::cout);
        
        
	}
	
	
    
	int main(const std::vector<std::string>& args){
        
//      useful for debugging args.
//		if (!_helpRequested)
//		{
//			logger().information("Arguments to main():");
//			for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it)
//			{
//				logger().information(*it);
//			}
//			//logger().information("Application properties:");
//			//printProperties("");
//		}
        
        if (_helpRequested){
            return Application::EXIT_OK;
        }
        
        if (!_helpRequested){
        
        if(targetsToMake.empty())
            targetsToMake.push_back( ofGetTargetPlatform() );
        
        
        for(int i = 0; i < (int)targetsToMake.size(); i++){
			setupForTarget(targetsToMake[i]);
        
            project->setup(target);
            
            
            cout << "creating " << projectPath <<  endl;
            project->create(projectPath);
        
            //vector < string > addons;
            //parseAddonsDotMake(project->getPath() + "addons.make", addons);
            for (int i = 0; i < (int)addons.size(); i++){
                ofAddon addon;
                addon.fromFS(ofFilePath::join(ofFilePath::join(getOFRoot(), "addons"), addons[i]),target);
                project->addAddon(addon);
            }
            project->save(false);
    	}
        }
        return Application::EXIT_OK;
	}
	
	
private:
	bool _helpRequested;
};


POCO_APP_MAIN(commandLineProjectGenerator)
