#pragma once

// C RunTime Header Files:
#define UNICODE
//efine GET_ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <wchar.h>
#include <math.h>
#include <Windows.h>
#include "Scripts\PlayerResult.h"
void HR(HRESULT const value);

// 循环延迟毫秒
#define DELAY_TIME 15

// 托盘菜单：退出
#define NTI_QUIT 0
// 托盘菜单：作者博客
#define NTI_ABM 1