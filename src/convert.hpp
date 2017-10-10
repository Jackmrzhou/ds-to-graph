#pragma once
#ifndef CONVERT_H_
#define CONVERT_H_
#include <memory>
#include <d2d1.h>
std::unique_ptr<WCHAR> to_WCHAR(size_t num);

#endif // !CONVERT_H_
