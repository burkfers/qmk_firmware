# handwired/arcboard_mk17_tft

A test keyboard for validating my quantum painter woes.

- 7789 TFT
- RP2040
- QP enabled

# Problem description
The code is attempting to draw a blue box on the screen.

Scan rate is atrociously bad (25) when executing `qp_rect` inside `housekeeping_task_kb`.
Uncommenting `qp_rect` immediately resolves the scan rate issues.

The issue presents when the SPI bus is shared with a PMW33xx device as well as when it is not.

# Hardware setup
Only the pins necessary for making the TFT work are used. 5v is supplied from VSYS to a power rail.  Ground rail from GND.
RST on GP0. 
