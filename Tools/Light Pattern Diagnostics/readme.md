# Detecting Light Patterns for Emergency Lights

Modern emergency lights these days are LED based so there are no "physical" light patterns any more. Insteads, each vendor can create their own light patterns (blinking patterns), and most of the time these patterns aren't well documented.

Knowing these patterns can be helpful for many scenarios:

* maybe you are a model maker and would like to create realistic emergency lights for your model world
* or you'd like to create your own emergency lights from old hardware or modern vanilla LED components and would like them to match their professional counter parts
* yet again others just love the challenge

We are going to create a light pattern detector that can dump the timings of any LED-driven emergency light. Here is a sample output for a *Hänsch Movia D* magnetic LED emergency light (8-part-pattern):

```
<8>: [153][-45][16][-25][16][-25][15][-187]
<8>: [154][-45][16][-25][15][-25][16][-188]
<8>: [152][-46][16][-24][17][-24][17][-187]
<8>: [153][-45][16][-25][16][-25][15][-187]
<8>: [154][-45][16][-25][15][-25][16][-188]
```

And this is the light pattern for a *Pintsch Bamag 4x3 LED Unit*** for a *Topas* emergency light bar (4-part-pattern):

```
<4>: [129][-25][36][-305]
<4>: [129][-24][37][-305]
<4>: [128][-26][36][-305]
<4>: [128][-25][37][-304]
<4>: [129][-25][37][-304]
<4>: [129][-25][36][-306]
```

All numbers are in milliseconds. Negative numbers are OFF-phases (dark), and positive values are ON-phases (light).

A *Hänsch Movia D* LED flashlight therefore uses this pattern:

ON:  153ms
OFF:  45ms
ON:   16ms
OFF:  25ms
ON:   16ms
OFF: 187ms

A *Pintsch 4x3 LED Unit* in contrast uses this pattern:

ON:  130ms
OFF:  25ms
ON:   35ms
OFF: 305ms

## Concept for Light Pattern Detector

Emergency lights use high frequency patterns of which some parts may last as short as 10-15 milliseconds.

A cheap photo resistor is not suitable for the task due to its latencies. What's needed is a phototransistor or a photodiode. I randomly picked a [PCB board that was readily available](https://www.google.com/search?q=CJMCU+101) and uses a [OPT101 monolithic photodiode](https://www.ti.com/lit/ds/symlink/opt101.pdf). 

You could of course reuse an old solar-cell operated calculator as well by reusing its solar cell. Really what's needed is a component that changes voltage based on light intensity, and it needs to do this with a minimum of latency.

### Using the OPT101 CJMCU Breakout Board

In my tool I am going to use the [CJMCU board with OPT101 from Texas Instruments](https://www.google.com/search?q=CJMCU+101). More often than not, the board comes in parts and w/o instructions or data sheet, and you are expected to solder everything together. 

The challenging part is soldering the OPT101 chip onto the board correctly: place it on the side of the PCB that shows a square white dot (so that the soldering bridges on the PCB board are still visible and not covered by the OPT101 chip), and make sure you place the chip in such way that the (barely visible) "half-moon"-shaped recess is facing away from the PCB board pins.

### Connecting CJMCU Board with OPT101 to Arduino Nano (or similar)

Connecting the CJMCU board with its OPT101 on it to Arduino Nano (or any other microprocessor board) is simple:

* Connect *VCC* to Anode (i.e. 5V+)
* Connect *COM* and *-V* to GND
* Connect *OUT* and *1M* and use them as output. Depending on the brightness of light, the connected wires will produce 0-5V

![plot](./simple_wiring_opt101_to_arduino_nano.png)

You can connect the output (*OUT* and *1M*) to one of the analog input pins of your MC, or you can as well connect it to a multimeter (connect the other end of it to GND) to see how the OPT101 works.
