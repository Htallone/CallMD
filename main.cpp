/*
 * main.cpp
 *
 *  Created on: Dec 11, 2020
 *      Author: htallone
 */
#include <cstdlib>
#include <cstdio>

#include "MDAeroPAC3MSE.h"
#include "textFileManipulation.h"
using namespace MissileDatcom;



int main(){
	//  vector<double> hp(8);
	//  hp[0] = 0;
	//  hp[1] = 5000;
	//  hp[2] = 10000;
	//  hp[3] = 15000;
	//  hp[4] = 20000;
	//  hp[5] = 25000;
	//  hp[6] = 30000;
	//  hp[7] = 40000;


    //  vector<double> beta(13);
    //  beta[0] = -40;
    //  beta[1] = -30;
    //  beta[2] = -20;
    //  beta[3] = -15;
    //  beta[4] = -10;
    //  beta[5] = -5;
    //  beta[6] = 0;
    //  beta[7] = 5;
    //  beta[8] = 10;
    //  beta[9] = 15;
    //  beta[10] = 20;
    //  beta[11] = 30;
    //  beta[12] = 40;


	//  vector<double> tempDeltaE(7);
	//  tempDeltaE[0] = -30;
	//  tempDeltaE[1] = -20;
	//  tempDeltaE[2] = -10;
	//  tempDeltaE[3] = 0;
	//  tempDeltaE[4] = 10;
	//  tempDeltaE[5] = 20;
	//  tempDeltaE[6] = 30;



	vector<double> hp(1);
	hp[0] = 0;

	vector<double> beta(1);
	beta[0] = 10;

	vector<double> tempDeltaE(1);
	tempDeltaE[0] = 10;

	MDAeroPAC3MSE pac3mse(hp,beta,tempDeltaE,tempDeltaE,tempDeltaE);

	int Sizeh = hp.size();
	int Sizebeta = beta.size();
	int SizedeltaA = tempDeltaE.size();
	int SizedeltaE = tempDeltaE.size();
	int SizedeltaR = tempDeltaE.size();

	for(int ih=0;ih<Sizeh;ih++)
		for (int ibeta = 0; ibeta < Sizebeta; ibeta++)
		{
			std::cout <<"  h-"<<ih<<"-beta-"<<ibeta<< "       h=" << hp[ih]<<"  beta=" << beta[ibeta] << endl;

			for (int ideltaA = 0; ideltaA < SizedeltaA; ideltaA++)
				for (int ideltaE = 0; ideltaE < SizedeltaE; ideltaE++)
					for (int ideltaR = 0; ideltaR < SizedeltaR; ideltaR++)
					{

						ofstream foutFor005;
						foutFor005.open("for005.dat", std::ios::out | std::ios::trunc);
						pac3mse.writeTheCase(foutFor005, hp[ih], beta[ibeta], tempDeltaE[ideltaA], tempDeltaE[ideltaE], tempDeltaE[ideltaR]);
						foutFor005.close();

						// //! Windows系统下使用
						// std::system("MD0311.exe"); 

						//! Linux系统下借助wine来调用MD程序，但是存在问题
						//! C++规定system函数调用的程序运行结束后才会运行后面的程序
						//! 这里system函数似乎只等待wine调用结束，而不是MD0311.exe运行结束
						//! 结果，MD0311.exe还没运行完，就后面程序就打开了for042.csv文件，此时结果数据不全。
						//! 所以在Linux下不要使用这种调用，只调用一次MD0311.exe时，可以在命令行中运行wine，
						//! 当case很多需要循环调用时，在windows系统下没问题。
						//! 也可以使用MD 1999在linux下生成的可执行程序，不过没有for042文件，其结果数据提取可能比较麻烦。
						std::system("wine start /Unix \"/FullPathtoMD/MD0311.exe\"");

						std::ifstream infile;
						infile.open("for042.csv", std::ios::in);
						std::ofstream outfileData("for042Total", std::ios::out | std::ios::app);

						std::string line;

						for (unsigned int curLine = 0; getline(infile, line); curLine++) {
							outfileData << line << "\n";
						}

						infile.close();
						outfileData.close();

						//std::remove("for042.csv");
					}

		}

	std::cout<<"Aero data compute over." << endl;


// 	for042FileToHeaderAndData("for042.csv",
// 			"for042Header.csv" ,
// 			"for042Data.csv");



}

