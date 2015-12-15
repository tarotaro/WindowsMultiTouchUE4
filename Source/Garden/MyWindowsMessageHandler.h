#pragma once
#include "GenericApplicationMessageHandler.h"
#include "WindowsApplication.h"
#include "WindowsWindow.h"
#include "AllowWindowsPlatformTypes.h"
#include "Ole2.h"
#include "OleIdl.h"
#include "ShObjIdl.h"
#include <Winuser.h>
#include "HideWindowsPlatformTypes.h"
#include "WindowsApplication.h"
#include "MultiTouchPlayerController.h"

class  GARDEN_API FMyWindowsMessageHandler :
	public IWindowsMessageHandler
{

public:
	void InitVariable();
	virtual bool ProcessMessage(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam, int32& OutResult) override;
	AMultiTouchPlayerController *TouchController;
	bool isTouchInit;
};

