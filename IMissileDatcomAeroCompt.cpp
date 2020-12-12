/*
 * IMissileDatcomAeroCompt.cpp
 *
 *  Created on: Dec 11, 2020
 *      Author: htallone
 */

#include "IMissileDatcomAeroCompt.h"

namespace MissileDatcom {

IMissileDatcomAeroCompt::IMissileDatcomAeroCompt() {
	// TODO Auto-generated constructor stub
	 h.clear();
	 beta.clear();
	 deltaA.clear();
	 deltaE.clear();
	 deltaR.clear();
}

IMissileDatcomAeroCompt::IMissileDatcomAeroCompt(vector<double> hp,vector<double> betap,vector<double> deltaAp,vector<double> deltaEp,vector<double> deltaRp){
	h =hp;
	beta = betap;
	deltaA = deltaAp;
	deltaE = deltaEp;
	deltaR = deltaRp;

}

bool IMissileDatcomAeroCompt::generateInitialFor005File(){

	ofstream foutFor005;
	foutFor005.open("for005.dat");

	int Sizeh = h.size();
	int Sizebeta = beta.size();
	int SizedeltaA = deltaA.size();
	int SizedeltaE = deltaE.size();
	int SizedeltaR = deltaR.size();

	writeInitalCase(foutFor005);
	for(int ih=0;ih<Sizeh;ih++)
		for(int ibeta=0;ibeta<Sizebeta;ibeta++)
			for(int ideltaA=0;ideltaA<SizedeltaA;ideltaA++)
				for(int ideltaE=0;ideltaE<SizedeltaE;ideltaE++)
					for(int ideltaR=0;ideltaR<SizedeltaR;ideltaR++)
					{
						writeChangeFLTCON_DEFLCTCase(foutFor005, h[ih], beta[ibeta], deltaA[ideltaA], deltaE[ideltaE], deltaR[ideltaR]);
					}

	foutFor005.close();
	return true;
}

IMissileDatcomAeroCompt::~IMissileDatcomAeroCompt() {
	// TODO Auto-generated destructor stub
}

} /* namespace MissileDatcom */
