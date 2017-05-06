#pragma once
#include <string>

class CHttpClient
{
public:
	CHttpClient(void);
	virtual ~CHttpClient(void);

public:
	/**
	* @brief HTTP POST请求
	* @param strUrl 输入参数,请求的Url地址,如:http://www.baidu.com
	* @param strBody 输入参数,发送的http包体
	* @param strResponse 输出参数,返回的内容
	* @return 返回是否Post成功
	*/
	int Post(const std::string & strUrl, const std::string & strBody, std::string & strResponse);

	/**
	* @brief HTTP GET请求
	* @param strUrl 输入参数,请求的Url地址,如:http://www.baidu.com
	* @param strResponse 输出参数,返回的内容
	* @return 返回是否Post成功
	*/
	int Get(const std::string & strUrl, std::string & strResponse);

	/**
	* @brief HTTPS POST请求,无证书版本
	* @param strUrl 输入参数,请求的Url地址,如:https://www.alipay.com
	* @param strBody 输入参数,发送的http包体
	* @param strResponse 输出参数,返回的内容
	* @param pCaPath 输入参数,为CA证书的路径.如果输入为NULL,则不验证服务器端证书的有效性.
	* @return 返回是否Post成功
	*/
	int Posts(const std::string & strUrl, const std::string & strBody, std::string & strResponse, const char * pCaPath = NULL);

	/**
	* @brief HTTPS GET请求,无证书版本
	* @param strUrl 输入参数,请求的Url地址,如:https://www.alipay.com
	* @param strResponse 输出参数,返回的内容
	* @param pCaPath 输入参数,为CA证书的路径.如果输入为NULL,则不验证服务器端证书的有效性.
	* @return 返回是否Post成功
	*/
	int Gets(const std::string & strUrl, std::string & strResponse, const char * pCaPath = NULL);

	/**
	* @brief HTTP POST请求
	* @param strUrl 输入参数,请求的Url地址,如:http://www.baidu.com
	* @param strFileName 输入参数,发送的文件
	* @param strResponse 输出参数,返回的内容
	* @return 返回是否Post成功
	*/
	int UploadFile(const std::string & strUrl, const std::string & utf8FileName, std::string & strResponse);

public:
	void SetDebug(bool bDebug);

private:
	bool m_bDebug;
};


