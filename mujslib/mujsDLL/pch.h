// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。
#include "mujs.h"
#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#include "framework.h"

#endif //PCH_H

extern "C" {
	__declspec(dllexport) js_State* WINAPI CreatNewJsObj(js_Panic panicFunction, js_Report reportFunction); //创建js对象，返回指针。panicFunction要求一个参数接收js对象指针。reportFunction要求两个参数，第一个接收指针，第二个接收错误信息。

	__declspec(dllexport) void WINAPI DestroyJsObj(js_State* jsObjPointer); //销毁js对象

	__declspec(dllexport) void WINAPI RegFunction(js_State* jsObjPointer, js_CPPFunction FunctionPointer, char* FunctionNameInJs, long ArgumentNumber); //注册js函数，函数指针必须有一个参数接收js对象

	__declspec(dllexport) void WINAPI js_returnNull(js_State* J); //函数返回null型
	__declspec(dllexport) void WINAPI js_returnBoolean(js_State* J, int v); //函数返回易语言逻辑型
	__declspec(dllexport) void WINAPI js_returnNumber(js_State* J, double v); //函数返回易语言双精度小数型
	__declspec(dllexport) void WINAPI js_returnlString(js_State* J, char* v); //函数返回易语言文本型

	__declspec(dllexport) int WINAPI js_getBoolean(js_State* J, int idx); //易语言逻辑型
	__declspec(dllexport) double WINAPI js_getNumber(js_State* J, int idx); //易语言双精度小数型
	__declspec(dllexport) int WINAPI js_getInt32(js_State* J, int idx); //易语言整数型
	__declspec(dllexport) short WINAPI js_getInt16(js_State* J, int idx); //易语言短整数型
	__declspec(dllexport) const char* WINAPI js_getString(js_State* J, int idx); //易语言文本型
	__declspec(dllexport) void WINAPI deleteString(char* lpStr); //释放文本型指针

	__declspec(dllexport) void WINAPI ExecuteJsCode(js_State* jsObjPointer, char* JsCode); //执行js代码
}