/* solid-taskbar - remove transparency from the Windows 8 taskbar

   Written in 2014 by James Ross-Gowan <rossymiles@gmail.com>

   To the extent possible under law, the author(s) have dedicated all copyright
   and related and neighboring rights to this software to the public domain
   worldwide. This software is distributed without any warranty.

   You should have received a copy of the CC0 Public Domain Dedication along
   with this software. If not, see
   <http://creativecommons.org/publicdomain/zero/1.0/>. */

#include <windows.h>
#include <dwmapi.h>

extern IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)

static UINT wm_taskbarcreated;

static void blurbehind_taskbar(void)
{
	HWND taskbar = FindWindowW(L"Shell_TrayWnd", NULL);
	if (!taskbar)
		return;

	/* In Windows 8, enabling blur-behind actually makes the window opaque */
	DwmEnableBlurBehindWindow(taskbar, &(const DWM_BLURBEHIND) {
		.dwFlags = DWM_BB_ENABLE,
		.fEnable = TRUE,
	});
}

static LRESULT CALLBACK window_proc(HWND wnd, UINT msg, WPARAM wp, LPARAM lp)
{
	/* If the taskbar is recreated, blur-behind needs to be enabled again. This
	   is why the program sticks around in the first place, instead of just
	   closing after removing transparency the first time. */
	if (msg == wm_taskbarcreated)
		blurbehind_taskbar();

	switch (msg) {
		case WM_CLOSE:
			DestroyWindow(wnd);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return DefWindowProcW(wnd, msg, wp, lp);
}

#ifdef NO_CRT
/* A __stdcall entry point is needed for building without the CRT */
int __stdcall entry(void)
#else
int wmain(int argc, wchar_t **argv)
#endif
{
	wm_taskbarcreated = RegisterWindowMessageW(L"TaskbarCreated");
	ATOM class = RegisterClassExW(&(const WNDCLASSEXW) {
		.cbSize = sizeof(WNDCLASSEXW),
		.lpfnWndProc = window_proc,
		.hInstance = HINST_THISCOMPONENT,
		.lpszClassName = L"solid-taskbar",
	});

	/* Create a top-level window to receive the TaskbarCreated message */
	if (!CreateWindowExW(0, (LPWSTR)MAKEINTATOM(class), L"", WS_POPUP, 0, 0, 0,
			0, NULL, NULL, HINST_THISCOMPONENT, NULL))
		return 1;

	/* Remove transparency from the taskbar, if it exists */
	blurbehind_taskbar();

	/* Watch for TaskbarCreated, in case the taskbar is recreated */
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
		DispatchMessageW(&msg);
	return msg.wParam;
}
