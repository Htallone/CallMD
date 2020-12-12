/*
 * textFileManipulation.h
 *
 *  Created on: Dec 11, 2020
 *      Author: htallone
 */

#ifndef TEXTFILEMANIPULATION_H_
#define TEXTFILEMANIPULATION_H_

#include <string>

//! for042文件处理函数
/*!
 * 分离Header行和数据，保存到两个文本文件中，便于处理
 * @param [in] for042PathName  原for042文件路径字符串
 * @param [in] for042HeaderFileName 保存for042文件中Header行的文件名字字符串
 * @param [in] for042DataFileName 保存for042文件中数据的文件名字字符串
 */
void for042FileToHeaderAndData(const std::string & for042PathName,
		const std::string & for042HeaderFileName ,
		const std::string & for042DataFileName);


#endif /* TEXTFILEMANIPULATION_H_ */
