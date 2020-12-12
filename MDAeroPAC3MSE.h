/*
 * MDAeroPAC3MSE.h
 *
 *  Created on: Dec 11, 2020
 *      Author: htallone
 */

#ifndef MDAEROPAC3MSE_H_
#define MDAEROPAC3MSE_H_

#include "IMissileDatcomAeroCompt.h"

namespace MissileDatcom {

//! 估算PAC3MSE气动系数的类
/*!
 * 继承自抽象类 IMissileDatcomAeroCompt，具体实现各个接口函数
 */
class MDAeroPAC3MSE: public IMissileDatcomAeroCompt {
public:
	MDAeroPAC3MSE();
	MDAeroPAC3MSE(vector<double> hp,vector<double> betap,vector<double> deltaAp,vector<double> deltaEp,vector<double> deltaRp);
	virtual ~MDAeroPAC3MSE();

	bool writeInitalCase(ofstream &outputFile);
	bool writeChangeFLTCON_DEFLCTCase(ofstream &outputFile, double h, double beta, double deltaA, double deltaE, double deltaR, string config = "+");
	bool writeChangeFLTCONCase(ofstream &outputFile, double h, double beta);
	bool writeChangeDEFLCTCase(ofstream &outputFile, double deltaA, double deltaE, double deltaR, string config = "+");

	bool writeTheCase(ofstream &outputFile, double h, double beta, double deltaA, double deltaE, double deltaR, string config = "+");

};

} /* namespace MissileDatcom */

#endif /* MDAEROPAC3MSE_H_ */
