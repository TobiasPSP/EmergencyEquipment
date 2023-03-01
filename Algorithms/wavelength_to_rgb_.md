# Wavelength to RGB

Functions to convert a wavelength in nm (Nanometer) to R, G and B values.

## C++/Arduino/ESP32

The code below outputs CSV data for wavelengths in the visible range from 380nm to 780nm and their approximate RGB values.

The algorithm takes into account the special sensitivity of the human eye and corrects the value based on wavelength and subjective eye sensitivity.

The method used is a rough approximation and does not take into account the specific correction factor per wavelength.

```c++
void setup() {
  Serial.begin(115200);
  
  float gamma = 0.8;
  float max_intensity = 255;
  // put your main code here, to run repeatedly:
  for (int nm = 380; nm <= 780; nm++) 
  {
    //  derived from http://www.physics.sfasu.edu/astro/color/spectra.html
    
    float factor = 0;
    float R = 0;
    float G = 0;
    float B = 0;

    if (nm>=380.0 && nm< 440.0)
    {
      R = ((nm - 440.0)*-1.0) / 60.0;
      G = 0.0;
      B = 1.0;
    }
    else if (nm < 490.0)
    {
      R = 0.0;
      G = (nm - 440.0) / 50.0;
      B = 1.0;
    }
    else if (nm < 510.0)
    {
      R = 0.0;
      G = 1.0;
      B = ((nm - 510)*-1.0) / 20.0;
    }
    else if (nm < 580.0)
    {
      R = (nm - 510.0) / 70.0;
      G = 1.0;
      B = 0.0;
    }
    else if (nm < 645.0)
    {
      R = 1.0;
      G = ((nm - 645.0)*-1.0) / 65;
      B = 0.0;
    }
    else if (nm <= 780.0)
    {
      R = 1.0;
      G = 0.0;
      B = 0.0;
    }

    if (nm >= 380.0 && nm < 420.0)
    {
      factor = 0.3 + 0.7 * (nm - 380.0) / 40.0;
    }
    else if (nm <= 700.0)
    {
      factor = 1.0;
    }
    else if (nm <= 780.0)
    {
      factor = 0.3 + 0.7 * (780 - nm) / 80.0;
    }

    if (R > 0)
    {
      R = round(max_intensity * pow((R * factor),gamma));
    }
    
    if (G > 0)
    {
      G = round(max_intensity * pow((G * factor),gamma));
    }

    if (B > 0)
    {
      B = round(max_intensity * pow((B * factor),gamma));
    }

    Serial.print(nm);
    Serial.print(",");
    Serial.print((int)R);
    Serial.print(",");
    Serial.print((int)G);
    Serial.print(",");
    Serial.println((int)B);    
  }
}

void loop() {
  
}
```

## PowerShell

For easy testing, here is the same function written in *PowerShell* which is available on all Windows PCs and available via free download for other platforms including *Linux* and *MacOS*:

```powershell
function Convert-WavelengthToRgb
{
    # derived from http://www.physics.sfasu.edu/astro/color/spectra.html

    param
    (
        [Parameter(Mandatory,ValueFromPipeline,ValueFromPipelineByPropertyName)]
        [ValidateRange(380,780)]
        [int]
        $Wavelength
    )

    process
    {
        #from: https://www.codedrome.com/exploring-the-visible-spectrum-in-python/
		$gamma = 0.8
		$maxIntensity = 255
		$factor = 0

        $result = [PSCustomObject]@{
            Wavelength = $Wavelength
            R = 0
            G = 0
            B = 0
        }

        switch($Wavelength)
        {

            { $_ -lt 420 }  {   
                                $result.R = -($_ - 440) / 60
                                $result.B = 1
                                $factor = 0.3 + 0.7 * ($_ - 380) / 40
                                break
                            }

            { $_ -lt 440 }  { 
                                $result.R = -($_ - 440) / 60
                                $result.B = 1
                                $factor = 1
                                break
                            }

            { $_ -lt 490 }  { 
                                $result.G = ($_ - 440) / 50
                                $result.B = 1
                                $factor = 1
                                break
                            }

            { $_ -lt 510 }  { 
                                $result.B = -($_ - 510) / 20
                                $result.G = 1
                                $factor = 1
                                break
                            }

            { $_ -lt 580 }  { 
                                $result.R = ($_ - 510) / 70
                                $result.G = 1
                                $factor = 1
                                break
                            }

            { $_ -lt 645 }  { 
                                $result.G = -($_ - 645) / 65
                                $result.R = 1
                                $factor = 1
                                break
                            }
            { $_ -le 700    }  { 
                                $result.R = 1
                                $factor = 1
                                break
                            }


            { $_ -le 780 }  { 
                                $result.R = 1
                                $factor = 0.3 + 0.7 * (780 - $_) / 80
                                break
                            }
        }
    
        $result.R = [Math]::Pow( ($result.R * $factor), $gamma)	* $maxIntensity -as [int]
        $result.G = [Math]::Pow( ($result.G * $factor), $gamma)	* $maxIntensity -as [int]
        $result.B = [Math]::Pow( ($result.B * $factor), $gamma)	* $maxIntensity -as [int]

        return $result
    }
}

380..780 | Convert-WavelengthToRgb | Out-GridView -Title 'Wavelength to RGB'
```

## Data Table

Both functions create the same RGB values:


| Wavelength (nm) | R | G | B | Hex |
|:---------:|:---:|:---:|:---:|---|
|380|97|0|97|![#610061](https://via.placeholder.com/15/610061/610061.png) `#610061`|
|381|100|0|102|![#640066](https://via.placeholder.com/15/640066/640066.png) `#640066`|
|382|103|0|106|![#67006a](https://via.placeholder.com/15/67006a/67006a.png) `#67006a`|
|383|106|0|111|![#6a006f](https://via.placeholder.com/15/6a006f/6a006f.png) `#6a006f`|
|384|109|0|115|![#6d0073](https://via.placeholder.com/15/6d0073/6d0073.png) `#6d0073`|
|385|111|0|119|![#6f0077](https://via.placeholder.com/15/6f0077/6f0077.png) `#6f0077`|
|386|114|0|124|![#72007c](https://via.placeholder.com/15/72007c/72007c.png) `#72007c`|
|387|116|0|128|![#740080](https://via.placeholder.com/15/740080/740080.png) `#740080`|
|388|118|0|132|![#760084](https://via.placeholder.com/15/760084/760084.png) `#760084`|
|389|120|0|136|![#780088](https://via.placeholder.com/15/780088/780088.png) `#780088`|
|390|121|0|141|![#79008d](https://via.placeholder.com/15/79008d/79008d.png) `#79008d`|
|391|123|0|145|![#7b0091](https://via.placeholder.com/15/7b0091/7b0091.png) `#7b0091`|
|392|124|0|149|![#7c0095](https://via.placeholder.com/15/7c0095/7c0095.png) `#7c0095`|
|393|126|0|153|![#7e0099](https://via.placeholder.com/15/7e0099/7e0099.png) `#7e0099`|
|394|127|0|157|![#7f009d](https://via.placeholder.com/15/7f009d/7f009d.png) `#7f009d`|
|395|128|0|161|![#8000a1](https://via.placeholder.com/15/8000a1/8000a1.png) `#8000a1`|
|396|129|0|165|![#8100a5](https://via.placeholder.com/15/8100a5/8100a5.png) `#8100a5`|
|397|129|0|169|![#8100a9](https://via.placeholder.com/15/8100a9/8100a9.png) `#8100a9`|
|398|130|0|173|![#8200ad](https://via.placeholder.com/15/8200ad/8200ad.png) `#8200ad`|
|399|130|0|177|![#8200b1](https://via.placeholder.com/15/8200b1/8200b1.png) `#8200b1`|
|400|131|0|181|![#8300b5](https://via.placeholder.com/15/8300b5/8300b5.png) `#8300b5`|
|401|131|0|185|![#8300b9](https://via.placeholder.com/15/8300b9/8300b9.png) `#8300b9`|
|402|131|0|188|![#8300bc](https://via.placeholder.com/15/8300bc/8300bc.png) `#8300bc`|
|403|131|0|192|![#8300c0](https://via.placeholder.com/15/8300c0/8300c0.png) `#8300c0`|
|404|130|0|196|![#8200c4](https://via.placeholder.com/15/8200c4/8200c4.png) `#8200c4`|
|405|130|0|200|![#8200c8](https://via.placeholder.com/15/8200c8/8200c8.png) `#8200c8`|
|406|129|0|204|![#8100cc](https://via.placeholder.com/15/8100cc/8100cc.png) `#8100cc`|
|407|129|0|207|![#8100cf](https://via.placeholder.com/15/8100cf/8100cf.png) `#8100cf`|
|408|128|0|211|![#8000d3](https://via.placeholder.com/15/8000d3/8000d3.png) `#8000d3`|
|409|127|0|215|![#7f00d7](https://via.placeholder.com/15/7f00d7/7f00d7.png) `#7f00d7`|
|410|126|0|219|![#7e00db](https://via.placeholder.com/15/7e00db/7e00db.png) `#7e00db`|
|411|124|0|222|![#7c00de](https://via.placeholder.com/15/7c00de/7c00de.png) `#7c00de`|
|412|123|0|226|![#7b00e2](https://via.placeholder.com/15/7b00e2/7b00e2.png) `#7b00e2`|
|413|121|0|230|![#7900e6](https://via.placeholder.com/15/7900e6/7900e6.png) `#7900e6`|
|414|120|0|233|![#7800e9](https://via.placeholder.com/15/7800e9/7800e9.png) `#7800e9`|
|415|118|0|237|![#7600ed](https://via.placeholder.com/15/7600ed/7600ed.png) `#7600ed`|
|416|116|0|241|![#7400f1](https://via.placeholder.com/15/7400f1/7400f1.png) `#7400f1`|
|417|113|0|244|![#7100f4](https://via.placeholder.com/15/7100f4/7100f4.png) `#7100f4`|
|418|111|0|248|![#6f00f8](https://via.placeholder.com/15/6f00f8/6f00f8.png) `#6f00f8`|
|419|109|0|251|![#6d00fb](https://via.placeholder.com/15/6d00fb/6d00fb.png) `#6d00fb`|
|420|106|0|255|![#6a00ff](https://via.placeholder.com/15/6a00ff/6a00ff.png) `#6a00ff`|
|421|102|0|255|![#6600ff](https://via.placeholder.com/15/6600ff/6600ff.png) `#6600ff`|
|422|97|0|255|![#6100ff](https://via.placeholder.com/15/6100ff/6100ff.png) `#6100ff`|
|423|93|0|255|![#5d00ff](https://via.placeholder.com/15/5d00ff/5d00ff.png) `#5d00ff`|
|424|89|0|255|![#5900ff](https://via.placeholder.com/15/5900ff/5900ff.png) `#5900ff`|
|425|84|0|255|![#5400ff](https://via.placeholder.com/15/5400ff/5400ff.png) `#5400ff`|
|426|80|0|255|![#5000ff](https://via.placeholder.com/15/5000ff/5000ff.png) `#5000ff`|
|427|75|0|255|![#4b00ff](https://via.placeholder.com/15/4b00ff/4b00ff.png) `#4b00ff`|
|428|70|0|255|![#4600ff](https://via.placeholder.com/15/4600ff/4600ff.png) `#4600ff`|
|429|66|0|255|![#4200ff](https://via.placeholder.com/15/4200ff/4200ff.png) `#4200ff`|
|430|61|0|255|![#3d00ff](https://via.placeholder.com/15/3d00ff/3d00ff.png) `#3d00ff`|
|431|56|0|255|![#3800ff](https://via.placeholder.com/15/3800ff/3800ff.png) `#3800ff`|
|432|51|0|255|![#3300ff](https://via.placeholder.com/15/3300ff/3300ff.png) `#3300ff`|
|433|46|0|255|![#2e00ff](https://via.placeholder.com/15/2e00ff/2e00ff.png) `#2e00ff`|
|434|40|0|255|![#2800ff](https://via.placeholder.com/15/2800ff/2800ff.png) `#2800ff`|
|435|35|0|255|![#2300ff](https://via.placeholder.com/15/2300ff/2300ff.png) `#2300ff`|
|436|29|0|255|![#1d00ff](https://via.placeholder.com/15/1d00ff/1d00ff.png) `#1d00ff`|
|437|23|0|255|![#1700ff](https://via.placeholder.com/15/1700ff/1700ff.png) `#1700ff`|
|438|17|0|255|![#1100ff](https://via.placeholder.com/15/1100ff/1100ff.png) `#1100ff`|
|439|10|0|255|![#0a00ff](https://via.placeholder.com/15/0a00ff/0a00ff.png) `#0a00ff`|
|440|0|0|255|![#0000ff](https://via.placeholder.com/15/0000ff/0000ff.png) `#0000ff`|
|441|0|11|255|![#000bff](https://via.placeholder.com/15/000bff/000bff.png) `#000bff`|
|442|0|19|255|![#0013ff](https://via.placeholder.com/15/0013ff/0013ff.png) `#0013ff`|
|443|0|27|255|![#001bff](https://via.placeholder.com/15/001bff/001bff.png) `#001bff`|
|444|0|34|255|![#0022ff](https://via.placeholder.com/15/0022ff/0022ff.png) `#0022ff`|
|445|0|40|255|![#0028ff](https://via.placeholder.com/15/0028ff/0028ff.png) `#0028ff`|
|446|0|47|255|![#002fff](https://via.placeholder.com/15/002fff/002fff.png) `#002fff`|
|447|0|53|255|![#0035ff](https://via.placeholder.com/15/0035ff/0035ff.png) `#0035ff`|
|448|0|59|255|![#003bff](https://via.placeholder.com/15/003bff/003bff.png) `#003bff`|
|449|0|65|255|![#0041ff](https://via.placeholder.com/15/0041ff/0041ff.png) `#0041ff`|
|450|0|70|255|![#0046ff](https://via.placeholder.com/15/0046ff/0046ff.png) `#0046ff`|
|451|0|76|255|![#004cff](https://via.placeholder.com/15/004cff/004cff.png) `#004cff`|
|452|0|81|255|![#0051ff](https://via.placeholder.com/15/0051ff/0051ff.png) `#0051ff`|
|453|0|87|255|![#0057ff](https://via.placeholder.com/15/0057ff/0057ff.png) `#0057ff`|
|454|0|92|255|![#005cff](https://via.placeholder.com/15/005cff/005cff.png) `#005cff`|
|455|0|97|255|![#0061ff](https://via.placeholder.com/15/0061ff/0061ff.png) `#0061ff`|
|456|0|102|255|![#0066ff](https://via.placeholder.com/15/0066ff/0066ff.png) `#0066ff`|
|457|0|108|255|![#006cff](https://via.placeholder.com/15/006cff/006cff.png) `#006cff`|
|458|0|113|255|![#0071ff](https://via.placeholder.com/15/0071ff/0071ff.png) `#0071ff`|
|459|0|118|255|![#0076ff](https://via.placeholder.com/15/0076ff/0076ff.png) `#0076ff`|
|460|0|123|255|![#007bff](https://via.placeholder.com/15/007bff/007bff.png) `#007bff`|
|461|0|127|255|![#007fff](https://via.placeholder.com/15/007fff/007fff.png) `#007fff`|
|462|0|132|255|![#0084ff](https://via.placeholder.com/15/0084ff/0084ff.png) `#0084ff`|
|463|0|137|255|![#0089ff](https://via.placeholder.com/15/0089ff/0089ff.png) `#0089ff`|
|464|0|142|255|![#008eff](https://via.placeholder.com/15/008eff/008eff.png) `#008eff`|
|465|0|146|255|![#0092ff](https://via.placeholder.com/15/0092ff/0092ff.png) `#0092ff`|
|466|0|151|255|![#0097ff](https://via.placeholder.com/15/0097ff/0097ff.png) `#0097ff`|
|467|0|156|255|![#009cff](https://via.placeholder.com/15/009cff/009cff.png) `#009cff`|
|468|0|160|255|![#00a0ff](https://via.placeholder.com/15/00a0ff/00a0ff.png) `#00a0ff`|
|469|0|165|255|![#00a5ff](https://via.placeholder.com/15/00a5ff/00a5ff.png) `#00a5ff`|
|470|0|169|255|![#00a9ff](https://via.placeholder.com/15/00a9ff/00a9ff.png) `#00a9ff`|
|471|0|174|255|![#00aeff](https://via.placeholder.com/15/00aeff/00aeff.png) `#00aeff`|
|472|0|178|255|![#00b2ff](https://via.placeholder.com/15/00b2ff/00b2ff.png) `#00b2ff`|
|473|0|183|255|![#00b7ff](https://via.placeholder.com/15/00b7ff/00b7ff.png) `#00b7ff`|
|474|0|187|255|![#00bbff](https://via.placeholder.com/15/00bbff/00bbff.png) `#00bbff`|
|475|0|192|255|![#00c0ff](https://via.placeholder.com/15/00c0ff/00c0ff.png) `#00c0ff`|
|476|0|196|255|![#00c4ff](https://via.placeholder.com/15/00c4ff/00c4ff.png) `#00c4ff`|
|477|0|200|255|![#00c8ff](https://via.placeholder.com/15/00c8ff/00c8ff.png) `#00c8ff`|
|478|0|205|255|![#00cdff](https://via.placeholder.com/15/00cdff/00cdff.png) `#00cdff`|
|479|0|209|255|![#00d1ff](https://via.placeholder.com/15/00d1ff/00d1ff.png) `#00d1ff`|
|480|0|213|255|![#00d5ff](https://via.placeholder.com/15/00d5ff/00d5ff.png) `#00d5ff`|
|481|0|218|255|![#00daff](https://via.placeholder.com/15/00daff/00daff.png) `#00daff`|
|482|0|222|255|![#00deff](https://via.placeholder.com/15/00deff/00deff.png) `#00deff`|
|483|0|226|255|![#00e2ff](https://via.placeholder.com/15/00e2ff/00e2ff.png) `#00e2ff`|
|484|0|230|255|![#00e6ff](https://via.placeholder.com/15/00e6ff/00e6ff.png) `#00e6ff`|
|485|0|234|255|![#00eaff](https://via.placeholder.com/15/00eaff/00eaff.png) `#00eaff`|
|486|0|239|255|![#00efff](https://via.placeholder.com/15/00efff/00efff.png) `#00efff`|
|487|0|243|255|![#00f3ff](https://via.placeholder.com/15/00f3ff/00f3ff.png) `#00f3ff`|
|488|0|247|255|![#00f7ff](https://via.placeholder.com/15/00f7ff/00f7ff.png) `#00f7ff`|
|489|0|251|255|![#00fbff](https://via.placeholder.com/15/00fbff/00fbff.png) `#00fbff`|
|490|0|255|255|![#00ffff](https://via.placeholder.com/15/00ffff/00ffff.png) `#00ffff`|
|491|0|255|245|![#00fff5](https://via.placeholder.com/15/00fff5/00fff5.png) `#00fff5`|
|492|0|255|234|![#00ffea](https://via.placeholder.com/15/00ffea/00ffea.png) `#00ffea`|
|493|0|255|224|![#00ffe0](https://via.placeholder.com/15/00ffe0/00ffe0.png) `#00ffe0`|
|494|0|255|213|![#00ffd5](https://via.placeholder.com/15/00ffd5/00ffd5.png) `#00ffd5`|
|495|0|255|203|![#00ffcb](https://via.placeholder.com/15/00ffcb/00ffcb.png) `#00ffcb`|
|496|0|255|192|![#00ffc0](https://via.placeholder.com/15/00ffc0/00ffc0.png) `#00ffc0`|
|497|0|255|181|![#00ffb5](https://via.placeholder.com/15/00ffb5/00ffb5.png) `#00ffb5`|
|498|0|255|169|![#00ffa9](https://via.placeholder.com/15/00ffa9/00ffa9.png) `#00ffa9`|
|499|0|255|158|![#00ff9e](https://via.placeholder.com/15/00ff9e/00ff9e.png) `#00ff9e`|
|500|0|255|146|![#00ff92](https://via.placeholder.com/15/00ff92/00ff92.png) `#00ff92`|
|501|0|255|135|![#00ff87](https://via.placeholder.com/15/00ff87/00ff87.png) `#00ff87`|
|502|0|255|123|![#00ff7b](https://via.placeholder.com/15/00ff7b/00ff7b.png) `#00ff7b`|
|503|0|255|110|![#00ff6e](https://via.placeholder.com/15/00ff6e/00ff6e.png) `#00ff6e`|
|504|0|255|97|![#00ff61](https://via.placeholder.com/15/00ff61/00ff61.png) `#00ff61`|
|505|0|255|84|![#00ff54](https://via.placeholder.com/15/00ff54/00ff54.png) `#00ff54`|
|506|0|255|70|![#00ff46](https://via.placeholder.com/15/00ff46/00ff46.png) `#00ff46`|
|507|0|255|56|![#00ff38](https://via.placeholder.com/15/00ff38/00ff38.png) `#00ff38`|
|508|0|255|40|![#00ff28](https://via.placeholder.com/15/00ff28/00ff28.png) `#00ff28`|
|509|0|255|23|![#00ff17](https://via.placeholder.com/15/00ff17/00ff17.png) `#00ff17`|
|510|0|255|0|![#00ff00](https://via.placeholder.com/15/00ff00/00ff00.png) `#00ff00`|
|511|9|255|0|![#09ff00](https://via.placeholder.com/15/09ff00/09ff00.png) `#09ff00`|
|512|15|255|0|![#0fff00](https://via.placeholder.com/15/0fff00/0fff00.png) `#0fff00`|
|513|21|255|0|![#15ff00](https://via.placeholder.com/15/15ff00/15ff00.png) `#15ff00`|
|514|26|255|0|![#1aff00](https://via.placeholder.com/15/1aff00/1aff00.png) `#1aff00`|
|515|31|255|0|![#1fff00](https://via.placeholder.com/15/1fff00/1fff00.png) `#1fff00`|
|516|36|255|0|![#24ff00](https://via.placeholder.com/15/24ff00/24ff00.png) `#24ff00`|
|517|40|255|0|![#28ff00](https://via.placeholder.com/15/28ff00/28ff00.png) `#28ff00`|
|518|45|255|0|![#2dff00](https://via.placeholder.com/15/2dff00/2dff00.png) `#2dff00`|
|519|49|255|0|![#31ff00](https://via.placeholder.com/15/31ff00/31ff00.png) `#31ff00`|
|520|54|255|0|![#36ff00](https://via.placeholder.com/15/36ff00/36ff00.png) `#36ff00`|
|521|58|255|0|![#3aff00](https://via.placeholder.com/15/3aff00/3aff00.png) `#3aff00`|
|522|62|255|0|![#3eff00](https://via.placeholder.com/15/3eff00/3eff00.png) `#3eff00`|
|523|66|255|0|![#42ff00](https://via.placeholder.com/15/42ff00/42ff00.png) `#42ff00`|
|524|70|255|0|![#46ff00](https://via.placeholder.com/15/46ff00/46ff00.png) `#46ff00`|
|525|74|255|0|![#4aff00](https://via.placeholder.com/15/4aff00/4aff00.png) `#4aff00`|
|526|78|255|0|![#4eff00](https://via.placeholder.com/15/4eff00/4eff00.png) `#4eff00`|
|527|82|255|0|![#52ff00](https://via.placeholder.com/15/52ff00/52ff00.png) `#52ff00`|
|528|86|255|0|![#56ff00](https://via.placeholder.com/15/56ff00/56ff00.png) `#56ff00`|
|529|90|255|0|![#5aff00](https://via.placeholder.com/15/5aff00/5aff00.png) `#5aff00`|
|530|94|255|0|![#5eff00](https://via.placeholder.com/15/5eff00/5eff00.png) `#5eff00`|
|531|97|255|0|![#61ff00](https://via.placeholder.com/15/61ff00/61ff00.png) `#61ff00`|
|532|101|255|0|![#65ff00](https://via.placeholder.com/15/65ff00/65ff00.png) `#65ff00`|
|533|105|255|0|![#69ff00](https://via.placeholder.com/15/69ff00/69ff00.png) `#69ff00`|
|534|108|255|0|![#6cff00](https://via.placeholder.com/15/6cff00/6cff00.png) `#6cff00`|
|535|112|255|0|![#70ff00](https://via.placeholder.com/15/70ff00/70ff00.png) `#70ff00`|
|536|115|255|0|![#73ff00](https://via.placeholder.com/15/73ff00/73ff00.png) `#73ff00`|
|537|119|255|0|![#77ff00](https://via.placeholder.com/15/77ff00/77ff00.png) `#77ff00`|
|538|123|255|0|![#7bff00](https://via.placeholder.com/15/7bff00/7bff00.png) `#7bff00`|
|539|126|255|0|![#7eff00](https://via.placeholder.com/15/7eff00/7eff00.png) `#7eff00`|
|540|129|255|0|![#81ff00](https://via.placeholder.com/15/81ff00/81ff00.png) `#81ff00`|
|541|133|255|0|![#85ff00](https://via.placeholder.com/15/85ff00/85ff00.png) `#85ff00`|
|542|136|255|0|![#88ff00](https://via.placeholder.com/15/88ff00/88ff00.png) `#88ff00`|
|543|140|255|0|![#8cff00](https://via.placeholder.com/15/8cff00/8cff00.png) `#8cff00`|
|544|143|255|0|![#8fff00](https://via.placeholder.com/15/8fff00/8fff00.png) `#8fff00`|
|545|146|255|0|![#92ff00](https://via.placeholder.com/15/92ff00/92ff00.png) `#92ff00`|
|546|150|255|0|![#96ff00](https://via.placeholder.com/15/96ff00/96ff00.png) `#96ff00`|
|547|153|255|0|![#99ff00](https://via.placeholder.com/15/99ff00/99ff00.png) `#99ff00`|
|548|156|255|0|![#9cff00](https://via.placeholder.com/15/9cff00/9cff00.png) `#9cff00`|
|549|160|255|0|![#a0ff00](https://via.placeholder.com/15/a0ff00/a0ff00.png) `#a0ff00`|
|550|163|255|0|![#a3ff00](https://via.placeholder.com/15/a3ff00/a3ff00.png) `#a3ff00`|
|551|166|255|0|![#a6ff00](https://via.placeholder.com/15/a6ff00/a6ff00.png) `#a6ff00`|
|552|169|255|0|![#a9ff00](https://via.placeholder.com/15/a9ff00/a9ff00.png) `#a9ff00`|
|553|173|255|0|![#adff00](https://via.placeholder.com/15/adff00/adff00.png) `#adff00`|
|554|176|255|0|![#b0ff00](https://via.placeholder.com/15/b0ff00/b0ff00.png) `#b0ff00`|
|555|179|255|0|![#b3ff00](https://via.placeholder.com/15/b3ff00/b3ff00.png) `#b3ff00`|
|556|182|255|0|![#b6ff00](https://via.placeholder.com/15/b6ff00/b6ff00.png) `#b6ff00`|
|557|185|255|0|![#b9ff00](https://via.placeholder.com/15/b9ff00/b9ff00.png) `#b9ff00`|
|558|189|255|0|![#bdff00](https://via.placeholder.com/15/bdff00/bdff00.png) `#bdff00`|
|559|192|255|0|![#c0ff00](https://via.placeholder.com/15/c0ff00/c0ff00.png) `#c0ff00`|
|560|195|255|0|![#c3ff00](https://via.placeholder.com/15/c3ff00/c3ff00.png) `#c3ff00`|
|561|198|255|0|![#c6ff00](https://via.placeholder.com/15/c6ff00/c6ff00.png) `#c6ff00`|
|562|201|255|0|![#c9ff00](https://via.placeholder.com/15/c9ff00/c9ff00.png) `#c9ff00`|
|563|204|255|0|![#ccff00](https://via.placeholder.com/15/ccff00/ccff00.png) `#ccff00`|
|564|207|255|0|![#cfff00](https://via.placeholder.com/15/cfff00/cfff00.png) `#cfff00`|
|565|210|255|0|![#d2ff00](https://via.placeholder.com/15/d2ff00/d2ff00.png) `#d2ff00`|
|566|213|255|0|![#d5ff00](https://via.placeholder.com/15/d5ff00/d5ff00.png) `#d5ff00`|
|567|216|255|0|![#d8ff00](https://via.placeholder.com/15/d8ff00/d8ff00.png) `#d8ff00`|
|568|219|255|0|![#dbff00](https://via.placeholder.com/15/dbff00/dbff00.png) `#dbff00`|
|569|222|255|0|![#deff00](https://via.placeholder.com/15/deff00/deff00.png) `#deff00`|
|570|225|255|0|![#e1ff00](https://via.placeholder.com/15/e1ff00/e1ff00.png) `#e1ff00`|
|571|228|255|0|![#e4ff00](https://via.placeholder.com/15/e4ff00/e4ff00.png) `#e4ff00`|
|572|231|255|0|![#e7ff00](https://via.placeholder.com/15/e7ff00/e7ff00.png) `#e7ff00`|
|573|234|255|0|![#eaff00](https://via.placeholder.com/15/eaff00/eaff00.png) `#eaff00`|
|574|237|255|0|![#edff00](https://via.placeholder.com/15/edff00/edff00.png) `#edff00`|
|575|240|255|0|![#f0ff00](https://via.placeholder.com/15/f0ff00/f0ff00.png) `#f0ff00`|
|576|243|255|0|![#f3ff00](https://via.placeholder.com/15/f3ff00/f3ff00.png) `#f3ff00`|
|577|246|255|0|![#f6ff00](https://via.placeholder.com/15/f6ff00/f6ff00.png) `#f6ff00`|
|578|249|255|0|![#f9ff00](https://via.placeholder.com/15/f9ff00/f9ff00.png) `#f9ff00`|
|579|252|255|0|![#fcff00](https://via.placeholder.com/15/fcff00/fcff00.png) `#fcff00`|
|580|255|255|0|![#ffff00](https://via.placeholder.com/15/ffff00/ffff00.png) `#ffff00`|
|581|255|252|0|![#fffc00](https://via.placeholder.com/15/fffc00/fffc00.png) `#fffc00`|
|582|255|249|0|![#fff900](https://via.placeholder.com/15/fff900/fff900.png) `#fff900`|
|583|255|246|0|![#fff600](https://via.placeholder.com/15/fff600/fff600.png) `#fff600`|
|584|255|242|0|![#fff200](https://via.placeholder.com/15/fff200/fff200.png) `#fff200`|
|585|255|239|0|![#ffef00](https://via.placeholder.com/15/ffef00/ffef00.png) `#ffef00`|
|586|255|236|0|![#ffec00](https://via.placeholder.com/15/ffec00/ffec00.png) `#ffec00`|
|587|255|233|0|![#ffe900](https://via.placeholder.com/15/ffe900/ffe900.png) `#ffe900`|
|588|255|230|0|![#ffe600](https://via.placeholder.com/15/ffe600/ffe600.png) `#ffe600`|
|589|255|226|0|![#ffe200](https://via.placeholder.com/15/ffe200/ffe200.png) `#ffe200`|
|590|255|223|0|![#ffdf00](https://via.placeholder.com/15/ffdf00/ffdf00.png) `#ffdf00`|
|591|255|220|0|![#ffdc00](https://via.placeholder.com/15/ffdc00/ffdc00.png) `#ffdc00`|
|592|255|217|0|![#ffd900](https://via.placeholder.com/15/ffd900/ffd900.png) `#ffd900`|
|593|255|213|0|![#ffd500](https://via.placeholder.com/15/ffd500/ffd500.png) `#ffd500`|
|594|255|210|0|![#ffd200](https://via.placeholder.com/15/ffd200/ffd200.png) `#ffd200`|
|595|255|207|0|![#ffcf00](https://via.placeholder.com/15/ffcf00/ffcf00.png) `#ffcf00`|
|596|255|203|0|![#ffcb00](https://via.placeholder.com/15/ffcb00/ffcb00.png) `#ffcb00`|
|597|255|200|0|![#ffc800](https://via.placeholder.com/15/ffc800/ffc800.png) `#ffc800`|
|598|255|197|0|![#ffc500](https://via.placeholder.com/15/ffc500/ffc500.png) `#ffc500`|
|599|255|193|0|![#ffc100](https://via.placeholder.com/15/ffc100/ffc100.png) `#ffc100`|
|600|255|190|0|![#ffbe00](https://via.placeholder.com/15/ffbe00/ffbe00.png) `#ffbe00`|
|601|255|187|0|![#ffbb00](https://via.placeholder.com/15/ffbb00/ffbb00.png) `#ffbb00`|
|602|255|183|0|![#ffb700](https://via.placeholder.com/15/ffb700/ffb700.png) `#ffb700`|
|603|255|180|0|![#ffb400](https://via.placeholder.com/15/ffb400/ffb400.png) `#ffb400`|
|604|255|176|0|![#ffb000](https://via.placeholder.com/15/ffb000/ffb000.png) `#ffb000`|
|605|255|173|0|![#ffad00](https://via.placeholder.com/15/ffad00/ffad00.png) `#ffad00`|
|606|255|169|0|![#ffa900](https://via.placeholder.com/15/ffa900/ffa900.png) `#ffa900`|
|607|255|166|0|![#ffa600](https://via.placeholder.com/15/ffa600/ffa600.png) `#ffa600`|
|608|255|162|0|![#ffa200](https://via.placeholder.com/15/ffa200/ffa200.png) `#ffa200`|
|609|255|159|0|![#ff9f00](https://via.placeholder.com/15/ff9f00/ff9f00.png) `#ff9f00`|
|610|255|155|0|![#ff9b00](https://via.placeholder.com/15/ff9b00/ff9b00.png) `#ff9b00`|
|611|255|152|0|![#ff9800](https://via.placeholder.com/15/ff9800/ff9800.png) `#ff9800`|
|612|255|148|0|![#ff9400](https://via.placeholder.com/15/ff9400/ff9400.png) `#ff9400`|
|613|255|145|0|![#ff9100](https://via.placeholder.com/15/ff9100/ff9100.png) `#ff9100`|
|614|255|141|0|![#ff8d00](https://via.placeholder.com/15/ff8d00/ff8d00.png) `#ff8d00`|
|615|255|137|0|![#ff8900](https://via.placeholder.com/15/ff8900/ff8900.png) `#ff8900`|
|616|255|134|0|![#ff8600](https://via.placeholder.com/15/ff8600/ff8600.png) `#ff8600`|
|617|255|130|0|![#ff8200](https://via.placeholder.com/15/ff8200/ff8200.png) `#ff8200`|
|618|255|126|0|![#ff7e00](https://via.placeholder.com/15/ff7e00/ff7e00.png) `#ff7e00`|
|619|255|123|0|![#ff7b00](https://via.placeholder.com/15/ff7b00/ff7b00.png) `#ff7b00`|
|620|255|119|0|![#ff7700](https://via.placeholder.com/15/ff7700/ff7700.png) `#ff7700`|
|621|255|115|0|![#ff7300](https://via.placeholder.com/15/ff7300/ff7300.png) `#ff7300`|
|622|255|111|0|![#ff6f00](https://via.placeholder.com/15/ff6f00/ff6f00.png) `#ff6f00`|
|623|255|107|0|![#ff6b00](https://via.placeholder.com/15/ff6b00/ff6b00.png) `#ff6b00`|
|624|255|103|0|![#ff6700](https://via.placeholder.com/15/ff6700/ff6700.png) `#ff6700`|
|625|255|99|0|![#ff6300](https://via.placeholder.com/15/ff6300/ff6300.png) `#ff6300`|
|626|255|95|0|![#ff5f00](https://via.placeholder.com/15/ff5f00/ff5f00.png) `#ff5f00`|
|627|255|91|0|![#ff5b00](https://via.placeholder.com/15/ff5b00/ff5b00.png) `#ff5b00`|
|628|255|87|0|![#ff5700](https://via.placeholder.com/15/ff5700/ff5700.png) `#ff5700`|
|629|255|83|0|![#ff5300](https://via.placeholder.com/15/ff5300/ff5300.png) `#ff5300`|
|630|255|79|0|![#ff4f00](https://via.placeholder.com/15/ff4f00/ff4f00.png) `#ff4f00`|
|631|255|75|0|![#ff4b00](https://via.placeholder.com/15/ff4b00/ff4b00.png) `#ff4b00`|
|632|255|70|0|![#ff4600](https://via.placeholder.com/15/ff4600/ff4600.png) `#ff4600`|
|633|255|66|0|![#ff4200](https://via.placeholder.com/15/ff4200/ff4200.png) `#ff4200`|
|634|255|62|0|![#ff3e00](https://via.placeholder.com/15/ff3e00/ff3e00.png) `#ff3e00`|
|635|255|57|0|![#ff3900](https://via.placeholder.com/15/ff3900/ff3900.png) `#ff3900`|
|636|255|52|0|![#ff3400](https://via.placeholder.com/15/ff3400/ff3400.png) `#ff3400`|
|637|255|48|0|![#ff3000](https://via.placeholder.com/15/ff3000/ff3000.png) `#ff3000`|
|638|255|43|0|![#ff2b00](https://via.placeholder.com/15/ff2b00/ff2b00.png) `#ff2b00`|
|639|255|38|0|![#ff2600](https://via.placeholder.com/15/ff2600/ff2600.png) `#ff2600`|
|640|255|33|0|![#ff2100](https://via.placeholder.com/15/ff2100/ff2100.png) `#ff2100`|
|641|255|27|0|![#ff1b00](https://via.placeholder.com/15/ff1b00/ff1b00.png) `#ff1b00`|
|642|255|22|0|![#ff1600](https://via.placeholder.com/15/ff1600/ff1600.png) `#ff1600`|
|643|255|16|0|![#ff1000](https://via.placeholder.com/15/ff1000/ff1000.png) `#ff1000`|
|644|255|9|0|![#ff0900](https://via.placeholder.com/15/ff0900/ff0900.png) `#ff0900`|
|645|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|646|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|647|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|648|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|649|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|650|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|651|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|652|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|653|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|654|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|655|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|656|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|657|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|658|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|659|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|660|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|661|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|662|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|663|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|664|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|665|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|666|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|667|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|668|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|669|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|670|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|671|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|672|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|673|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|674|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|675|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|676|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|677|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|678|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|679|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|680|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|681|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|682|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|683|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|684|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|685|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|686|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|687|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|688|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|689|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|690|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|691|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|692|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|693|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|694|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|695|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|696|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|697|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|698|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|699|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|700|255|0|0|![#ff0000](https://via.placeholder.com/15/ff0000/ff0000.png) `#ff0000`|
|701|253|0|0|![#fd0000](https://via.placeholder.com/15/fd0000/fd0000.png) `#fd0000`|
|702|251|0|0|![#fb0000](https://via.placeholder.com/15/fb0000/fb0000.png) `#fb0000`|
|703|250|0|0|![#fa0000](https://via.placeholder.com/15/fa0000/fa0000.png) `#fa0000`|
|704|248|0|0|![#f80000](https://via.placeholder.com/15/f80000/f80000.png) `#f80000`|
|705|246|0|0|![#f60000](https://via.placeholder.com/15/f60000/f60000.png) `#f60000`|
|706|244|0|0|![#f40000](https://via.placeholder.com/15/f40000/f40000.png) `#f40000`|
|707|242|0|0|![#f20000](https://via.placeholder.com/15/f20000/f20000.png) `#f20000`|
|708|241|0|0|![#f10000](https://via.placeholder.com/15/f10000/f10000.png) `#f10000`|
|709|239|0|0|![#ef0000](https://via.placeholder.com/15/ef0000/ef0000.png) `#ef0000`|
|710|237|0|0|![#ed0000](https://via.placeholder.com/15/ed0000/ed0000.png) `#ed0000`|
|711|235|0|0|![#eb0000](https://via.placeholder.com/15/eb0000/eb0000.png) `#eb0000`|
|712|233|0|0|![#e90000](https://via.placeholder.com/15/e90000/e90000.png) `#e90000`|
|713|232|0|0|![#e80000](https://via.placeholder.com/15/e80000/e80000.png) `#e80000`|
|714|230|0|0|![#e60000](https://via.placeholder.com/15/e60000/e60000.png) `#e60000`|
|715|228|0|0|![#e40000](https://via.placeholder.com/15/e40000/e40000.png) `#e40000`|
|716|226|0|0|![#e20000](https://via.placeholder.com/15/e20000/e20000.png) `#e20000`|
|717|224|0|0|![#e00000](https://via.placeholder.com/15/e00000/e00000.png) `#e00000`|
|718|222|0|0|![#de0000](https://via.placeholder.com/15/de0000/de0000.png) `#de0000`|
|719|220|0|0|![#dc0000](https://via.placeholder.com/15/dc0000/dc0000.png) `#dc0000`|
|720|219|0|0|![#db0000](https://via.placeholder.com/15/db0000/db0000.png) `#db0000`|
|721|217|0|0|![#d90000](https://via.placeholder.com/15/d90000/d90000.png) `#d90000`|
|722|215|0|0|![#d70000](https://via.placeholder.com/15/d70000/d70000.png) `#d70000`|
|723|213|0|0|![#d50000](https://via.placeholder.com/15/d50000/d50000.png) `#d50000`|
|724|211|0|0|![#d30000](https://via.placeholder.com/15/d30000/d30000.png) `#d30000`|
|725|209|0|0|![#d10000](https://via.placeholder.com/15/d10000/d10000.png) `#d10000`|
|726|207|0|0|![#cf0000](https://via.placeholder.com/15/cf0000/cf0000.png) `#cf0000`|
|727|206|0|0|![#ce0000](https://via.placeholder.com/15/ce0000/ce0000.png) `#ce0000`|
|728|204|0|0|![#cc0000](https://via.placeholder.com/15/cc0000/cc0000.png) `#cc0000`|
|729|202|0|0|![#ca0000](https://via.placeholder.com/15/ca0000/ca0000.png) `#ca0000`|
|730|200|0|0|![#c80000](https://via.placeholder.com/15/c80000/c80000.png) `#c80000`|
|731|198|0|0|![#c60000](https://via.placeholder.com/15/c60000/c60000.png) `#c60000`|
|732|196|0|0|![#c40000](https://via.placeholder.com/15/c40000/c40000.png) `#c40000`|
|733|194|0|0|![#c20000](https://via.placeholder.com/15/c20000/c20000.png) `#c20000`|
|734|192|0|0|![#c00000](https://via.placeholder.com/15/c00000/c00000.png) `#c00000`|
|735|190|0|0|![#be0000](https://via.placeholder.com/15/be0000/be0000.png) `#be0000`|
|736|188|0|0|![#bc0000](https://via.placeholder.com/15/bc0000/bc0000.png) `#bc0000`|
|737|186|0|0|![#ba0000](https://via.placeholder.com/15/ba0000/ba0000.png) `#ba0000`|
|738|185|0|0|![#b90000](https://via.placeholder.com/15/b90000/b90000.png) `#b90000`|
|739|183|0|0|![#b70000](https://via.placeholder.com/15/b70000/b70000.png) `#b70000`|
|740|181|0|0|![#b50000](https://via.placeholder.com/15/b50000/b50000.png) `#b50000`|
|741|179|0|0|![#b30000](https://via.placeholder.com/15/b30000/b30000.png) `#b30000`|
|742|177|0|0|![#b10000](https://via.placeholder.com/15/b10000/b10000.png) `#b10000`|
|743|175|0|0|![#af0000](https://via.placeholder.com/15/af0000/af0000.png) `#af0000`|
|744|173|0|0|![#ad0000](https://via.placeholder.com/15/ad0000/ad0000.png) `#ad0000`|
|745|171|0|0|![#ab0000](https://via.placeholder.com/15/ab0000/ab0000.png) `#ab0000`|
|746|169|0|0|![#a90000](https://via.placeholder.com/15/a90000/a90000.png) `#a90000`|
|747|167|0|0|![#a70000](https://via.placeholder.com/15/a70000/a70000.png) `#a70000`|
|748|165|0|0|![#a50000](https://via.placeholder.com/15/a50000/a50000.png) `#a50000`|
|749|163|0|0|![#a30000](https://via.placeholder.com/15/a30000/a30000.png) `#a30000`|
|750|161|0|0|![#a10000](https://via.placeholder.com/15/a10000/a10000.png) `#a10000`|
|751|159|0|0|![#9f0000](https://via.placeholder.com/15/9f0000/9f0000.png) `#9f0000`|
|752|157|0|0|![#9d0000](https://via.placeholder.com/15/9d0000/9d0000.png) `#9d0000`|
|753|155|0|0|![#9b0000](https://via.placeholder.com/15/9b0000/9b0000.png) `#9b0000`|
|754|153|0|0|![#990000](https://via.placeholder.com/15/990000/990000.png) `#990000`|
|755|151|0|0|![#970000](https://via.placeholder.com/15/970000/970000.png) `#970000`|
|756|149|0|0|![#950000](https://via.placeholder.com/15/950000/950000.png) `#950000`|
|757|147|0|0|![#930000](https://via.placeholder.com/15/930000/930000.png) `#930000`|
|758|145|0|0|![#910000](https://via.placeholder.com/15/910000/910000.png) `#910000`|
|759|143|0|0|![#8f0000](https://via.placeholder.com/15/8f0000/8f0000.png) `#8f0000`|
|760|141|0|0|![#8d0000](https://via.placeholder.com/15/8d0000/8d0000.png) `#8d0000`|
|761|138|0|0|![#8a0000](https://via.placeholder.com/15/8a0000/8a0000.png) `#8a0000`|
|762|136|0|0|![#880000](https://via.placeholder.com/15/880000/880000.png) `#880000`|
|763|134|0|0|![#860000](https://via.placeholder.com/15/860000/860000.png) `#860000`|
|764|132|0|0|![#840000](https://via.placeholder.com/15/840000/840000.png) `#840000`|
|765|130|0|0|![#820000](https://via.placeholder.com/15/820000/820000.png) `#820000`|
|766|128|0|0|![#800000](https://via.placeholder.com/15/800000/800000.png) `#800000`|
|767|126|0|0|![#7e0000](https://via.placeholder.com/15/7e0000/7e0000.png) `#7e0000`|
|768|124|0|0|![#7c0000](https://via.placeholder.com/15/7c0000/7c0000.png) `#7c0000`|
|769|122|0|0|![#7a0000](https://via.placeholder.com/15/7a0000/7a0000.png) `#7a0000`|
|770|119|0|0|![#770000](https://via.placeholder.com/15/770000/770000.png) `#770000`|
|771|117|0|0|![#750000](https://via.placeholder.com/15/750000/750000.png) `#750000`|
|772|115|0|0|![#730000](https://via.placeholder.com/15/730000/730000.png) `#730000`|
|773|113|0|0|![#710000](https://via.placeholder.com/15/710000/710000.png) `#710000`|
|774|111|0|0|![#6f0000](https://via.placeholder.com/15/6f0000/6f0000.png) `#6f0000`|
|775|109|0|0|![#6d0000](https://via.placeholder.com/15/6d0000/6d0000.png) `#6d0000`|
|776|106|0|0|![#6a0000](https://via.placeholder.com/15/6a0000/6a0000.png) `#6a0000`|
|777|104|0|0|![#680000](https://via.placeholder.com/15/680000/680000.png) `#680000`|
|778|102|0|0|![#660000](https://via.placeholder.com/15/660000/660000.png) `#660000`|
|779|100|0|0|![#640000](https://via.placeholder.com/15/640000/640000.png) `#640000`|
|780|97|0|0|![#610000](https://via.placeholder.com/15/610000/610000.png) `#610000`|
