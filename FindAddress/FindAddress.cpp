#include "stdafx.h"
#include "FindAddress.h"
#include <windows.h>
#include <vector>

void GetAddressOfData(DWORD pid, const char *data, size_t len, int startAddress,int endAddress,int* ptrArr,int* pos)
{
	HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (process)
	{
		
		SYSTEM_INFO si;
		GetSystemInfo(&si);
		int endAddress_ = (int)si.lpMaximumApplicationAddress < endAddress ? (int)si.lpMaximumApplicationAddress : endAddress;
		MEMORY_BASIC_INFORMATION info;
		std::vector<char> chunk;
		char* p = (char*)startAddress;
		while ((int)p <endAddress_)
		{
			if (VirtualQueryEx(process, p, &info, sizeof(info)) == sizeof(info))
			{
				//p =  (char*)info.BaseAddress;
				chunk.resize(info.RegionSize);
				SIZE_T bytesRead;
				if (ReadProcessMemory(process, p, &chunk[0], info.RegionSize, &bytesRead))
				{
					for (size_t i = 0; i < (bytesRead - len); ++i)
					{
						if (memcmp(data, &chunk[i], len) == 0)
						{
							ptrArr[*pos] = (int)((char*)p + i);
							(*pos)++;
							if ((*pos) == MAXPTR)
							{
								break;
							}
						}
					}
				}
				p += info.RegionSize;
			}
		}
	}
}



API int FindAddress(int pid, char *data,int startAddress,int endAddress,int** ptrArr)
{

	int wr;
	int pos = 0;
	*ptrArr= new int[MAXPTR];
	DWORD pid_ = (DWORD)pid;
	GetAddressOfData(pid_, data, sizeof(data), startAddress,endAddress,*ptrArr,&pos);
	

	return pos;

}