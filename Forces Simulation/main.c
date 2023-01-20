#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define BT_PLAY_SOUND 0xBEEF

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void InitComponents(HWND);
void thrust();
void ImposeWindowLayout(LPARAM);


//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
typedef struct _FORCE_OBJECT {
    float init_x;
    float init_y;

    float x;
    float y;
    float width;
    float height;
    
    float angle;
    float accel;
    float force;
    
} FORCE_OBJECT;

static FORCE_OBJECT objs[2];

//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
static HINSTANCE hInst;
static WNDCLASSW WNDC;

static HWND root;
// static HWND lbl_prompt;
// static HWND bt_playsound;

static volatile boolean mouse_down = false;
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE _hInst, HINSTANCE hprev, LPSTR args, int ncmdshow){
    
    hInst = _hInst;

    WNDCLASSW WNDC = {0};

    WNDC.lpszClassName = L"wndclass";
    WNDC.hInstance     = _hInst;
    WNDC.hbrBackground = (HBRUSH)COLOR_WINDOW;
    WNDC.lpfnWndProc   = WndProc;
    WNDC.hCursor       = LoadCursor(0, IDC_ARROW);
    
    if(!RegisterClassW(&WNDC)){
        //register unsuccessful
        return -1;
    }
    
    root = CreateWindowW(WNDC.lpszClassName, L"Wave Synthesizer", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 500, 0, 0, _hInst, 0);

    MSG msg = {};

    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp){

    if(mouse_down){
        thrust();
    }

    switch (msg) {
        case WM_LBUTTONDOWN:
            mouse_down = true;
            break;

        case WM_GETMINMAXINFO:
            break;

        case WM_LBUTTONUP:
            mouse_down = false;
            break;

        case WM_SIZE:
            ImposeWindowLayout(lp);
            break;

        case WM_CREATE:
            InitComponents(hwnd);
            ImposeWindowLayout(lp);
            break;

        case WM_COMMAND:
            if(LOWORD(wp) == BT_PLAY_SOUND){
                MessageBeep(MB_YESNO);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        
        default:
            DefWindowProcW(hwnd, msg, wp, lp);
            break;
    }
}

void thrust(){
    POINT cur;
    GetCursorPos(&cur);
    
    printf("%i\n", cur.x);
    printf("%i\n", cur.y);
}

void ImposeWindowLayout(LPARAM lp){

    int width = LOWORD(lp);
    int height = HIWORD(lp);
    
    // SetWindowTextW(lbl_prompt, L"<- Make a Noise");

    // SetWindowPos(lbl_prompt, NULL, (int)(width*0.52), (int)(height*0.02), (int)(width*0.45), (int)20, SWP_SHOWWINDOW);
    // SetWindowPos(bt_playsound, NULL, (int)(width*0.02), (int)(height*0.02), (int)(width*0.45), (int)20, SWP_SHOWWINDOW);
}

void InitComponents(HWND hwnd){
    // lbl_prompt = CreateWindowW(L"static", L"<- Make a Noise", WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTER , 0, 0, 0, 0, hwnd, NULL, NULL, NULL);
    // bt_playsound = CreateWindowW(L"Button", L"playsound", WS_CHILD | WS_VISIBLE, 10, 10, 100, 20, hwnd, (HMENU)BT_PLAY_SOUND, NULL, NULL);
} 