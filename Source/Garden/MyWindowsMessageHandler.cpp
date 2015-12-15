
#include "Garden.h"
#include "MyWindowsMessageHandler.h"
#include "GenericApplication.h"
#include "AllowWindowsPlatformTypes.h"
#include <Winuser.h>
#include "HideWindowsPlatformTypes.h"

#define MAXPOINTS 32
static int32 idLookup[MAXPOINTS];


int32 GetContactIndex(int32 dwID){
	for (int32 i = 0; i < MAXPOINTS; i++){
		if (idLookup[i] == -1){
			idLookup[i] = dwID;
			return i;
		}
		else{
			if (idLookup[i] == dwID){
				return i;
			}
		}
	}
	// Out of contacts
	return -1;
}

void ReleaseContactIndex(int32 dwID){
	for (int32 i = 0; i < MAXPOINTS; i++){
		if (idLookup[i] == dwID){
			idLookup[i] = -1;
		}
	}
}

void  FMyWindowsMessageHandler::InitVariable(){
	for (int32 i = 0; i < MAXPOINTS; i++){
		idLookup[i] = -1;
	}
	isTouchInit = false;
}
bool  FMyWindowsMessageHandler::ProcessMessage(HWND hwnd, uint32 msg, WPARAM wParam, LPARAM lParam, int32& OutResult){
	if (msg == WM_TOUCH){
		unsigned int numInputs = LOWORD(wParam); // Number of actual per-contact messages
		TOUCHINPUT* ti = new TOUCHINPUT[numInputs]; // Allocate the storage for the parameters of the per-contact messages
		if (ti == NULL){
			return false;
		}
		
		if (GetTouchInputInfo((HTOUCHINPUT)lParam, numInputs, ti, sizeof(TOUCHINPUT)))
		{
			// For each contact, dispatch the message to the appropriate message
			// handler.
			for (unsigned int i = 0; i<numInputs; ++i)
			{
				int32 index = GetContactIndex(ti[i].dwID);
				if (ti[i].dwID != 0 && index < MAXPOINTS){				
					if((ti[i].dwFlags & TOUCHEVENTF_UP))
					{
					ReleaseContactIndex(ti[i].dwID);
					TouchController->OnTouchUpHandler(TOUCH_COORD_TO_PIXEL(ti[i].x), TOUCH_COORD_TO_PIXEL(ti[i].y), index);
					}
					else if ((ti[i].dwFlags & TOUCHEVENTF_MOVE))
					{
						//case photo detecter is TOUCHEVENTF_MOVE  and TOUCHEVENTF_UP combine so Release is this position,so case no photo detector is this position's ReleaseContactIndex comment out
						ReleaseContactIndex(ti[i].dwID);
						TouchController->OnTouchMoveHandler(TOUCH_COORD_TO_PIXEL(ti[i].x), TOUCH_COORD_TO_PIXEL(ti[i].y), index);						
					}
					else if ((ti[i].dwFlags & TOUCHEVENTF_DOWN))
					{
						//case photo detecter is TOUCHEVENTF_MOVE  and TOUCHEVENTF_UP combine so Release is this position,so case no photo detector is this position's ReleaseContactIndex comment out  
						ReleaseContactIndex(ti[i].dwID);
						TouchController->OnTouchDownHandler(TOUCH_COORD_TO_PIXEL(ti[i].x), TOUCH_COORD_TO_PIXEL(ti[i].y), index);
					}
					
				}
			}
		}
		CloseTouchInputHandle((HTOUCHINPUT)lParam);
		delete[] ti;
		return false;
	}
	else if(!isTouchInit){
		RegisterTouchWindow(hwnd, 0);
		isTouchInit = true;
	}
	LRESULT rez = DefWindowProc(hwnd, msg, wParam, lParam);
	return (rez != 0 ? true: false);
}

