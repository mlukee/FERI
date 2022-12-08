//
// Created by Matic on 5/30/2022.
//

#include "Log.h"

const std::string Log::fileName = "log.txt";

std::string Log::GetStringLogType(LogType type){
    switch (type) {
        case LogType::DEBUG:
            return "[DEBUG] ";
        case LogType::INFO:
            return "[INFO] ";
        case LogType::WARN:
            return "[WARN] ";
        case LogType::ERROR:
            return "[ERROR] ";
    }
}
Log::Log(LogType type){
    file.open(fileName, std::ios::app);
    if(file.is_open()){
        file << GetStringLogType(type);
    }
}

Log::~Log(){
    file.close();
}