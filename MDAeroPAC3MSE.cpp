/*
 * MDAeroPAC3MSE.cpp
 *
 *  Created on: Dec 11, 2020
 *      Author: htallone
 */

#include "MDAeroPAC3MSE.h"

namespace MissileDatcom {

MDAeroPAC3MSE::MDAeroPAC3MSE() {
	// TODO Auto-generated constructor stub

}

MDAeroPAC3MSE::MDAeroPAC3MSE(vector<double> hp,vector<double> betap,vector<double> deltaAp,vector<double> deltaEp,vector<double> deltaRp)
			: IMissileDatcomAeroCompt(hp,betap,deltaAp,deltaEp,deltaRp) {

}


bool MDAeroPAC3MSE::writeInitalCase(ofstream &outputFile){
	double H = 0.14;
	double l=0.98;//0.98
	double h=0.1275;
	double r=(l*l+h*h)/2.0/h;
	//y=sqrt(r*r-(x-l)*(x-l))-(r-h);
	double X[48]={0.0 , 0.03, 0.06, 0.09, 0.12, 0.15, 0.20, 0.25, 0.30, 0.35,
				0.40, 0.45, 0.50, 0.56, 0.70, 0.82, 0.9, 0.95, 0.98, 1.02,    //0.56, 0.70, 0.82, 0.9, 0.95, 0.98, 1.02,
				1.08 , 1.18, 1.3, 1.4, 1.56, 1.76, 2.086, 2.10, 2.13, 2.161,       //2.086, 2.10, 2.13, 2.161,
				2.18, 2.24, 2.35, 2.408, 2.45, 2.5, 3.0, 3.73, 4.13, 4.53,        //DCON 2.086 2.161 2.408 5.042   .... 27 30 34 43
				4.93, 5.0, 5.06, 5.12, 5.14, 5.16, 5.18, 5.2 };
	double R[48]={0.};
	for(int i=0;i<48;i++){
		if(X[i]<0.98){
			R[i] = sqrt(r*r-(X[i]-l)*(X[i]-l))-(r-h);
		}
		else if(X[i]<2.086){
			R[i] = h;
		}
		else if(X[i]<2.161){
			R[i] = h+(0.135-h)/(2.161-2.086)*(X[i]-2.086);
		}
		else if(X[i]<2.408){
			R[i] = 0.135+(H-0.135)/(2.408-2.161)*(X[i]-2.161);
		}
		else if(X[i]<5.06){
			R[i] = H;
		}
		else{
			R[i] = H+(0.12-H)/(5.2-5.06)*(X[i]-5.06);
		}

	}

	//initial case
	outputFile 	<< "CASEID PAC-3MSE BODY AND FINS WITH C.G. SPECIFIED"                   		<<endl
			    << "DIM M"                                                                  	<<endl
				<< " $FLTCON  NALPHA=13.0,"                               						<<endl
				<< "          ALPHA=-40.,-30.,-20.,-15.,-10.,-5.,0.,"                   		<<endl
				<< "                5.,10.,15.,20.,30.,40.,"                     				<<endl
				<< "          NMACH=10.,"                                             			<<endl
				<< "          MACH=0.1,0.5,1.0,"  												<<endl
				<< "               1.5,2.0,3.0,4.0,5.0,6.0,7.0,"  								<<endl
				<< "          ALT=0.0,0.0,0.0,"   												<<endl
				<< "              0.0,0.0,0.0,0.0,0.0,0.0,0.0,"   								<<endl
				<< "          BETA=0.0,"                                                       	<<endl
				<< " $END"                                            							<<endl
				<< " $REFQ  SREF=0.062,"                                           				<<endl
				<< "        LREF=5.2,"                   										<<endl
				<< "        XCG=0.,"                     										<<endl
				<< "        ZCG=0.,"                                                        	<<endl
				<< "        RHR=50.,"                                                   		<<endl
				<< " $END"                                                  					<<endl

				<< " $AXIBOD  NX=48.,"                                                         	<<endl                 
				<< "          X=";

	for(int i=0;i<48;i++){
		outputFile<< fixed << setprecision(3)<<X[i]<<",";
		if(i%10==9){
			outputFile  << "\n"
						<< "            ";
		}
	}
	outputFile  << "\n"
				<< "          R=";
	for(int i=0;i<48;i++){
		outputFile<<fixed << setprecision(6)<<R[i]<<",";
		if(i%6==5){
			outputFile  << "\n"
						<< "            ";
		}
	}
	outputFile  << "\n";

	outputFile  << "          DISCON=27.,30.,34.,43.,"           								<<endl
				<< "          LNOSE=2.408,"                   									<<endl
				<< "          DNOSE=0.28,"                   									<<endl
				<< "          LCENTR=2.652,"                  									<<endl
				<< "          LAFT=0.14,"                     									<<endl
				<< "          DAFT=0.24,"                   									<<endl
				<< "          DEXIT=0.,"                     									<<endl
				<< " $END"
                                                                                                <<endl
				<< " $FINSET1  SECTYP=HEX,"                                                     <<endl
				<< "           SSPAN=0.14,0.205,"                                             	<<endl
				<< "           CHORD=1.043,0.809,"                                            	<<endl
				<< "           XLE=2.689,2.861,"                                               	<<endl
				<< "           NPANEL=4.0,"                                                  	<<endl
				<< "           PHIF=0.0,90.0,180.0,270.0,"                                   	<<endl
				<< "           ZUPPER=0.006,0.0037,LMAXU=0.171,0.1,LFLATU=0.7596,0.8,"       	<<endl
				<< " $END"                                                                    	<<endl

				<< " $FINSET2  SECTYP=HEX,"                                                  	<<endl
				<< "           SSPAN=0.14,0.21,0.29,"                                    		<<endl
				<< "           CHORD=0.296,0.2279,0.15,"                                  		<<endl
				<< "           XLE=4.5,4.534,4.573,"                                            <<endl
				<< "           NPANEL=4.0,"                                                 	<<endl
				<< "           PHIF=0.0,90.0,180.0,270.0,"                               		<<endl
				<< "           ZUPPER=0.01689,0.02194,0.006,LMAXU=0.3378,0.4388,0.01,"        	<<endl
				<< "           LFLATU=0.3244,0.1224,0.98,"                                     	<<endl
				<< " $END"                                                                    	<<endl

				<< " $DEFLCT  DELTA2=0.0,0.0,0.0,0.0,"                                        	<<endl
				<< "          XHINGE=4.648,"                                                  	<<endl
				<< " $END"                                                                     	<<endl
				<< "DAMP"                                                                      	<<endl
				<< "SAVE"                                                                     	<<endl
				<< "NEXT CASE"                                                                	<<endl;

	return true;
}



bool MDAeroPAC3MSE::writeTheCase(ofstream &outputFile, double hin, double betain, double deltaAin, double deltaEin, double deltaRin, string config){
	double H = 0.14;
	double l=0.98;//0.98
	double h=0.1275;
	double r=(l*l+h*h)/2.0/h;
	//y=sqrt(r*r-(x-l)*(x-l))-(r-h);
	double X[48]={	0.0 , 0.03, 0.06, 0.09, 0.12, 0.15, 0.20, 0.25, 0.30, 0.35,
					0.40, 0.45, 0.50, 0.56, 0.70, 0.82, 0.9, 0.95, 0.98, 1.02,    //0.56, 0.70, 0.82, 0.9, 0.95, 0.98, 1.02,
					1.08, 1.18, 1.3, 1.4, 1.56, 1.76, 2.086, 2.10, 2.13, 2.161,       //2.086, 2.10, 2.13, 2.161,
					2.18, 2.24, 2.35, 2.408, 2.45, 2.5, 3.0, 3.73, 4.13, 4.53,        //DCON 2.086 2.161 2.408 5.042   .... 27 30 34 43
					4.93, 5.0, 5.06, 5.12, 5.14, 5.16, 5.18, 5.2 };
	double R[48]={0.};
	for(int i=0;i<48;i++){
		if(X[i]<0.98){
			R[i] = sqrt(r*r-(X[i]-l)*(X[i]-l))-(r-h);
		}
		else if(X[i]<2.086){
			R[i] = h;
		}
		else if(X[i]<2.161){
			R[i] = h+(0.135-h)/(2.161-2.086)*(X[i]-2.086);
		}
		else if(X[i]<2.408){
			R[i] = 0.135+(H-0.135)/(2.408-2.161)*(X[i]-2.161);
		}
		else if(X[i]<5.06){
			R[i] = H;
		}
		else{
			R[i] = H+(0.12-H)/(5.2-5.06)*(X[i]-5.06);
		}

	}

	//initial case
	outputFile  << "CASEID PAC-3MSE BODY AND FINS WITH C.G. SPECIFIED"                       	<<endl
			    << "DIM M"                                                                     	<<endl
				<< " $FLTCON  NALPHA=13.0,"                                                    	<<endl
				<< "          ALPHA=-40.,-30.,-20.,-15.,-10.,-5.,0.,"                   		<<endl
				<< "                5.,10.,15.,20.,30.,40.,"                     				<<endl
				<< "          NMACH=10.,"                                                      	<<endl
				<< "          MACH=0.1,0.5,1.0,"  												<<endl
				<< "               1.5,2.0,3.0,4.0,5.0,6.0,7.0,"  								<<endl
				<< "          ALT=";
	for(int i=0;i<10;i++)
	{
		outputFile  << fixed << setprecision(2) << hin << ",";
		if(i%6==5){
			outputFile  << "\n"
					    << "              ";
		}
	}
	outputFile  << "\n"
				<< "          BETA=" << fixed << setprecision(2) << betain << ","             	<<endl
				<< " $END"                                                                     	<<endl

				<< " $REFQ  SREF=0.062,"                                                        <<endl
				<< "        LREF=5.2,"                   										<<endl
				<< "        XCG=0.,"                     										<<endl
				<< "        ZCG=0.,"                                                            <<endl
				<< "        RHR=50.,"                                                   		<<endl
				<< " $END"                                                                     	<<endl

				<< " $AXIBOD  NX=48.,"                                                          <<endl
				<< "          X=";
	for(int i=0;i<48;i++){
		outputFile  << fixed << setprecision(3) << X[i] << ",";
		if(i%10==9){
			outputFile  << "\n"
						<< "            ";
		}
	}
	outputFile  << "\n"
				<< "          R=";
	for(int i=0;i<48;i++){
		outputFile  << fixed << setprecision(6) << R[i] << ",";
		if(i%6==5){
			outputFile  << "\n"
						<< "            ";
		}
	}
	outputFile  << "\n";
	outputFile  << "          DISCON=27.,30.,34.,43.,"           								<<endl
				<< "          LNOSE=2.408,"                   									<<endl
				<< "          DNOSE=0.28,"                   									<<endl
				<< "          LCENTR=2.652,"                  									<<endl
				<< "          LAFT=0.14,"                     									<<endl
				<< "          DAFT=0.24,"                   									<<endl
				<< "          DEXIT=0.,"                     									<<endl
				<< " $END"
                                                                                                <<endl
				<< " $FINSET1  SECTYP=HEX,"                                                   	<<endl
				<< "           SSPAN=0.14,0.205,"                                              	<<endl
				<< "           CHORD=1.043,0.809,"                                             	<<endl
				<< "           XLE=2.689,2.861,"                                               	<<endl
				<< "           NPANEL=4.0,"                                                   	<<endl
				<< "           PHIF=0.0,90.0,180.0,270.0,"                                     	<<endl
				<< "           ZUPPER=0.006,0.0037,LMAXU=0.171,0.1,LFLATU=0.7596,0.8,"          <<endl
				<< " $END"                                                                     	<<endl

				<< " $FINSET2  SECTYP=HEX,"                                                    	<<endl
				<< "           SSPAN=0.14,0.21,0.29,"                                          	<<endl
				<< "           CHORD=0.296,0.2279,0.15,"                                       	<<endl
				<< "           XLE=4.5,4.534,4.573,"                                            <<endl
				<< "           NPANEL=4.0,"                                                   	<<endl
				<< "           PHIF=0.0,90.0,180.0,270.0,"                                     	<<endl
				<< "           ZUPPER=0.01689,0.02194,0.006,LMAXU=0.3378,0.4388,0.01,"        	<<endl
				<< "           LFLATU=0.3244,0.1224,0.98,"                                    	<<endl
				<< " $END"                                                                    	<<endl;

	double delta1,delta2,delta3,delta4;
	if(config == "+"){
		delta1 = deltaAin - deltaRin;
		delta2 = deltaAin + deltaEin;
		delta3 = deltaAin + deltaRin;
		delta4 = deltaAin - deltaEin;
	}else if (config == "x") {
		delta1 = deltaAin + deltaEin - deltaRin;
		delta2 = deltaAin + deltaEin + deltaRin;
		delta3 = deltaAin - deltaEin + deltaRin;
		delta4 = deltaAin - deltaEin - deltaRin;
	}
	else
	{
		std::cerr << "wrong config parameter!\n";
	}
	

	outputFile	<< " $DEFLCT  DELTA2=" << fixed << setprecision(2) << delta1 << ","
									   << fixed << setprecision(2) << delta2 << ","
									   << fixed << setprecision(2) << delta3 << ","
									   << fixed << setprecision(2) << delta4 << ","				<<endl
				<< "          XHINGE=4.648,"                                                   	<<endl
				<< " $END"                                                                     	<<endl
				<< "DAMP"                                                                     	<<endl
				<< "SAVE"                                                                     	<<endl
				<< "NEXT CASE"                                                                	<<endl;

	return true;
}






bool MDAeroPAC3MSE::writeChangeFLTCON_DEFLCTCase(ofstream &outputFile, double h, double beta, double deltaA, double deltaE, double deltaR, string config){
	outputFile  << "CASEID PAC-3MSE FLTCON Change H=" << h << ";  beta=" << beta              	<<endl
			    << "DELETE FLTCON"                                                           	<<endl
				<< " $FLTCON  NALPHA=13.0,"                                                   	<<endl
				<< "          ALPHA=-40.,-30.,-20.,-15.,-10.,-5.,0.,"                   		<<endl
				<< "                5.,10.,15.,20.,30.,40.,"                     				<<endl
				<< "          NMACH=10.,"                                                      	<<endl
				<< "          MACH=0.1,0.5,1.0,"  												<<endl
				<< "               1.5,2.0,3.0,4.0,5.0,6.0,7.0,"  								<<endl
				<< "          ALT=";
	for(int i=0;i<10;i++)
	{
		outputFile  << fixed << setprecision(2) << h << ",";
		if(i%6==5){
			outputFile  << "\n"
					    << "              ";
		}
	}
	outputFile  << "\n"
				<< "          BETA=" << fixed << setprecision(2) << beta <<","               	<<endl
				<< " $END"                                                                     	<<endl;

	double delta1,delta2,delta3,delta4;
	if(config == "+"){
		delta1 = deltaA - deltaR;
		delta2 = deltaA + deltaE;
		delta3 = deltaA + deltaR;
		delta4 = deltaA - deltaE;
	}else if (config == "x") {
		delta1 = deltaA + deltaE - deltaR;
		delta2 = deltaA + deltaE + deltaR;
		delta3 = deltaA - deltaE + deltaR;
		delta4 = deltaA - deltaE - deltaR;
	}
	else
	{
		std::cerr << "wrong config parameter!\n";
	}
	outputFile  << "DELETE DEFLCT"                                                             	<<endl
				<< " $DEFLCT  DELTA2=" << fixed << setprecision(2) << delta1 << ","
									   << fixed << setprecision(2) << delta2 << ","
									   << fixed << setprecision(2) << delta3 << ","
									   << fixed << setprecision(2) << delta4 << ","				<<endl
				<< "          XHINGE=4.648,"                                                   	<<endl
				<< " $END"                                                                    	<<endl
				<< "DAMP"                                                                      	<<endl
				<< "SAVE"                                                                      	<<endl
				<< "NEXT CASE"                                                                 	<<endl;

	return true;
}

bool MDAeroPAC3MSE::writeChangeFLTCONCase(ofstream &outputFile, double h, double beta){
	outputFile  << "CASEID PAC-3MSE FLTCON Change H=" << h << ";  beta=" << beta              	<<endl
			    << "DELETE FLTCON"                                                            	<<endl
				<< " $FLTCON  NALPHA=13.0,"                                                    	<<endl
				<< "          ALPHA=-40.,-30.,-20.,-15.,-10.,-5.,0.,"                   		<<endl
				<< "                5.,10.,15.,20.,30.,40.,"                     				<<endl
				<< "          NMACH=10.,"                                                      	<<endl
				<< "          MACH=0.1,0.5,1.0,1.5,2.0,3.0,4.0,5.0,6.0,7.0,"                   	<<endl
				<< "          ALT=";
	for(int i=0;i<10;i++)
	{
		outputFile  << fixed << setprecision(2) << h << ",";
		if(i%6==5){
			outputFile  << "\n"
					    << "              ";
		}
	}
	outputFile  << "\n"
				<< "          BETA="<< fixed << setprecision(2) << beta << ","               	<<endl
				<< " $END"                                                                     	<<endl
				<< "DAMP"                                                                      	<<endl
				<< "SAVE"                                                                      	<<endl
				<< "NEXT CASE"                                                                 	<<endl;

	return true;
}


bool MDAeroPAC3MSE::writeChangeDEFLCTCase(ofstream &outputFile, double deltaA, double deltaE, double deltaR, string config)
{
	double delta1,delta2,delta3,delta4;
	if(config == "+"){
		delta1 = deltaA - deltaR;
		delta2 = deltaA + deltaE;
		delta3 = deltaA + deltaR;
		delta4 = deltaA - deltaE;
	}else if (config == "x") {
		delta1 = deltaA + deltaE - deltaR;
		delta2 = deltaA + deltaE + deltaR;
		delta3 = deltaA - deltaE + deltaR;
		delta4 = deltaA - deltaE - deltaR;
	}
	else
	{
		std::cerr << "wrong config parameter!\n";
	}
	outputFile  << "CASEID PAC-3MSE DEFLCT Change deltaA=" << deltaA << "; deltaE=" 
				<< deltaE << "; deltaR=" << deltaR     											<<endl
			    << "DELETE DEFLCT"                                                             	<<endl
				<< " $DEFLCT  DELTA2=" << fixed << setprecision(2) << delta1 << ","
				                       << fixed << setprecision(2) << delta2 << ","
									   << fixed << setprecision(2) << delta3 << ","
									   << fixed << setprecision(2) << delta4 << ","				<<endl
				<< "          XHINGE=4.648,"                                                   	<<endl
				<< " $END"                                                                     	<<endl
				<< "DAMP"                                                                      	<<endl
				<< "SAVE"                                                                      	<<endl
				<< "NEXT CASE"                                                                 	<<endl;

	return true;
}



MDAeroPAC3MSE::~MDAeroPAC3MSE() {
	// TODO Auto-generated destructor stub
}

} /* namespace MissileDatcom */
