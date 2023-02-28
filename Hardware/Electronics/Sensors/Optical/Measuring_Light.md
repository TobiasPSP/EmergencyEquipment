# Measuring Light Intensity

Light intensity can be measured and expressed in a variety of ways. Let's shed some light on units used to measure light.

## Units to Express Light Intensity

There are different units to represent light intensity, such as *W/m2*, *Lux* and *Lumen*. They all measure light intensity, but they do so from different perspectives. So it is important to look at the appropriate unit when trying to get an answer:

* **Energy**: If you want to set up solar panels, you are interested in the pure physical energy that sunline can deliver. Thus *W/m2* is your choice.
* **Brightness at Receiver**: If you want to buy a new lamp to illuminate your living room you are interested in how bright the room will be. Thus "Lux" is your choice.
* **Brightness at Emitter**: If you'd like to compare the brightness of different LEDs, "Lumen" is the unit of choice.

Let's take a closer look at what the different units really express:

* **W/m2 (*"Irradiance"*, Energy per Surface*)**: The unit *W/m2* is often used to represent the physical energy emitted by a light source. So W/m2 is the *rate of energy* that falls on a defined *surface*. It is mostly used in the solar industry because it expresses for example the energy of sunshine that can be captured by a solar panel. It is not so much a good indicator for *"brightness*" because it does not take into consideration wavelengths (colors) of light. Since the human eye picks up different light wavelengths in a different way (and is most sensitive to green light for example), the "felt" brightness can be much different from the actual light energy. For example, UV light may be of high energetic intensitiy (take a tan lamp) yet the human eye would "feel" this light is not very bright or even completely dark (which is in essence why you should wear eye protection when tanning because even though the UV lamp does not blind you, its energy will inded physically blind you over time).
* **lx (Lux, *Luminous Flux"*)**: The unit *Lux* is often used to represent the *"brightness*" of a lamp, or more precise: its ability to lighten up a room. So *Lux* represents the *luminous lux* of 1 *lumen* per square meter, so it is a unit to measure the level of illuminance (how brightly something gets illuminated by light). In comparison, *W/m2* expresses the energy delivered by light to a surface, regardless of light spectrum and thus regardless of the special human eye sensitivities. In short, *Lux* is *W/m2* with an adaption factor that takes into account the special nature and sensitivity of the human eye.
* **Photometric Radiation Equivalent**: this is the magic conversion factor that converts *W/m2* to *Lux*. Since it incorporates the specific sensitivity of the human eye to different wave lengths, this factor is not a constant but instead depends on the light wavelength. The *Photometric Radiation Equivalent* for light with a wavelength of *555nm* (roughly the midpoint of human eye sensitivity) for example is *683lm/W*.
* **Lumen**: The unit "Lumen" measures the *luminous flux* emitted by a lamp in all directions. In older days, the "brightness* of conventional light bulbs was conveniently expressed as *Watt*. Since conventional light bulbs all work by heating a filament, they all shared the same efficiency (or lack thereof) so the brightness could roughly be guessed by looking at the energy intake. Today with many different light technologies (that all have different efficiencies), the energy intake no longer uniformly correlates to the light output. For example, a 5W light bulb produces considerably less light than a 5W LED. That's why *Lumen* today expresses the "*brightness*" of light emitting devices. 

### Difference Between *Lux* and *Lumen*

You now know that *W/m2* ignores the specific sensitivity of the human eye and thus is not suitable for measuring "brightness". Only *Lux* and *Lumen* take into account the light wavelength and the "feeling for brightness" for the human eye.

However, what exactly *is* the difference between *Lux* and *Lumen* then?

* **Lux** (*receiving* light): This unit looks at the receiver of the light so it measures how bright a given surface will be when the light is shed on it. Use it to calculate the requirements for lamps for a given lighting scenario, i.e. a stage or a room in your house.
* **Lumen** (*sending* light): This unit looks at the sender of the light and measures the raw light output, independent of emitting angle, emitter surface, receiver surface, or distance to other objects. Use it to describe the raw *strength* of light sources.

### Converting Lux to Lumen

To better understand the relationship between *Lux* and *Lumen*, let's take a look at how to convert from *Lux* to *Lumen*:

**1 Lux** (lx) represents the *luminous flux* of **1 Lumen** per square meter. So the same light source with the same lux will produce different lumens, depending on the distance to the illuminated object, its emitting angle and the presence of reflectors or other beam forming devices.

Which makes total sense: a torch can be blazingly bright when tightly focused (on a small area) and shined directly into your eye, or it can be rather dim when shining on a wide angle from a great distance (on a much larger area).

## Measuring Light Intensity Electronically

If you'd like to *measure* "brightness", you need a device that can translate light energy to a reading. As you have seen previously, there are a few technical challenges to make sure the device actually measures what you are interested in.

### Photoelectric Component Types

To measure light energy with an electronic device, you need a component that changes its characteristics in the presence of light, such as a *photodiode*, a *phptptransistor*, or a *photoresistor*. With each, the principle is the same: in the presence of light, more electric energy can pass, and this can be measured. 

### Sensitivity to Wavelength

The device needs to be sensitive to the light wavelength that matters to you. If you want to calculate *W/m2*, the sensitivity should include all light wavelengths that you expect to receive. If you want to calculate *Lumen*, the sensitivity should include visible light only. We'll elaborate on this more in a bit.

### Sensitivity to Energy

The device needs to be sensitive to light energy in the range that you want to measure. If you want to measure light outside in bright sunshine, the energy levels are grossly different from i.e. light measurements in a cave. If the device maxes out long before you actually go outside, or if the device does not differentiate dim light levels in the twilight, it may be of limited use to you.

Most photoelectric components cannot measure the entire range from complete darkness to extreme sunshine. They can be embedded in simple electronic circuits, though, that shift their sensitivity into the range needed.

### Wavelengths

If you want to measure *W/m2* (Energy), the component needs to be sensitive to the complete light spectrum that includes all light that you expect to receive, i.e. include UV and Infrared.

If you want to measure *Lumen*, the component needs to be sensitive to the light frequency that matters to you: if you just want to measure the *Lumen* of blue LED to compare different vendors or create a quality control station, all you need is a light component sensitive to around 450nm. If however you'd like to measure *Lumen* of white light, i.e. to examine torches or room lights, the device must be sensitive to the range of visible light.

In addition, unwanted wavelengths must be isolated, either by excluding them (inside a room, there are hardly any UV or Infrared light emissions that would falsify your measurements) or by choosing a photoelectric device that is insensitive (blind) towards these frequencies.


### Dealing with Different Wavelengths

Unless you are measuring monochromatic light only (i.e. a LED emitting light with just one frequency), the photoelectric component must ideally be equally sensitive to all frequencies. This of course is impractical. In reality, photoelectric component sensitivity varies greatly with light frequency.

That's why most reasonably-priced "lux meters" roughly estimate the brightness by averaging the readings around the center frequency of visible light. A more precise method would be to use light filters and measure smaller light frequency ranges (multiple measurements or multiple sensors).

### Sensor Latency

If you just want to measure *static* scenarios where the light isn't changing very much, any photoelectric component will do if it meets above criteria.

If however you want to measure light with high time resolution, i.e. to measure the brightness of a thunderbolt or decode the light pattern of emergency lights, the photoelectric component must have a low *latency*: it must produce results fast (which typically exclude digital chips due to the required post-processing of analog readings), and it must be ready to take the next measurement fast (similar to the human eye, when you were blinded by a bright torch, your eye will require minutes to regain its ability to distinguish dim lights).

This is why typically photoresistors are great to measure static light (i.e. brightness in a room) but are not suitable for high-frequency measurement series.

## Luminous Efficiency Function

Electronic devices return an analog signal that corresponds with the received light energy (*W/m2*). To translate this energy to a human *brightness*, the light frequency must be taken into account. 

### Monochromatic Light

If you are measuring monochromatic light only, you can "translate* the received light energy with the correction factor for the light frequency that you measure. Here is a function that translates *W/m2* or *uW/cm2* (which are both the same) to *Lux* if the light frequency is known:

```c++
// lightEnergy = W/m2 or uW/cm2
// luminousEfficiency = empirical correction factor based on light frequency (wavelength)

float energyToLux(float lightEnergy, float luminousEfficiency) {
  float w_m2 = (lightEnergy / (float) 1000000) * (float) 100;
  float lux  = w_m2 * luminousEfficiency * (float) 683;
  return(lux);
}
```

#### Luminous Efficiency

In fact, the function does not take in the light frequency directly. Instead, it asks for a *luminousEfficiency* which is an empirical correction factor for a given light wavelength that corresponds with the sensitivity of the human eye for this frequency. Therefore, there is no "formula" for this. You need to look up the value for the *luminous Efficiency*:

| Wavelength  | +0 | +1 | +2 | +3 | +4 |
| ----------- | -- |-- |-- |-- |-- |
|380 nm|0.0002000|0.0002280|0.0002610|0.0002990|0.0003440|
|385 nm|0.0003960|0.0004550|0.0005250|0.0006040|0.0006960|
|390 nm|0.0008000|0.0009160|0.0010500|0.0012000|0.0013600|
|395 nm|0.0015500|0.0017500|0.0018800|0.0022300|0.0025000|
|400 nm|0.0028000|0.0031200|0.0034600|0.0038300|0.0042300|
|405 nm|0.0046600|0.0051200|0.0056200|0.0061700|0.0067600|
|410 nm|0.0074000|0.0081500|0.0089600|0.0098300|0.0108000|
|415 nm|0.0118000|0.0128000|0.0140000|0.0151000|0.0163000|
|420 nm|0.0175000|0.0186000|0.0196000|0.0207000|0.0217000|
|425 nm|0.0227000|0.0236000|0.0246000|0.0255000|0.0264000|
|430 nm|0.0273000|0.0283000|0.0294000|0.0304000|0.0315000|
|435 nm|0.0326000|0.0337000|0.0347000|0.0358000|0.0369000|
|440 nm|0.0379000|0.0388000|0.0398000|0.0406000|0.0415000|
|445 nm|0.0424000|0.0433000|0.0441000|0.0450000|0.0459000|
|450 nm|0.0468000|0.0477000|0.0487000|0.0498000|0.0509000|
|455 nm|0.0521000|0.0534000|0.0549000|0.0564000|0.0581000|
|460 nm|0.0600000|0.0626000|0.0653000|0.0680000|0.0709000|
|465 nm|0.0739000|0.0770000|0.0803000|0.0837000|0.0872000|
|470 nm|0.0910000|0.0949000|0.0990000|0.1040000|0.1080000|
|475 nm|0.1130000|0.1180000|0.1230000|0.1280000|0.1330000|
|480 nm|0.1390000|0.1450000|0.1500000|0.1560000|0.1630000|
|485 nm|0.1690000|0.1760000|0.1840000|0.1910000|0.1990000|
|490 nm|0.2080000|0.2170000|0.2270000|0.2370000|0.2470000|
|495 nm|0.2590000|0.2700000|0.2822900|0.2950500|0.3085700|
|500 nm|0.3230000|0.3384000|0.3546800|0.3716900|0.3892800|
|505 nm|0.4073000|0.4256200|0.4443000|0.4633900|0.4829300|
|510 nm|0.5030000|0.5235600|0.5445100|0.5656900|0.5869600|
|515 nm|0.6082000|0.6293400|0.6503000|0.6708700|0.6908400|
|520 nm|0.7100000|0.7281800|0.7454600|0.7619600|0.7778300|
|525 nm|0.7932000|0.8081100|0.8224900|0.8363000|0.8494900|
|530 nm|0.8620000|0.8738100|0.8849600|0.8954900|0.9054400|
|535 nm|0.9148500|0.9237300|0.9320900|0.9399200|0.9472200|
|540 nm|0.9540000|0.9602500|0.9660000|0.9712600|0.9760200|
|545 nm|0.9803000|0.9840900|0.9874800|0.9903100|0.9928100|
|550 nm|0.9949500|0.9967100|0.9980900|0.9991100|0.9997400|
|555 nm|1.0000000|0.9998500|0.9993000|0.9983200|0.9968900|
|560 nm|0.9950000|0.9926000|0.9897400|0.9864400|0.9827200|
|565 nm|0.9786000|0.9740800|0.9691700|0.9638500|0.9581300|
|570 nm|0.9520000|0.9454500|0.9384900|0.9311600|0.9234500|
|575 nm|0.9154000|0.9070000|0.8982700|0.8892000|0.8797800|
|580 nm|0.8700000|0.8598600|0.8493900|0.8386200|0.8275800|
|585 nm|0.8163000|0.8047900|0.7930800|0.7811900|0.7691500|
|590 nm|0.7570000|0.7447500|0.7324200|0.7200000|0.7074900|
|595 nm|0.6949000|0.6822100|0.6694700|0.6567400|0.6438400|
|600 nm|0.6310000|0.6181500|0.6053100|0.5924700|0.5796300|
|605 nm|0.5668000|0.5539600|0.5411300|0.5283500|0.5156300|
|610 nm|0.5030000|0.4904600|0.4780300|0.4656700|0.4534000|
|615 nm|0.4412000|0.4290800|0.4170300|0.4050300|0.3930300|
|620 nm|0.3810000|0.3689100|0.3568200|0.3447700|0.3328100|
|625 nm|0.3200000|0.3093300|0.2978500|0.2865900|0.2756200|
|630 nm|0.2650000|0.2547600|0.2448800|0.2353300|0.2260500|
|635 nm|0.2170000|0.2081600|0.1995400|0.1911500|0.1829700|
|640 nm|0.1750000|0.1672200|0.1596400|0.1522700|0.1451200|
|645 nm|0.1382000|0.1315000|0.1250200|0.1187700|0.1127600|
|650 nm|0.1070000|0.1014700|0.0962000|0.0911000|0.0863000|
|655 nm|0.0816000|0.0771000|0.0728000|0.0687000|0.0648000|
|660 nm|0.0610000|0.0574000|0.0540000|0.0507000|0.0475000|
|665 nm|0.0446000|0.0418000|0.0391000|0.0366000|0.0342000|
|670 nm|0.0320000|0.0300000|0.0281000|0.0263000|0.0247000|
|675 nm|0.0232000|0.0218000|0.0205000|0.0193000|0.0181000|
|680 nm|0.0170000|0.0159000|0.0148000|0.0138000|0.0128000|
|685 nm|0.0119000|0.0111000|0.0103000|0.0095300|0.0088500|
|690 nm|0.0082100|0.0076200|0.0070900|0.0065900|0.0061400|
|695 nm|0.0057200|0.0053400|0.0050000|0.0046800|0.0043800|
|700 nm|0.0041000|0.0038400|0.0035900|0.0033500|0.0031300|
|705 nm|0.0029300|0.0027400|0.0025600|0.0023900|0.0022400|
|710 nm|0.0020900|0.0019500|0.0018200|0.0017000|0.0015900|
|715 nm|0.0014800|0.0013800|0.0012900|0.0012000|0.0011200|
|720 nm|0.0010500|0.0009770|0.0009110|0.0008500|0.0007930|
|725 nm|0.0007400|0.0006900|0.0006430|0.0005990|0.0005580|
|730 nm|0.0005200|0.0004840|0.0004500|0.0004180|0.0003890|
|735 nm|0.0003610|0.0003350|0.0003110|0.0002890|0.0002680|
|740 nm|0.0002490|0.0002310|0.0002150|0.0001990|0.0001850|
|745 nm|0.0001720|0.0001510|0.0001490|0.0001380|0.0001290|
|750 nm|0.0001200|0.0001120|0.0001040|0.0000973|0.0000908|
|755 nm|0.0000848|0.0000791|0.0000739|0.0000689|0.0000643|
|760 nm|0.0000600|0.0000560|0.0000522|0.0000487|0.0000454|
|765 nm|0.0000424|0.0000396|0.0000369|0.0000345|0.0000321|
|770 nm|0.0000300|0.0000280|0.0000261|0.0000244|0.0000227|
|775 nm|0.0000212|0.0000198|0.0000185|0.0000172|0.0000161|
|780 nm|0.0000150|||||


you can multiply your analog signal with a static numeric value that describes how sensitive the human eye is to the light frequency you measure. 

Here is a simple example: the factor for green light is higher than the factor for red light because the human eye is more sensitive to the frequency spectrum of green light. A red and a green LED with the same *W/m2* energy emission appear differently bright to the human eye with the green LED *feeling* much brighter than the red. Thanks to the correction factor taking into account different frequencies, both LEDs with the same *W/m2* energy emission would have different *Lumen*.

### Mixed Light

In many circumstances, you want to measure a mixture of many different light frequencies. I.e. "white light" consists of all frequencies within the visible light.

Since it is completely impractical to filter out different light frequencies and apply individual correction factors per frequencies, two formulas are in wide use that apply the human eye sensitivity to frequency. Since the human eye has different receptors for bright and for dim light, there are two formulars:

* **Photopic Luminosity Function**: For *everyday light levels* that are picked up by the color-sensitive *Cones* in the human eye that require daylight levels of light to operate.
* **Scotopic Curve**: For dim light levels that are picked up by the black-and-white *Rods* that are highly sensitive to light but cannot differentiate colors (wavelengths).
