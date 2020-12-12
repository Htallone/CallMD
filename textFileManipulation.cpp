/*
 * textFileManipulation.cpp
 *
 *  Created on: Dec 11, 2020
 *      Author: htallone
 */

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <list>

#include "textFileManipulation.h"

void for042FileToHeaderAndData(const std::string & for042PathName,
		const std::string & for042HeaderFileName ,
		const std::string & for042DataFileName)
{
	std::ifstream infile( for042PathName.c_str( ) , std::ios::in ) ;
	std::ofstream outfileHeader( for042HeaderFileName.c_str( ) , std::ios::out | std::ios::trunc ) ;
	std::ofstream outfileData( for042DataFileName.c_str( ) , std::ios::out | std::ios::trunc ) ;

	std::string line ;
	if ((!infile.is_open()) || (!outfileHeader.is_open()) || (!outfileData.is_open())) {
		std::cerr << "The for042.csv or for042Header or for042Data file cannot be opened";
		exit(1);
	}

	std::string strSIZES ("SIZES");
	std::string strCASE ("CASE");
	std::string strNALPHA ("NALPHA");
	std::string strNMACH ("NMACH");


	bool flagHeaderLineReadFirst = false;
	for(unsigned int curLine = 0; getline(infile, line); curLine++) {
	    if (line.find(strSIZES) != std::string::npos) {

	    }
	    else if(line.find(strCASE) != std::string::npos){
	    	if(!flagHeaderLineReadFirst)
	    	{
	    		outfileHeader << line << "\n" ;
	    		outfileData << line << "\n" ;
	    		flagHeaderLineReadFirst  = true;
	    	}

	    }
	    else{
	    	outfileData << line << "\n" ;
	    }
	}

	infile.close( ) ;
	outfileHeader.close();
	outfileData.close();
}
