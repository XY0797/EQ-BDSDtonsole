// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
//GB2312到UTF-8的转换
static char* GB2312ToUtf8(const char* gb2312)//记得释放内存！！
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* utf8 = new char[len + 1];
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return utf8;
}
//UTF-8到GB2312的转换
static char* Utf8ToGB2312(const char* utf8)//记得释放内存！！
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* gb2312 = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, gb2312, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return gb2312;
}


//创建js对象，返回指针
//panicFunction要求一个参数接收js对象指针
//reportFunction要求两个参数，第一个接收指针，第二个接收错误信息
js_State* WINAPI CreatNewJsObj(js_Panic panicFunction, js_Report reportFunction) {
	js_State* ptr = js_newstate(NULL, NULL, JS_STRICT);
	js_atpanic(ptr,panicFunction);
	js_setreport(ptr, reportFunction);
	return ptr;
}

//销毁js对象
void WINAPI DestroyJsObj(js_State* jsObjPointer) {
	js_freestate(jsObjPointer);
}
//注册js函数，函数指针必须有一个参数接收js对象
void WINAPI RegFunction(js_State* jsObjPointer, js_CPPFunction FunctionPointer, char* FunctionNameInJs, long ArgumentNumber) {
	char* UTF8FunctionNameInJs=GB2312ToUtf8(FunctionNameInJs);
	js_newcppfunction(jsObjPointer, FunctionPointer, UTF8FunctionNameInJs, ArgumentNumber);
	js_setglobal(jsObjPointer, UTF8FunctionNameInJs);
	delete[] UTF8FunctionNameInJs;
}

//执行js代码
void WINAPI ExecuteJsCode(js_State* jsObjPointer, char* JsCode) {
	char* UTF8JsCode = GB2312ToUtf8(JsCode);
	js_dostring(jsObjPointer, UTF8JsCode);
	delete[] UTF8JsCode;
}



//函数返回null型
void WINAPI js_returnNull(js_State* J) {
	js_pushnull(J);
}

//函数返回易语言逻辑型
void WINAPI js_returnBoolean(js_State* J, int v) {
	js_pushboolean(J, v);
}

//函数返回易语言双精度小数型
void WINAPI js_returnNumber(js_State* J, double v) {
	js_pushnumber(J, v);
}

//函数返回易语言文本型，注意指定长度
void WINAPI js_returnlString(js_State* J, char* v) {
	int len = MultiByteToWideChar(CP_ACP, 0, v, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, v, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* utf8 = new char[len + 1];
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8, len, NULL, NULL);
	if (wstr) delete[] wstr;
	js_pushlstring(J, utf8, len);
	delete[] utf8;
}



//易语言逻辑型
int WINAPI js_getBoolean(js_State* J, int idx) {
	return js_toboolean(J, idx);
}

//易语言双精度小数型
double WINAPI js_getNumber(js_State* J, int idx) {
	return js_tonumber(J, idx);
}

//易语言整数型
int WINAPI js_getInt32(js_State* J, int idx) {
	return js_toint32(J, idx);
}

//易语言短整数型
short WINAPI js_getInt16(js_State* J, int idx) {
	return js_toint16(J, idx);
}

//易语言文本型
const char* WINAPI js_getString(js_State* J, int idx) {
	char* GB2312Str = Utf8ToGB2312(js_tostring(J, idx));
	return GB2312Str;
	//return js_tostring(J, idx);
}

//释放文本型指针
void WINAPI deleteString(char* lpStr) {
	delete[] lpStr;
}