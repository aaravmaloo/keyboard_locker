#include <windows.h>

static bool locked = false;
static HHOOK hook = NULL;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && locked) {
        KBDLLHOOKSTRUCT* kb = (KBDLLHOOKSTRUCT*)lParam;
        bool ctrl = GetAsyncKeyState(VK_CONTROL) & 0x8000;
        bool shift = GetAsyncKeyState(VK_SHIFT) & 0x8000;
        bool x = kb->vkCode == 'X';
        if (ctrl && shift && x && wParam == WM_KEYDOWN) {
            locked = false;
            return CallNextHookEx(hook, nCode, wParam, lParam);
        }
        return 1;
    }
    if (nCode == HC_ACTION && wParam == WM_KEYDOWN) {
        KBDLLHOOKSTRUCT* kb = (KBDLLHOOKSTRUCT*)lParam;
        bool ctrl = GetAsyncKeyState(VK_CONTROL) & 0x8000;
        bool shift = GetAsyncKeyState(VK_SHIFT) & 0x8000;
        bool x = kb->vkCode == 'X';
        if (ctrl && shift && x) {
            locked = true;
            return 1;
        }
    }
    return CallNextHookEx(hook, nCode, wParam, lParam);
}

void RegisterStartup() {
    HKEY hKey;
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_SET_VALUE, &hKey);
    RegSetValueExA(hKey, "klock", 0, REG_SZ, (BYTE*)path, strlen(path) + 1);
    RegCloseKey(hKey);
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    RegisterStartup();
    hook = SetWindowsHookExA(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hook);
    return 0;
}
