#ifndef NALOGA1102_LOG_H
#define NALOGA1102_LOG_H

#include <fstream>

enum class LogType{
    DEBUG, INFO, WARN, ERROR
};

class Log {
private:
    static std::ofstream file;
    const static std::string fileName;
public:
    static std::string GetStringLogType(LogType type);
    Log(LogType type);
    ~Log();

    template<typename T>
    Log &operator<<(const T &msg){
        if(file.is_open())
            file << msg << "\n";
        return *this;
    }
};


#endif //NALOGA1102_LOG_H
