#include <string>
#include <cwchar>
#include <memory>
using namespace std;
using WCHAR = wchar_t;
unique_ptr<WCHAR> to_WCHAR(size_t num)
{
	size_t count = 0;
	size_t tmp = num;
	while (num != 0)
	{
		count++;
		num /= 10;
	}
	if (tmp == 0)
		count = 1;
	unique_ptr<WCHAR> pWCHAR(new WCHAR[count + 1]);
	swprintf(pWCHAR.get(), count + 1, L"%u", tmp);
	return pWCHAR;
}