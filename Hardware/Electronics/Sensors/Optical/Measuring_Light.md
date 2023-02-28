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

If you are measuring monochromatic light only, you can multiply your analog signal with a static numeric value that describes how sensitive the human eye is to the light frequency you measure. 

Here is a simple example: the factor for green light is higher than the factor for red light because the human eye is more sensitive to the frequency spectrum of green light. A red and a green LED with the same *W/m2* energy emission appear differently bright to the human eye with the green LED *feeling* much brighter than the red. Thanks to the correction factor taking into account different frequencies, both LEDs with the same *W/m2* energy emission would have different *Lumen*.

### Mixed Light

In many circumstances, you want to measure a mixture of many different light frequencies. I.e. "white light" consists of all frequencies within the visible light.

Since it is completely impractical to filter out different light frequencies and apply individual correction factors per frequencies, two formulas are in wide use that apply the human eye sensitivity to frequency. Since the human eye has different receptors for bright and for dim light, there are two formulars:

* **Photopic Luminosity Function**: For *everyday light levels* that are picked up by the color-sensitive *Cones* in the human eye that require daylight levels of light to operate.
* **Scotopic Curve**: For dim light levels that are picked up by the black-and-white *Rods* that are highly sensitive to light but cannot differentiate colors (wavelengths).
