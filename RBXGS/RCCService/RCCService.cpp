// entry point file
// by mike
// v2026.0124
#include "StdAfx.h"
#include "soapH.h"
#include <conio.h>
#define SVCNAME "RCCService"

SOAP_SOCKET soap_bind(int one, int two, int three, int four) {
	return SOAP_OK;
}

VOID WINAPI mainService(DWORD dwArgc, LPTSTR *lpszArgv) {};

HANDLE startRCCService(int port) { // this seems to be a __thiscall, try to find the parent class?
	char messageBuffer[68];

	// call_once((int)sub_407350, &dword_79EE48);
	//initWebService();
	if (soap_bind(NULL, NULL, port, 100) == SOAP_INVALID_SOCKET) {
		//sub_424DA0();
		//if ( word_776C26 == 2 )
			//v2 = *(_DWORD **)(dword_779BD0 + 20);
		//else
			//v2 = (_DWORD *)(dword_779BD0 + 4);
		//std::string::string(v8, *v2);
		//v11 = 0;
		//sub_402220(v8);
		//throw std::runtime_error(""); // should put a message here
	}
	sprintf_s(messageBuffer, 0x40, "Service Started on port %d", port);
	printf("%s\n", messageBuffer);
	
	HANDLE hEventLog = RegisterEventSource(NULL, SVCNAME);
	if (hEventLog) {
		ReportEvent(hEventLog, EVENTLOG_INFORMATION_TYPE, 0x0, 0x20000001, NULL, 1, 0, (LPCSTR *)&messageBuffer, NULL);
		return (HANDLE)DeregisterEventSource(hEventLog);
	}
	return hEventLog;
}

void stepRCC() {};

int main(int argc, char *argv[]) {
	bool useServiceDispatcher = true; // for some reason this was a char, we'll make this a boolean
	bool isConsoleEnabled = false; // this too

	int charIndex = 1;
	char currentCharacter;
	while (charIndex < argc) { // parse args
		currentCharacter = argv[charIndex][0];
		if (currentCharacter == '/')
			argv[charIndex][0] = '-';
		if (_stricmp(argv[charIndex], "-Install") == 0) {
			// sub_406350(v10, v11);
			// sub_4064B0(v10, v11);
			useServiceDispatcher = false;
		}
		if (_stricmp(argv[charIndex], "-Uninstall") == 0) {
			// sub_406190();
			// sub_4062F0();
			useServiceDispatcher = false;
		}
		if (_stricmp(argv[charIndex], "-Start") == 0) {
			// sub_4061F0();
			useServiceDispatcher = false;
		}
		if (_stricmp(argv[charIndex], "-Stop") == 0) {
			// sub_406280();
			useServiceDispatcher = false;
		}
		if (_stricmp(argv[charIndex], "-Console") == 0) {
			isConsoleEnabled = true;
			useServiceDispatcher = false;
		}

		charIndex++;
	}

	if (isConsoleEnabled) {
		int port = 64989;
		char portCurrentCharacter;
		for (int i = 1; i < argc; ++i)
		{
			portCurrentCharacter = *argv[i];
			if (portCurrentCharacter != '/' && portCurrentCharacter != '-')
				port = atoi(argv[i]);
		}
		
		startRCCService(port);
		printf("Press ESC key to exit\n");
		while (!kbhit() || getch() != '\x1B') // \x1B is ESC
			stepRCC();
		printf("Service Shut Down\n");
	} else if (useServiceDispatcher) {
		SERVICE_TABLE_ENTRY serviceTableInfo[] = {
			{SVCNAME, mainService}, //(LPSERVICE_MAIN_FUNCTIONA)sub_406040;
			{NULL, NULL}
		};
		if (!StartServiceCtrlDispatcher(serviceTableInfo))
			printf("StartServiceCtrlDispatcher failed (%d)\n", GetLastError());
	}
	return EXIT_SUCCESS;
}