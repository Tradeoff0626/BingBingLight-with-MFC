#pragma once
#include "afxwin.h"

#define	MAX_PATTERN_COUNT	256
#define MAX_LED_COUNT		24
#define MAX_DISPLAY_COUNT	128


#define PIXEL_SIZE	7


enum enumColor {BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, SKYBLUE, WHITE, GRAY};


//에디트 뷰에 배치되는 컬러 픽셀 정보
typedef struct _PIXELDISPINFO
{
	enum enumColor		pixelColor;
} PIXELDISPINFO;


//MMAP 데이터 파일에서 읽어온 현재 에디터 뷰의 정보는 멤버 변수에 바로 대입
//아래 구조체는 최대 패턴 256개만큼 배열을 선언하여 프로그램에서도 관리하며, MMAP 파일에서 헤더로도 사용.
typedef struct _PATTERNINFO
{
	int ledCnt;		//해당 패턴의 led 개수
	int DispCnt;	//패턴의 상태 개수
	BOOL enable;	//패턴이 사용되는 것인지 여부 체크
} PATTERNINFO, *PPATTERNINFO;

//MMAP용 데이터 파일의 데이터
typedef struct _PIXELTABLEDATA
{
	int tableIndex;						//픽셀 테이블의 인덱스
	int dispCnt;						//해당 테이블의 디스플레이 개수
	PIXELDISPINFO pPixelTable[MAX_LED_COUNT][MAX_DISPLAY_COUNT];		//픽셀 테이블의 주소값.	MEMCPY로 복사해야됨.
} PIXELTABLEDATA, *PPIXELTABLEDATA;


//시리얼로 전송할 (파일 저장용?)할 에디터 뷰의 픽셀 값을 전송용 데이터로 변환하여 저장할 용도의 구조체
typedef struct _LEDCOLORREF
{
	BYTE red1;			
	BYTE red2;
	BYTE red3;			//RED - 24 bits
	BYTE green1;		
	BYTE green2;
	BYTE green3;		//GREEN - 24 bits
	BYTE blue1;		
	BYTE blue2;
	BYTE blue3;		//BLUE - 24 bits
} LEDCOLORREF;