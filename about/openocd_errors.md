# OpenOCD errors
## `Error: Error connecting DP: cannot read IDR`
### CONDITIONS 
The following conditions can be observed by using a DAPlink programmer.

1) Enable debug mode level `>0` for openOCD, this can be done either via:
- `openocd -d3 ...other_parameters...`
- If using the extension cortex-debug in VSCode, by adding:  
	```
	in file openocd.cfg
	-------
	debug_level 3
	```
2) If the output of openocd contains:
    ```
    Debug: 229 931 cmsis_dap.c:646 cmsis_dap_swd_read_process(): SWD ack not OK @ 0 JUNK
    Error: 230 932 adi_v5_swd.c:144 swd_connect(): Error connecting DP: cannot read IDR
    Debug: 231 932 command.c:628 run_command(): Command 'dap init' failed with error code -4
    User : 232 932 command.c:694 command_run_line():
    ```
     Then the problem is likely to be hardware, i.e. the programmer (DAPlink) is unable to connect/talk to the target via SWD. See [this]( https://sourceforge.net/p/openocd/mailman/openocd-devel/thread/20200706142907.GF2662%40home.paul.comp/) mailling list thread.
### SOLUTION
    1) Check `VDD` voltages:
        - [ ] Do they reach the micro?
        - [ ] Are they the correct value?
        - [ ] Are there short-circuits to `GND`?
    2) Check continuity on `SWDIO` and `SWCLK` lines
        - [ ] Are the mircos' pins soldered to the board?
        - [ ] Is the micro correctly oriented on the pcb?
    3) Check the DAP connection
        - [ ] Do the jumper-wires work?


