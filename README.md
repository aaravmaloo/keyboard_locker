<h1 align="center">keyboard_locker: A tiny keyboard locker written in C++</h1>

This is my personal project that took ~42 mins to write. Essentially it is just a keyboard locker. Nothing really complex. 
I chose C++ for this project, because, it has easy windows API to interact and efficient binary sizes.
I've included the architecture I used to develop this below.

```mermaid
flowchart TD
    A["Windows Login"] --> B["klock.exe starts via Run registry key"]
    B --> C["RegisterStartup()"]
    C --> D["SetWindowsHookExA WH_KEYBOARD_LL"]
    D --> E["Message Loop (blocking)"]
    E --> F["Keypress anywhere on system"]
    F --> G["LowLevelKeyboardProc fires"]
    G --> H{"locked?"}
    H -->|"no"| I{"Ctrl+Shift+X?"}
    I -->|"yes"| J["locked = true, eat key"]
    I -->|"no"| K["CallNextHookEx, pass through"]
    H -->|"yes"| L{"Ctrl+Shift+X?"}
    L -->|"yes"| M["locked = false, pass through"]
    L -->|"no"| N["return 1, key eaten"]
    J --> E
    K --> E
    M --> E
    N --> E
```
