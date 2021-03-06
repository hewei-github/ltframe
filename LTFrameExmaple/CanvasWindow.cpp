#include "stdafx.h"

#include "CanvasWindow.h"


namespace CanvasWindowSpace{
CanvasWindow* CanvasWindowC=0;

DEFINEFUNCTION DragWindowFun(LTExecState* es)
{
	CanvasWindowC->DragWindow();
	return JsUndefined();
}

DEFINEFUNCTION CloseWindowFun(LTExecState* es)
{
	CanvasWindowC->CloseWindow();
	return JsUndefined();
}
DEFINEFUNCTION MinWindowFun(LTExecState* es)
{
	CanvasWindowC->MinWindow();
	return JsUndefined();
}

CanvasWindow::CanvasWindow()
{	
	HMODULE hModule = ::GetModuleHandle(0);
	applicationpath  = (wchar_t*)malloc((MAX_PATH+1)*sizeof(wchar_t)); 
	GetModuleFileName(NULL, applicationpath, MAX_PATH);
	(wcsrchr(applicationpath, '\\'))[1] = 0;
	int ww = 700,wh=500;
	OleInitialize(0);
	ltskinview= CreateLTFrameInstance(this,L"LTFrame",NULL,WS_POPUP | WS_VISIBLE,0,0,ww,wh,0);
	CanvasWindowC =this;
	ltskinview->BindUserFunction("DragWindow",DragWindowFun,0);
	ltskinview->BindUserFunction("CloseWindow",CloseWindowFun,0);
	ltskinview->BindUserFunction("MinWindow",MinWindowFun,0);
	SetWindowText(ltskinview->windowHandle(),L"LTFrame");
	wstring path = wstring(applicationpath)+L"./template/Canvas.html";
	ltskinview->loadFile(path.c_str());
	ltskinview->EnableDragFrameChangeSize(false);
	SetForegroundWindow(ltskinview->windowHandle());
	ltskinview->MessageLoop();
}


CanvasWindow::~CanvasWindow(void)
{
	free(applicationpath);
}
void CanvasWindow::DragWindow()
{
	ReleaseCapture();
	POINT DownPoint;
	GetCursorPos(&DownPoint);
	SendMessage(ltskinview->windowHandle(),WM_NCLBUTTONDOWN,HTCAPTION,MAKEWPARAM(DownPoint.x,DownPoint.y));
}
void CanvasWindow::CloseWindow()
{
	DestroyWindow(ltskinview->windowHandle());
}
void CanvasWindow::MinWindow()
{
	::ShowWindow(ltskinview->windowHandle(),SW_MINIMIZE);	
}
LRESULT CanvasWindow::HandleMessage(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{

	}
	return ltskinview->HandleMessage(hwnd,uMsg,wParam,lParam);
}


LPCWSTR CanvasWindow::GetWindowClassName()
{
	return L"INDEX";
}
}