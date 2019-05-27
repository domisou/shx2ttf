// SoapCalcServer.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "calc.nsmap" // XML namespace mapping table (only needed once at the global level)
#include "soapH.h"    // client stubs, serializers, etc.

int main()
{
	//	启动一个 stand-alone server
	struct soap *soap = soap_new1(SOAP_XML_INDENT);
	if (!soap_valid_socket(soap_bind(soap, NULL, 8080, 100)))
		exit(EXIT_FAILURE);
	while (soap_valid_socket(soap_accept(soap)))
	{
		if (soap_serve(soap) != SOAP_OK)
			break;
		soap_destroy(soap); // delete deserialized objects
		soap_end(soap);     // delete allocated (deserialized) data
	}
	soap_print_fault(soap, stderr);
	soap_free(soap); // free the soap struct context data
    return 0;
}

int ns2__add(struct soap *soap, double a, double b, double *result)
{
	*result = a + b;
	return SOAP_OK;
}
int ns2__sub(struct soap *soap, double a, double b, double *result)
{
	*result = a - b;
	return SOAP_OK;
}
int ns2__mul(struct soap *soap, double a, double b, double *result)
{
	*result = a * b;
	return SOAP_OK;
}
int ns2__div(struct soap *soap, double a, double b, double *result)
{
	if (b == 0.0)
	{
		char *msg = (char*)soap_malloc(soap, 1024);
		snprintf(msg, 1024, "Trying to divide %f by zero", a);
		return soap_sender_fault(soap, msg, NULL);
	}
	*result = a / b;
	return SOAP_OK;
}
int ns2__pow(struct soap *soap, double a, double b, double *result)
{
	*result = ::pow(a, b);
	// soap_errno is like errno, but compatible with Win32
	if (soap_errno == EDOM)
	{
		char *msg = (char*)soap_malloc(soap, 1024);
		snprintf(msg, 1024, "<error xmlns=\"http://tempuri.org/\">Can't take power of %f to %f</error>", a, b);
		return soap_sender_fault(soap, "Power function domain error", msg);
	}
	return SOAP_OK;
}

