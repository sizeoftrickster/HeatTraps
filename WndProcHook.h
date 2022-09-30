#ifndef _WND_PROC_HOOK_H_
#define _WND_PROC_HOOK_H_

#include <Windows.h>
#include <kthook/kthook.hpp>
#include "HeatTraps.h"

using WndProcPrototype = LRESULT( __stdcall* )( HWND, UINT, WPARAM, LPARAM );

class WndProcHook
{
	kthook::kthook_simple<WndProcPrototype> wndprocHook{ 0x747EB0 };

	HeatTraps* heatTraps;
public:
	WndProcHook();
	~WndProcHook();
private:
	LRESULT WndProcHooked( const decltype( wndprocHook )& hook, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
};

#endif // !_WND_PROC_HOOK_H_