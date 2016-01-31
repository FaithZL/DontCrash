//
//  UserData.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/31.
//
//

#ifndef UserData_hpp
#define UserData_hpp

#include "cocos2d.h"
#include "../utils/FileData.hpp"

class UserData : public cocos2d::Ref , public FileData {
public:
    UserData();
    ~UserData();
    
    CREATE_FUNC(UserData);
    
    virtual bool init();
    
    bool createFile();
    
protected:
    
    std::string _filePath;
    
};

#endif /* UserData_hpp */
