// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 在此处引用程序需要的其他头文件

/*

运行外部工具 wsdl2h -c -o calc.h http://www.genivia.com/calc.wsdl
运行外部工具 soapcpp2 -S -L calc.h

将生成的文件 soapServer.c  soapC.c soapH.h  soapStub.h  等增加到本工程
将 gsoap-2.8\gsoap 目录下的 stdsoap2.h  stdsoap2.c 增加到本工程

服务器要实现的接口函数在 soapStub.h 中

*/