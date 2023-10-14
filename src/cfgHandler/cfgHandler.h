#ifndef FILES_H
#define FILES_H
#include<SPIMemory.h>
#include "SPIFFS.h"

std::string readFile(fs::FS &fs, const char * path){
    //Serial.printf("Reading file: %s\r\n", path);
    std::string content = "";
    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return "";
    }
    // Serial.println("- read from file:");

    
      
    while (file.available())
    {
        content += char(file.read());
    }

    file.close();    
    return content;
    /*Serial.println("=====================================");
    Serial.println(debugLogData);
    Serial.println("=====================================");*/
}


bool writeFile(fs::FS &fs, const char * path, const char * message){
    // Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return false;
    }
    if(file.print(message)){
        Serial.println("- file written");
        file.close();
        return true;
    } else {
        Serial.println("- write failed");
        file.close();
        return false;
    }

}

bool deleteFile(fs::FS &fs, const char * path){
    //Serial.printf("Deleting file: %s\r\n", path);
    if(fs.remove(path)){
        Serial.println("- file deleted");
        return true;
    } else {
        Serial.println("- delete failed");
        return false;
    }
}



#endif
