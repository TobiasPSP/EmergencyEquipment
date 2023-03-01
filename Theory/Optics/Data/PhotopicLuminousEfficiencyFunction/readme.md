# Photopic Luminous Efficiency Function

The [Photopic Luminous Efficiency Function](https://donklipstein.com/photopic.html) provides an adjustment factor per wavelength to account for the sensitivity of the human eye.

By applying the conversion factor to pure light energy (i.e. sensor readings), you essentially convert the unit from *energy* (*W/m2*) to *brightness* (Lumen). 

Applying the factor calculated by the *Photopic Luminous Efficiency Function* adapts the sensor reading to *human sensitivity*. To convert a sensor reading to *Lumen*, you'd also need to multiply the result by *Km*, a static constant.

## Not a Function but Empirical Data

The *Photopic Luminous Efficiency Function* really is no algorithm but rather a table with empirical data. 

This data was first gathered 1932 by examining how humans respond to light with different wavelengths and how they felt its brightness.

In 1988, the CIE adjusted the data slightly to account for the higher sensitivity of young people to blue light. Apparently, in the original study, there was an overweigh on older subjects.

## Data File

The data is provided as CSV file.
