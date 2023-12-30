# handwired/arcboard_mk19

![handwired/arcboard_mk19](imgur.com image replace me!)

*KeyDesk? DeskBoard? UltraDorito?*

Introducing ArcBoard mk19, the latest in a line of medical needs-focused input devices that allow you to operate a computer with flat, at-rest hands.
Specific focus has been applied to maintaining the tension of minimizing combos and button holds while not losing out on the benefits of layers and QMK's vast scope of programmability.

- Never move your fingers from homerow yet still mouse using the 34mm thumb trackball and auto-mouse layer.
- Moving functionality from pinkies to thumbs reduces strain.
- 5-way switches on both sides are easily accessed by your thumbs - e.g. dedicated arrow keys or modifier keys.
- Four encoders - two on each half - with generous 70mm backlit knobs allow you to offload repetitive actions.
- Large 1.5u thumb keycaps make for comfortable thumb actioning, with six thumb keys available.
- RGB leds on each mapped button for rapid learning of remapped functionality, reducing much of the friction around customizing your keymap.
- The flat encoder panel can be swapped out for another type of device, like a USB SpaceMouse Compact.
- The integrated 8-key macropad allows one-key functions for things like microphone muting - or whatever you care to program in. 
- Grifiti FatMat (18mm thick neoprene) palm rests reach all the way out to the macropad, making every action comfy.
- Custom pcb designed to integrate with the Cyboard flex-pcb system
- USB-C connectivity for all external wiring including serial interconnect

- A bank of dedicated indicator LEDs allow shift and other hold function states to be made visible. >>>>>  and are extendable to external indicators.
- RP2040 MCU socketed onto a custom pcb - internal JST and FFC connections >>>>> (why both? economy)
- >>>>> matrix, logical, is 51 keys/side = keywell(5x6) + thumbs(6) + 5-way(5) + falcons (2 push-buttons) + macropad (8)
- >>>>> matrix, electrical, is 6 rows, 10 cols; via shift-registers (why cols, why not rows? - something about how shift registers work...)
- Right-half has a PMW33xx, >>>>> left-half has...something else...


# What if's
## ultrafalcon encoders
PER60 encoder wheels with embedded GC9A01 LCDs on pushbuttons.

custom pcb w. center passthrough
- JST-XH 2.54 (DI,DO,+,-,ROW,COL)
- capacitor for led
- diode for row
- PER60 footprint
- led surround
- pushbutton
- GC9A01 LCD mount w. passthrough FFC cable 8-pin 0.5mm?

## integrated pedals
Pedals really seem to only use a couple of functions per foot - and layers really only used for 'main app' and 'browsing'.
Pedals mk3 would move from 4 to 2 buttons per foot.
Layer stackup would enable pedal layers to work.
- button to toggle which pedal bool you wanted on

>>>>> Something like this?
Layer4 - tog/hold - keys-symbols; pedals-trans
Layer3 - tog/hold - keys-numpad; pedals-trans
Layer2 - hold     - keys-automouse; pedals-trans
Layer1 - hold     - keys-trans; pedals-L1
Layer0 - default  - keys-L0; pedals-L0

