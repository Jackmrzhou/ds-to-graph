#pragma once
#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;}
#ifndef INIT_H
#define INIT_H

#include <Windows.h>
#include <d2d1.h>
#include <dwrite.h>

#endif // !INIT_H
