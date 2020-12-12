/*
 * IMissileDatcomAeroCompt.h
 *
 *  Created on: Dec 11, 2020
 *      Author: htallone
 */

#ifndef IMISSILEDATCOMAEROCOMPT_H_
#define IMISSILEDATCOMAEROCOMPT_H_

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

namespace MissileDatcom {

//! 用于估算气动系数的抽象接口类
/*!
 * 
 */
class IMissileDatcomAeroCompt {
public:
	IMissileDatcomAeroCompt();
	IMissileDatcomAeroCompt(vector<double> hp,vector<double> betap,vector<double> deltaAp,vector<double> deltaEp,vector<double> deltaRp);
	virtual ~IMissileDatcomAeroCompt() = 0;

	//! 写用于MD计算的初始Case，就是往for005文件写一个初始的标准case
	/*!
	 *  @param [in] outputFile  输入到for005的文件流
	 */
	virtual bool writeInitalCase(ofstream &outputFile) = 0;

	//! 接着初始Case，往for005文件续写改变飞行条件和舵偏角的case，要配合 writeInitalCase 函数
	/*!
	 *  @param [in] outputFile  输入到for005的文件流
	 *  @param [in] h  飞行条件高度
	 *  @param [in] beta  飞行条件侧滑角
	 *  @param [in] deltaA  滚转 虚拟舵偏角
	 *  @param [in] deltaE  俯仰 虚拟舵偏角
	 *  @param [in] deltaR  偏航 虚拟舵偏角
	 *  @param [in] config  四片舵采用"+"还是"x"配置，前面输入虚拟舵偏角，需要按照控制配置转化为实际舵偏角进行计算
	 */
	virtual bool writeChangeFLTCON_DEFLCTCase(ofstream &outputFile, double h, double beta, double deltaA, double deltaE, double deltaR, string config = "+") = 0;
	
	//! 接着初始Case，往for005文件续写只改变飞行条件的case，要配合 writeInitalCase 函数
	/*!
	 *  @param [in] outputFile  输入到for005的文件流
	 *  @param [in] h  飞行条件高度
	 *  @param [in] beta  飞行条件侧滑角
	 */
	virtual bool writeChangeFLTCONCase(ofstream &outputFile, double h, double beta)=0;

	//! 接着初始Case，往for005文件续写只改变舵偏角的case，要配合 writeInitalCase 函数
	/*!
	 *  @param [in] outputFile  输入到for005的文件流
	 *  @param [in] deltaA  滚转 虚拟舵偏角
	 *  @param [in] deltaE  俯仰 虚拟舵偏角
	 *  @param [in] deltaR  偏航 虚拟舵偏角
	 *  @param [in] config  四片舵采用"+"还是"x"配置，前面输入虚拟舵偏角，需要按照控制配置转化为实际舵偏角进行计算
	 */
	virtual bool writeChangeDEFLCTCase(ofstream &outputFile, double deltaA, double deltaE, double deltaR, string config = "+")=0;

	//! 往for005文件写一个改变飞行条件和舵偏角的case，这个是覆盖原for005文件，用于大样本case循环调用MD程序
	/*!
	 *  @param [in] outputFile  输入到for005的文件流
	 *  @param [in] hin  飞行条件高度
	 *  @param [in] betain  飞行条件侧滑角
	 *  @param [in] deltaAin  滚转 虚拟舵偏角
	 *  @param [in] deltaEin  俯仰 虚拟舵偏角
	 *  @param [in] deltaRin  偏航 虚拟舵偏角
	 *  @param [in] config  四片舵采用"+"还是"x"配置，前面输入虚拟舵偏角，需要按照控制配置转化为实际舵偏角进行计算
	 */
	virtual bool writeTheCase(ofstream &outputFile, double hin, double betain, double deltaAin, double deltaEin, double deltaRin, string config = "+")=0;

	//! 先写一个用于MD计算的初始Case，然后按照成员变量飞行条件和舵偏角数据，
	//! 调用writeChangeFLTCON_DEFLCTCase 往for005文件续写这些case，
	//! 最后生成一个包含所有case的for005文件，调用1次MD程序即可，
	//! 但是，MD程序好像一次只能计算几十个case吧，多了就不行了，而且这个函数默认"+"配置。
	//! 小样本case可以用这个函数，采样较多时还是要用 writeTheCase 循环调用、存储结果数据
	virtual bool generateInitialFor005File();

private:
	vector<double> h;	//!< 高度采样数据
	vector<double> beta;//!< 侧滑角采样数据
	vector<double> deltaA;//!< 滚转 虚拟舵偏角采样数据
	vector<double> deltaE;//!< 俯仰 虚拟舵偏角采样数据
	vector<double> deltaR;//!< 偏航 虚拟舵偏角采样数据
};

} /* namespace MissileDatcom */

#endif /* IMISSILEDATCOMAEROCOMPT_H_ */
