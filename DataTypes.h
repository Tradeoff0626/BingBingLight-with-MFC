#pragma once
#include "afxwin.h"

#define	MAX_PATTERN_COUNT	256
#define MAX_LED_COUNT		24
#define MAX_DISPLAY_COUNT	128


#define PIXEL_SIZE	7


enum enumColor {BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, SKYBLUE, WHITE, GRAY};


//����Ʈ �信 ��ġ�Ǵ� �÷� �ȼ� ����
typedef struct _PIXELDISPINFO
{
	enum enumColor		pixelColor;
} PIXELDISPINFO;


//MMAP ������ ���Ͽ��� �о�� ���� ������ ���� ������ ��� ������ �ٷ� ����
//�Ʒ� ����ü�� �ִ� ���� 256����ŭ �迭�� �����Ͽ� ���α׷������� �����ϸ�, MMAP ���Ͽ��� ����ε� ���.
typedef struct _PATTERNINFO
{
	int ledCnt;		//�ش� ������ led ����
	int DispCnt;	//������ ���� ����
	BOOL enable;	//������ ���Ǵ� ������ ���� üũ
} PATTERNINFO, *PPATTERNINFO;

//MMAP�� ������ ������ ������
typedef struct _PIXELTABLEDATA
{
	int tableIndex;						//�ȼ� ���̺��� �ε���
	int dispCnt;						//�ش� ���̺��� ���÷��� ����
	PIXELDISPINFO pPixelTable[MAX_LED_COUNT][MAX_DISPLAY_COUNT];		//�ȼ� ���̺��� �ּҰ�.	MEMCPY�� �����ؾߵ�.
} PIXELTABLEDATA, *PPIXELTABLEDATA;


//�ø���� ������ (���� �����?)�� ������ ���� �ȼ� ���� ���ۿ� �����ͷ� ��ȯ�Ͽ� ������ �뵵�� ����ü
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