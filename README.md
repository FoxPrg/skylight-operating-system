# skylight-operating-system
Protected mode os, written in C++
## Progress:
-   [X] Bootloader
    -   [X] Main loader
-	[X] Terminal
    -   [X] Functions to print char, string
    -   [X] Escape sequences support (`\r\n\t\v\b`)
    -   [X] Formatted & colored print (`%eb` - start colored text, `%ee` - stop)
    -   [X] Numbers support (`\b\o\d\x\X`)
-   [X] Input & output through ports
-   [X] Global Descriptor Table Manager
-   [X] Programmable Interrupt Controller
-   [X] Interrupts
    -   [X] Interrupt Descriptor Table Manager
    -   [X] Exceptions Manager
    -   [X] Hardware Interrupts Manager
-   [X] Programmable Interval Timer
-   [ ] Advanced Configuration & Power Interface Manager
    -   [X] Power Off
    -   [ ] Reboot