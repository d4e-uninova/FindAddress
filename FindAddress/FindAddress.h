#define MAXPTR 999

#ifndef _NATIVELIB_H_
#define _NATIVELIB_H_

#ifndef API
#define API
#endif

#ifdef __cplusplus
extern "C" {
#endif

	API int  FindAddress(int pid, char *data, int startAddress,int endAddress, int ** ptrArr);

#ifdef __cplusplus
}
#endif

#endif // _NATIVELIB_H_