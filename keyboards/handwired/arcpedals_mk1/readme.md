# handwired/arcpedals_mk1
*QMK-powered foot pedals - offload strain from your hands to your feet!*

![handwired/arcpedals_mk1](https://i.imgur.com/uLY4qxZl.jpg)

* Keyboard Maintainer: [christrotter](https://github.com/christrotter)

## Features
* Layer changing with the ball of your foot; toes for functionality
* Split keyboard w. TRRS
* RGB all day long
* JST connector for remote indicator bar
* Modular assembly w. dovetail/M3 connectors
* Prototype jank

## Parts and files
* STLs and Fusion 360 files here: https://github.com/christrotter/3d-models/tree/main/keyboards/arcpedals-mk1
* Hardware Supported: RP2040 w. mxledbit 'container' PCBs, ST7789 TFTs, 3D-printed chassis
* Hardware Availability: 
  * Waveshare RP2040-Plus: https://www.aliexpress.com/item/1005003504708746.html
  * per-key PCB: https://github.com/swanmatch/MxLEDBitPCB/tree/master/container (via JLCPCB)
  * wiring PCB: https://www.amazon.ca/Solderable-Breadboard-Electronics-Gold-Plated-Multicolor/dp/B081MSKJJX
  * TRRS PCB: https://www.aliexpress.com/item/32968034072.html
  * Hotswap sockets: https://www.aliexpress.com/item/4001051840976.html
  * Capacitors: https://www.aliexpress.com/item/32877282377.html
  * LEDs: https://www.aliexpress.com/item/4000475685852.html
  * JST connectors: https://www.aliexpress.com/item/32954418743.html (but I highly recommend buying a JST crimper, connectors, and using 26awg silicone wiring)

## Details
* JST connectors make wiring and troubleshooting much easier.  Much, much, much easier.  USE A FLUX PEN WHEN SOLDERING WOW.
* I used some old Grifiti wrist pad (palm rest) (about 3/4"/~20mm neoprene pad) for the heel pads.
* The wiring covers are separate parts for reasons I can't now remember.
* I used prototypes of the MCU holder as wire retainers; the latest design includes the capacity for making a wire retainer part.
* Can't recommend JST XH 2.54 connectors enough, have really made a difference in packaging/assembly/troubleshooting my prototypes!

![handwired/arcpedals_mk1](https://i.imgur.com/uLY4qxZ.jpg)
![handwired/arcpedals_mk1](https://i.imgur.com/QyyWODa.jpg)
![handwired/arcpedals_mk1](https://i.imgur.com/PbXtXyX.jpg)
![handwired/arcpedals_mk1](https://i.imgur.com/9EiABB0.jpg)

More pictures here: https://crazymittens.imgur.com/all


## Bootloader and flashing
Make example for this keyboard (after setting up your build environment):

    ./build.sh build

Flashing example for this keyboard:

    ./build.sh left
    ./build.sh right

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
