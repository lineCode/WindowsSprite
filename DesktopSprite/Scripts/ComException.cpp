#include <Windows.h>

struct ComException
{
	HRESULT result;
	ComException(HRESULT const value) :result(value)
	{
		LPVOID lpMsgBuf;
		LPVOID lpDisplayBuf;
		DWORD dw = GetLastError();
		LPTSTR errorText = NULL;
		//_com_error error(hresult);
		FormatMessage(
			FORMAT_MESSAGE_FROM_SYSTEM
			| FORMAT_MESSAGE_ALLOCATE_BUFFER
			| FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			value,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&errorText,  // output 
			0, // minimum size for output buffer
			NULL);   // arguments - see note 

		if (NULL != errorText)
		{
			MessageBox(NULL, errorText, TEXT("ComException"), NULL);
			// release memory allocated by FormatMessage()
			LocalFree(errorText);
			errorText = NULL;
		}
	}
};

void HR(HRESULT const result)
{
	if (S_OK != result)
		throw ComException(result);
}
