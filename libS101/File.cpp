#include "File.h"

namespace libS101 {

void File::write(const void *buffer, size_t size){
    std::fstream::write(static_cast<const char*>(buffer),size);
}

size_t File::read(void *buffer, size_t size){
    std::fstream::read(static_cast<char*>(buffer),size);
    return this->gcount();
}

long long File::length(){
    long long curpos = tellg();
    seekg(0,std::ios::end);
    long long result = tellg();
    seekg(curpos);
    return result;
}

};