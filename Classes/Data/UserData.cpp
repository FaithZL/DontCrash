//
//  UserData.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/31.
//
//

#include "UserData.hpp"
#include "constant.h"


UserData::UserData(){
    
}

UserData::~UserData(){
    
}

bool UserData::init(){
	createFile();
    return true;
}

bool UserData::createFile(){
	_filePath = cocos2d::FileUtils::getInstance()->getWritablePath() + GAME_DIR;
	
	if (!cocos2d::FileUtils::getInstance()->isDirectoryExist(_filePath)) {
		cocos2d::FileUtils::getInstance()->createDirectory(_filePath);
	}
	
	setFileName(_filePath + USER_DATA_FILE);
	
	if (!cocos2d::FileUtils::getInstance()->isFileExist(_fileName)) {
		fopen(_fileName.c_str() , "w+");
	}
	
	CCLOG("full path: %s" , _fileName.c_str());
	return true;
}

