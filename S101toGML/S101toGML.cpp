// S101toGML.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "S101toGML.h"
#include "S101.h"

#include <iostream>


int main(int argc, char* argv[])
{
	if (argc < 3){
		std::cout << "usage: program <S101/input/path> <GML/output/path>";
		return -1;
	}
	else {
		std::string s101path = argv[1];
		std::string gmlpath = argv[2];

		libS101::S101 s101;
		if(s101.Open(s101path)){
			std::cout << "Open " << s101path << " success" << std::endl;
		} else {
			std::cout << "Open " << s101path <<  " failed. Please check the file path." << std::endl;
			return -1;
		}

		s101.Save(gmlpath,L"");
		std::cout << "GML export to " << gmlpath << " success" << std::endl;

    }
    return 0;

}