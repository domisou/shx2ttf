// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

//------------------------
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

#include <WinSock2.h>
#include <Windows.h>

#include "ZvLibs.h"
using namespace ZvLibs;


// TODO: 在此处引用程序需要的其他头文件

typedef  struct {
	string CmdType;
	string DeviceSN;
	int		DeviceType;
	string	DeviceName;
	string	DeviceMac;
	string	SoftVersion;
	string	HardVersion;

	string	SessionID;

} SnDevice;