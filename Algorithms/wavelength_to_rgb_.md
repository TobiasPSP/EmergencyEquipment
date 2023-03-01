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


| Wavelength (nm) | R | G | B | Hex | Sample |
|:---------:|:---:|:---:|:---:|:---:|:---:|
|380|97|0|97|#610061|$${\color{#610061}SAMPLECOLOR}$$|
|381|100|0|102|#640066|$${\color{#640066}SAMPLECOLOR}$$|
|382|103|0|106|#67006A|$${\color{#67006A}SAMPLECOLOR}$$|
|383|106|0|111|#6A006F|$${\color{#6A006F}SAMPLECOLOR}$$|
|384|109|0|115|#6D0073|$${\color{#6D0073}SAMPLECOLOR}$$|
|385|111|0|119|#6F0077|$${\color{#6F0077}SAMPLECOLOR}$$|
|386|114|0|124|#72007C|$${\color{#72007C}SAMPLECOLOR}$$|
|387|116|0|128|#740080|$${\color{#740080}SAMPLECOLOR}$$|
|388|118|0|132|#760084|$${\color{#760084}SAMPLECOLOR}$$|
|389|120|0|136|#780088|$${\color{#780088}SAMPLECOLOR}$$|
|390|121|0|141|#79008D|$${\color{#79008D}SAMPLECOLOR}$$|
|391|123|0|145|#7B0091|$${\color{#7B0091}SAMPLECOLOR}$$|
|392|124|0|149|#7C0095|$${\color{#7C0095}SAMPLECOLOR}$$|
|393|126|0|153|#7E0099|$${\color{#7E0099}SAMPLECOLOR}$$|
|394|127|0|157|#7F009D|$${\color{#7F009D}SAMPLECOLOR}$$|
|395|128|0|161|#8000A1|$${\color{#8000A1}SAMPLECOLOR}$$|
|396|129|0|165|#8100A5|$${\color{#8100A5}SAMPLECOLOR}$$|
|397|129|0|169|#8100A9|$${\color{#8100A9}SAMPLECOLOR}$$|
|398|130|0|173|#8200AD|$${\color{#8200AD}SAMPLECOLOR}$$|
|399|130|0|177|#8200B1|$${\color{#8200B1}SAMPLECOLOR}$$|
|400|131|0|181|#8300B5|$${\color{#8300B5}SAMPLECOLOR}$$|
|401|131|0|185|#8300B9|$${\color{#8300B9}SAMPLECOLOR}$$|
|402|131|0|188|#8300BC|$${\color{#8300BC}SAMPLECOLOR}$$|
|403|131|0|192|#8300C0|$${\color{#8300C0}SAMPLECOLOR}$$|
|404|130|0|196|#8200C4|$${\color{#8200C4}SAMPLECOLOR}$$|
|405|130|0|200|#8200C8|$${\color{#8200C8}SAMPLECOLOR}$$|
|406|129|0|204|#8100CC|$${\color{#8100CC}SAMPLECOLOR}$$|
|407|129|0|207|#8100CF|$${\color{#8100CF}SAMPLECOLOR}$$|
|408|128|0|211|#8000D3|$${\color{#8000D3}SAMPLECOLOR}$$|
|409|127|0|215|#7F00D7|$${\color{#7F00D7}SAMPLECOLOR}$$|
|410|126|0|219|#7E00DB|$${\color{#7E00DB}SAMPLECOLOR}$$|
|411|124|0|222|#7C00DE|$${\color{#7C00DE}SAMPLECOLOR}$$|
|412|123|0|226|#7B00E2|$${\color{#7B00E2}SAMPLECOLOR}$$|
|413|121|0|230|#7900E6|$${\color{#7900E6}SAMPLECOLOR}$$|
|414|120|0|233|#7800E9|$${\color{#7800E9}SAMPLECOLOR}$$|
|415|118|0|237|#7600ED|$${\color{#7600ED}SAMPLECOLOR}$$|
|416|116|0|241|#7400F1|$${\color{#7400F1}SAMPLECOLOR}$$|
|417|113|0|244|#7100F4|$${\color{#7100F4}SAMPLECOLOR}$$|
|418|111|0|248|#6F00F8|$${\color{#6F00F8}SAMPLECOLOR}$$|
|419|109|0|251|#6D00FB|$${\color{#6D00FB}SAMPLECOLOR}$$|
|420|106|0|255|#6A00FF|$${\color{#6A00FF}SAMPLECOLOR}$$|
|421|102|0|255|#6600FF|$${\color{#6600FF}SAMPLECOLOR}$$|
|422|97|0|255|#6100FF|$${\color{#6100FF}SAMPLECOLOR}$$|
|423|93|0|255|#5D00FF|$${\color{#5D00FF}SAMPLECOLOR}$$|
|424|89|0|255|#5900FF|$${\color{#5900FF}SAMPLECOLOR}$$|
|425|84|0|255|#5400FF|$${\color{#5400FF}SAMPLECOLOR}$$|
|426|80|0|255|#5000FF|$${\color{#5000FF}SAMPLECOLOR}$$|
|427|75|0|255|#4B00FF|$${\color{#4B00FF}SAMPLECOLOR}$$|
|428|70|0|255|#4600FF|$${\color{#4600FF}SAMPLECOLOR}$$|
|429|66|0|255|#4200FF|$${\color{#4200FF}SAMPLECOLOR}$$|
|430|61|0|255|#3D00FF|$${\color{#3D00FF}SAMPLECOLOR}$$|
|431|56|0|255|#3800FF|$${\color{#3800FF}SAMPLECOLOR}$$|
|432|51|0|255|#3300FF|$${\color{#3300FF}SAMPLECOLOR}$$|
|433|46|0|255|#2E00FF|$${\color{#2E00FF}SAMPLECOLOR}$$|
|434|40|0|255|#2800FF|$${\color{#2800FF}SAMPLECOLOR}$$|
|435|35|0|255|#2300FF|$${\color{#2300FF}SAMPLECOLOR}$$|
|436|29|0|255|#1D00FF|$${\color{#1D00FF}SAMPLECOLOR}$$|
|437|23|0|255|#1700FF|$${\color{#1700FF}SAMPLECOLOR}$$|
|438|17|0|255|#1100FF|$${\color{#1100FF}SAMPLECOLOR}$$|
|439|10|0|255|#0A00FF|$${\color{#0A00FF}SAMPLECOLOR}$$|
|440|0|0|255|#0000FF|$${\color{#0000FF}SAMPLECOLOR}$$|
|441|0|11|255|#000BFF|$${\color{#000BFF}SAMPLECOLOR}$$|
|442|0|19|255|#0013FF|$${\color{#0013FF}SAMPLECOLOR}$$|
|443|0|27|255|#001BFF|$${\color{#001BFF}SAMPLECOLOR}$$|
|444|0|34|255|#0022FF|$${\color{#0022FF}SAMPLECOLOR}$$|
|445|0|40|255|#0028FF|$${\color{#0028FF}SAMPLECOLOR}$$|
|446|0|47|255|#002FFF|$${\color{#002FFF}SAMPLECOLOR}$$|
|447|0|53|255|#0035FF|$${\color{#0035FF}SAMPLECOLOR}$$|
|448|0|59|255|#003BFF|$${\color{#003BFF}SAMPLECOLOR}$$|
|449|0|65|255|#0041FF|$${\color{#0041FF}SAMPLECOLOR}$$|
|450|0|70|255|#0046FF|$${\color{#0046FF}SAMPLECOLOR}$$|
|451|0|76|255|#004CFF|$${\color{#004CFF}SAMPLECOLOR}$$|
|452|0|81|255|#0051FF|$${\color{#0051FF}SAMPLECOLOR}$$|
|453|0|87|255|#0057FF|$${\color{#0057FF}SAMPLECOLOR}$$|
|454|0|92|255|#005CFF|$${\color{#005CFF}SAMPLECOLOR}$$|
|455|0|97|255|#0061FF|$${\color{#0061FF}SAMPLECOLOR}$$|
|456|0|102|255|#0066FF|$${\color{#0066FF}SAMPLECOLOR}$$|
|457|0|108|255|#006CFF|$${\color{#006CFF}SAMPLECOLOR}$$|
|458|0|113|255|#0071FF|$${\color{#0071FF}SAMPLECOLOR}$$|
|459|0|118|255|#0076FF|$${\color{#0076FF}SAMPLECOLOR}$$|
|460|0|123|255|#007BFF|$${\color{#007BFF}SAMPLECOLOR}$$|
|461|0|127|255|#007FFF|$${\color{#007FFF}SAMPLECOLOR}$$|
|462|0|132|255|#0084FF|$${\color{#0084FF}SAMPLECOLOR}$$|
|463|0|137|255|#0089FF|$${\color{#0089FF}SAMPLECOLOR}$$|
|464|0|142|255|#008EFF|$${\color{#008EFF}SAMPLECOLOR}$$|
|465|0|146|255|#0092FF|$${\color{#0092FF}SAMPLECOLOR}$$|
|466|0|151|255|#0097FF|$${\color{#0097FF}SAMPLECOLOR}$$|
|467|0|156|255|#009CFF|$${\color{#009CFF}SAMPLECOLOR}$$|
|468|0|160|255|#00A0FF|$${\color{#00A0FF}SAMPLECOLOR}$$|
|469|0|165|255|#00A5FF|$${\color{#00A5FF}SAMPLECOLOR}$$|
|470|0|169|255|#00A9FF|$${\color{#00A9FF}SAMPLECOLOR}$$|
|471|0|174|255|#00AEFF|$${\color{#00AEFF}SAMPLECOLOR}$$|
|472|0|178|255|#00B2FF|$${\color{#00B2FF}SAMPLECOLOR}$$|
|473|0|183|255|#00B7FF|$${\color{#00B7FF}SAMPLECOLOR}$$|
|474|0|187|255|#00BBFF|$${\color{#00BBFF}SAMPLECOLOR}$$|
|475|0|192|255|#00C0FF|$${\color{#00C0FF}SAMPLECOLOR}$$|
|476|0|196|255|#00C4FF|$${\color{#00C4FF}SAMPLECOLOR}$$|
|477|0|200|255|#00C8FF|$${\color{#00C8FF}SAMPLECOLOR}$$|
|478|0|205|255|#00CDFF|$${\color{#00CDFF}SAMPLECOLOR}$$|
|479|0|209|255|#00D1FF|$${\color{#00D1FF}SAMPLECOLOR}$$|
|480|0|213|255|#00D5FF|$${\color{#00D5FF}SAMPLECOLOR}$$|
|481|0|218|255|#00DAFF|$${\color{#00DAFF}SAMPLECOLOR}$$|
|482|0|222|255|#00DEFF|$${\color{#00DEFF}SAMPLECOLOR}$$|
|483|0|226|255|#00E2FF|$${\color{#00E2FF}SAMPLECOLOR}$$|
|484|0|230|255|#00E6FF|$${\color{#00E6FF}SAMPLECOLOR}$$|
|485|0|234|255|#00EAFF|$${\color{#00EAFF}SAMPLECOLOR}$$|
|486|0|239|255|#00EFFF|$${\color{#00EFFF}SAMPLECOLOR}$$|
|487|0|243|255|#00F3FF|$${\color{#00F3FF}SAMPLECOLOR}$$|
|488|0|247|255|#00F7FF|$${\color{#00F7FF}SAMPLECOLOR}$$|
|489|0|251|255|#00FBFF|$${\color{#00FBFF}SAMPLECOLOR}$$|
|490|0|255|255|#00FFFF|$${\color{#00FFFF}SAMPLECOLOR}$$|
|491|0|255|245|#00FFF5|$${\color{#00FFF5}SAMPLECOLOR}$$|
|492|0|255|234|#00FFEA|$${\color{#00FFEA}SAMPLECOLOR}$$|
|493|0|255|224|#00FFE0|$${\color{#00FFE0}SAMPLECOLOR}$$|
|494|0|255|213|#00FFD5|$${\color{#00FFD5}SAMPLECOLOR}$$|
|495|0|255|203|#00FFCB|$${\color{#00FFCB}SAMPLECOLOR}$$|
|496|0|255|192|#00FFC0|$${\color{#00FFC0}SAMPLECOLOR}$$|
|497|0|255|181|#00FFB5|$${\color{#00FFB5}SAMPLECOLOR}$$|
|498|0|255|169|#00FFA9|$${\color{#00FFA9}SAMPLECOLOR}$$|
|499|0|255|158|#00FF9E|$${\color{#00FF9E}SAMPLECOLOR}$$|
|500|0|255|146|#00FF92|$${\color{#00FF92}SAMPLECOLOR}$$|
|501|0|255|135|#00FF87|$${\color{#00FF87}SAMPLECOLOR}$$|
|502|0|255|123|#00FF7B|$${\color{#00FF7B}SAMPLECOLOR}$$|
|503|0|255|110|#00FF6E|$${\color{#00FF6E}SAMPLECOLOR}$$|
|504|0|255|97|#00FF61|$${\color{#00FF61}SAMPLECOLOR}$$|
|505|0|255|84|#00FF54|$${\color{#00FF54}SAMPLECOLOR}$$|
|506|0|255|70|#00FF46|$${\color{#00FF46}SAMPLECOLOR}$$|
|507|0|255|56|#00FF38|$${\color{#00FF38}SAMPLECOLOR}$$|
|508|0|255|40|#00FF28|$${\color{#00FF28}SAMPLECOLOR}$$|
|509|0|255|23|#00FF17|$${\color{#00FF17}SAMPLECOLOR}$$|
|510|0|255|0|#00FF00|$${\color{#00FF00}SAMPLECOLOR}$$|
|511|9|255|0|#09FF00|$${\color{#09FF00}SAMPLECOLOR}$$|
|512|15|255|0|#0FFF00|$${\color{#0FFF00}SAMPLECOLOR}$$|
|513|21|255|0|#15FF00|$${\color{#15FF00}SAMPLECOLOR}$$|
|514|26|255|0|#1AFF00|$${\color{#1AFF00}SAMPLECOLOR}$$|
|515|31|255|0|#1FFF00|$${\color{#1FFF00}SAMPLECOLOR}$$|
|516|36|255|0|#24FF00|$${\color{#24FF00}SAMPLECOLOR}$$|
|517|40|255|0|#28FF00|$${\color{#28FF00}SAMPLECOLOR}$$|
|518|45|255|0|#2DFF00|$${\color{#2DFF00}SAMPLECOLOR}$$|
|519|49|255|0|#31FF00|$${\color{#31FF00}SAMPLECOLOR}$$|
|520|54|255|0|#36FF00|$${\color{#36FF00}SAMPLECOLOR}$$|
|521|58|255|0|#3AFF00|$${\color{#3AFF00}SAMPLECOLOR}$$|
|522|62|255|0|#3EFF00|$${\color{#3EFF00}SAMPLECOLOR}$$|
|523|66|255|0|#42FF00|$${\color{#42FF00}SAMPLECOLOR}$$|
|524|70|255|0|#46FF00|$${\color{#46FF00}SAMPLECOLOR}$$|
|525|74|255|0|#4AFF00|$${\color{#4AFF00}SAMPLECOLOR}$$|
|526|78|255|0|#4EFF00|$${\color{#4EFF00}SAMPLECOLOR}$$|
|527|82|255|0|#52FF00|$${\color{#52FF00}SAMPLECOLOR}$$|
|528|86|255|0|#56FF00|$${\color{#56FF00}SAMPLECOLOR}$$|
|529|90|255|0|#5AFF00|$${\color{#5AFF00}SAMPLECOLOR}$$|
|530|94|255|0|#5EFF00|$${\color{#5EFF00}SAMPLECOLOR}$$|
|531|97|255|0|#61FF00|$${\color{#61FF00}SAMPLECOLOR}$$|
|532|101|255|0|#65FF00|$${\color{#65FF00}SAMPLECOLOR}$$|
|533|105|255|0|#69FF00|$${\color{#69FF00}SAMPLECOLOR}$$|
|534|108|255|0|#6CFF00|$${\color{#6CFF00}SAMPLECOLOR}$$|
|535|112|255|0|#70FF00|$${\color{#70FF00}SAMPLECOLOR}$$|
|536|115|255|0|#73FF00|$${\color{#73FF00}SAMPLECOLOR}$$|
|537|119|255|0|#77FF00|$${\color{#77FF00}SAMPLECOLOR}$$|
|538|123|255|0|#7BFF00|$${\color{#7BFF00}SAMPLECOLOR}$$|
|539|126|255|0|#7EFF00|$${\color{#7EFF00}SAMPLECOLOR}$$|
|540|129|255|0|#81FF00|$${\color{#81FF00}SAMPLECOLOR}$$|
|541|133|255|0|#85FF00|$${\color{#85FF00}SAMPLECOLOR}$$|
|542|136|255|0|#88FF00|$${\color{#88FF00}SAMPLECOLOR}$$|
|543|140|255|0|#8CFF00|$${\color{#8CFF00}SAMPLECOLOR}$$|
|544|143|255|0|#8FFF00|$${\color{#8FFF00}SAMPLECOLOR}$$|
|545|146|255|0|#92FF00|$${\color{#92FF00}SAMPLECOLOR}$$|
|546|150|255|0|#96FF00|$${\color{#96FF00}SAMPLECOLOR}$$|
|547|153|255|0|#99FF00|$${\color{#99FF00}SAMPLECOLOR}$$|
|548|156|255|0|#9CFF00|$${\color{#9CFF00}SAMPLECOLOR}$$|
|549|160|255|0|#A0FF00|$${\color{#A0FF00}SAMPLECOLOR}$$|
|550|163|255|0|#A3FF00|$${\color{#A3FF00}SAMPLECOLOR}$$|
|551|166|255|0|#A6FF00|$${\color{#A6FF00}SAMPLECOLOR}$$|
|552|169|255|0|#A9FF00|$${\color{#A9FF00}SAMPLECOLOR}$$|
|553|173|255|0|#ADFF00|$${\color{#ADFF00}SAMPLECOLOR}$$|
|554|176|255|0|#B0FF00|$${\color{#B0FF00}SAMPLECOLOR}$$|
|555|179|255|0|#B3FF00|$${\color{#B3FF00}SAMPLECOLOR}$$|
|556|182|255|0|#B6FF00|$${\color{#B6FF00}SAMPLECOLOR}$$|
|557|185|255|0|#B9FF00|$${\color{#B9FF00}SAMPLECOLOR}$$|
|558|189|255|0|#BDFF00|$${\color{#BDFF00}SAMPLECOLOR}$$|
|559|192|255|0|#C0FF00|$${\color{#C0FF00}SAMPLECOLOR}$$|
|560|195|255|0|#C3FF00|$${\color{#C3FF00}SAMPLECOLOR}$$|
|561|198|255|0|#C6FF00|$${\color{#C6FF00}SAMPLECOLOR}$$|
|562|201|255|0|#C9FF00|$${\color{#C9FF00}SAMPLECOLOR}$$|
|563|204|255|0|#CCFF00|$${\color{#CCFF00}SAMPLECOLOR}$$|
|564|207|255|0|#CFFF00|$${\color{#CFFF00}SAMPLECOLOR}$$|
|565|210|255|0|#D2FF00|$${\color{#D2FF00}SAMPLECOLOR}$$|
|566|213|255|0|#D5FF00|$${\color{#D5FF00}SAMPLECOLOR}$$|
|567|216|255|0|#D8FF00|$${\color{#D8FF00}SAMPLECOLOR}$$|
|568|219|255|0|#DBFF00|$${\color{#DBFF00}SAMPLECOLOR}$$|
|569|222|255|0|#DEFF00|$${\color{#DEFF00}SAMPLECOLOR}$$|
|570|225|255|0|#E1FF00|$${\color{#E1FF00}SAMPLECOLOR}$$|
|571|228|255|0|#E4FF00|$${\color{#E4FF00}SAMPLECOLOR}$$|
|572|231|255|0|#E7FF00|$${\color{#E7FF00}SAMPLECOLOR}$$|
|573|234|255|0|#EAFF00|$${\color{#EAFF00}SAMPLECOLOR}$$|
|574|237|255|0|#EDFF00|$${\color{#EDFF00}SAMPLECOLOR}$$|
|575|240|255|0|#F0FF00|$${\color{#F0FF00}SAMPLECOLOR}$$|
|576|243|255|0|#F3FF00|$${\color{#F3FF00}SAMPLECOLOR}$$|
|577|246|255|0|#F6FF00|$${\color{#F6FF00}SAMPLECOLOR}$$|
|578|249|255|0|#F9FF00|$${\color{#F9FF00}SAMPLECOLOR}$$|
|579|252|255|0|#FCFF00|$${\color{#FCFF00}SAMPLECOLOR}$$|
|580|255|255|0|#FFFF00|$${\color{#FFFF00}SAMPLECOLOR}$$|
|581|255|252|0|#FFFC00|$${\color{#FFFC00}SAMPLECOLOR}$$|
|582|255|249|0|#FFF900|$${\color{#FFF900}SAMPLECOLOR}$$|
|583|255|246|0|#FFF600|$${\color{#FFF600}SAMPLECOLOR}$$|
|584|255|242|0|#FFF200|$${\color{#FFF200}SAMPLECOLOR}$$|
|585|255|239|0|#FFEF00|$${\color{#FFEF00}SAMPLECOLOR}$$|
|586|255|236|0|#FFEC00|$${\color{#FFEC00}SAMPLECOLOR}$$|
|587|255|233|0|#FFE900|$${\color{#FFE900}SAMPLECOLOR}$$|
|588|255|230|0|#FFE600|$${\color{#FFE600}SAMPLECOLOR}$$|
|589|255|226|0|#FFE200|$${\color{#FFE200}SAMPLECOLOR}$$|
|590|255|223|0|#FFDF00|$${\color{#FFDF00}SAMPLECOLOR}$$|
|591|255|220|0|#FFDC00|$${\color{#FFDC00}SAMPLECOLOR}$$|
|592|255|217|0|#FFD900|$${\color{#FFD900}SAMPLECOLOR}$$|
|593|255|213|0|#FFD500|$${\color{#FFD500}SAMPLECOLOR}$$|
|594|255|210|0|#FFD200|$${\color{#FFD200}SAMPLECOLOR}$$|
|595|255|207|0|#FFCF00|$${\color{#FFCF00}SAMPLECOLOR}$$|
|596|255|203|0|#FFCB00|$${\color{#FFCB00}SAMPLECOLOR}$$|
|597|255|200|0|#FFC800|$${\color{#FFC800}SAMPLECOLOR}$$|
|598|255|197|0|#FFC500|$${\color{#FFC500}SAMPLECOLOR}$$|
|599|255|193|0|#FFC100|$${\color{#FFC100}SAMPLECOLOR}$$|
|600|255|190|0|#FFBE00|$${\color{#FFBE00}SAMPLECOLOR}$$|
|601|255|187|0|#FFBB00|$${\color{#FFBB00}SAMPLECOLOR}$$|
|602|255|183|0|#FFB700|$${\color{#FFB700}SAMPLECOLOR}$$|
|603|255|180|0|#FFB400|$${\color{#FFB400}SAMPLECOLOR}$$|
|604|255|176|0|#FFB000|$${\color{#FFB000}SAMPLECOLOR}$$|
|605|255|173|0|#FFAD00|$${\color{#FFAD00}SAMPLECOLOR}$$|
|606|255|169|0|#FFA900|$${\color{#FFA900}SAMPLECOLOR}$$|
|607|255|166|0|#FFA600|$${\color{#FFA600}SAMPLECOLOR}$$|
|608|255|162|0|#FFA200|$${\color{#FFA200}SAMPLECOLOR}$$|
|609|255|159|0|#FF9F00|$${\color{#FF9F00}SAMPLECOLOR}$$|
|610|255|155|0|#FF9B00|$${\color{#FF9B00}SAMPLECOLOR}$$|
|611|255|152|0|#FF9800|$${\color{#FF9800}SAMPLECOLOR}$$|
|612|255|148|0|#FF9400|$${\color{#FF9400}SAMPLECOLOR}$$|
|613|255|145|0|#FF9100|$${\color{#FF9100}SAMPLECOLOR}$$|
|614|255|141|0|#FF8D00|$${\color{#FF8D00}SAMPLECOLOR}$$|
|615|255|137|0|#FF8900|$${\color{#FF8900}SAMPLECOLOR}$$|
|616|255|134|0|#FF8600|$${\color{#FF8600}SAMPLECOLOR}$$|
|617|255|130|0|#FF8200|$${\color{#FF8200}SAMPLECOLOR}$$|
|618|255|126|0|#FF7E00|$${\color{#FF7E00}SAMPLECOLOR}$$|
|619|255|123|0|#FF7B00|$${\color{#FF7B00}SAMPLECOLOR}$$|
|620|255|119|0|#FF7700|$${\color{#FF7700}SAMPLECOLOR}$$|
|621|255|115|0|#FF7300|$${\color{#FF7300}SAMPLECOLOR}$$|
|622|255|111|0|#FF6F00|$${\color{#FF6F00}SAMPLECOLOR}$$|
|623|255|107|0|#FF6B00|$${\color{#FF6B00}SAMPLECOLOR}$$|
|624|255|103|0|#FF6700|$${\color{#FF6700}SAMPLECOLOR}$$|
|625|255|99|0|#FF6300|$${\color{#FF6300}SAMPLECOLOR}$$|
|626|255|95|0|#FF5F00|$${\color{#FF5F00}SAMPLECOLOR}$$|
|627|255|91|0|#FF5B00|$${\color{#FF5B00}SAMPLECOLOR}$$|
|628|255|87|0|#FF5700|$${\color{#FF5700}SAMPLECOLOR}$$|
|629|255|83|0|#FF5300|$${\color{#FF5300}SAMPLECOLOR}$$|
|630|255|79|0|#FF4F00|$${\color{#FF4F00}SAMPLECOLOR}$$|
|631|255|75|0|#FF4B00|$${\color{#FF4B00}SAMPLECOLOR}$$|
|632|255|70|0|#FF4600|$${\color{#FF4600}SAMPLECOLOR}$$|
|633|255|66|0|#FF4200|$${\color{#FF4200}SAMPLECOLOR}$$|
|634|255|62|0|#FF3E00|$${\color{#FF3E00}SAMPLECOLOR}$$|
|635|255|57|0|#FF3900|$${\color{#FF3900}SAMPLECOLOR}$$|
|636|255|52|0|#FF3400|$${\color{#FF3400}SAMPLECOLOR}$$|
|637|255|48|0|#FF3000|$${\color{#FF3000}SAMPLECOLOR}$$|
|638|255|43|0|#FF2B00|$${\color{#FF2B00}SAMPLECOLOR}$$|
|639|255|38|0|#FF2600|$${\color{#FF2600}SAMPLECOLOR}$$|
|640|255|33|0|#FF2100|$${\color{#FF2100}SAMPLECOLOR}$$|
|641|255|27|0|#FF1B00|$${\color{#FF1B00}SAMPLECOLOR}$$|
|642|255|22|0|#FF1600|$${\color{#FF1600}SAMPLECOLOR}$$|
|643|255|16|0|#FF1000|$${\color{#FF1000}SAMPLECOLOR}$$|
|644|255|9|0|#FF0900|$${\color{#FF0900}SAMPLECOLOR}$$|
|645|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|646|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|647|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|648|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|649|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|650|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|651|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|652|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|653|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|654|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|655|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|656|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|657|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|658|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|659|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|660|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|661|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|662|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|663|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|664|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|665|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|666|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|667|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|668|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|669|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|670|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|671|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|672|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|673|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|674|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|675|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|676|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|677|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|678|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|679|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|680|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|681|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|682|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|683|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|684|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|685|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|686|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|687|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|688|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|689|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|690|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|691|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|692|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|693|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|694|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|695|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|696|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|697|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|698|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|699|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|700|255|0|0|#FF0000|$${\color{#FF0000}SAMPLECOLOR}$$|
|701|253|0|0|#FD0000|$${\color{#FD0000}SAMPLECOLOR}$$|
|702|251|0|0|#FB0000|$${\color{#FB0000}SAMPLECOLOR}$$|
|703|250|0|0|#FA0000|$${\color{#FA0000}SAMPLECOLOR}$$|
|704|248|0|0|#F80000|$${\color{#F80000}SAMPLECOLOR}$$|
|705|246|0|0|#F60000|$${\color{#F60000}SAMPLECOLOR}$$|
|706|244|0|0|#F40000|$${\color{#F40000}SAMPLECOLOR}$$|
|707|242|0|0|#F20000|$${\color{#F20000}SAMPLECOLOR}$$|
|708|241|0|0|#F10000|$${\color{#F10000}SAMPLECOLOR}$$|
|709|239|0|0|#EF0000|$${\color{#EF0000}SAMPLECOLOR}$$|
|710|237|0|0|#ED0000|$${\color{#ED0000}SAMPLECOLOR}$$|
|711|235|0|0|#EB0000|$${\color{#EB0000}SAMPLECOLOR}$$|
|712|233|0|0|#E90000|$${\color{#E90000}SAMPLECOLOR}$$|
|713|232|0|0|#E80000|$${\color{#E80000}SAMPLECOLOR}$$|
|714|230|0|0|#E60000|$${\color{#E60000}SAMPLECOLOR}$$|
|715|228|0|0|#E40000|$${\color{#E40000}SAMPLECOLOR}$$|
|716|226|0|0|#E20000|$${\color{#E20000}SAMPLECOLOR}$$|
|717|224|0|0|#E00000|$${\color{#E00000}SAMPLECOLOR}$$|
|718|222|0|0|#DE0000|$${\color{#DE0000}SAMPLECOLOR}$$|
|719|220|0|0|#DC0000|$${\color{#DC0000}SAMPLECOLOR}$$|
|720|219|0|0|#DB0000|$${\color{#DB0000}SAMPLECOLOR}$$|
|721|217|0|0|#D90000|$${\color{#D90000}SAMPLECOLOR}$$|
|722|215|0|0|#D70000|$${\color{#D70000}SAMPLECOLOR}$$|
|723|213|0|0|#D50000|$${\color{#D50000}SAMPLECOLOR}$$|
|724|211|0|0|#D30000|$${\color{#D30000}SAMPLECOLOR}$$|
|725|209|0|0|#D10000|$${\color{#D10000}SAMPLECOLOR}$$|
|726|207|0|0|#CF0000|$${\color{#CF0000}SAMPLECOLOR}$$|
|727|206|0|0|#CE0000|$${\color{#CE0000}SAMPLECOLOR}$$|
|728|204|0|0|#CC0000|$${\color{#CC0000}SAMPLECOLOR}$$|
|729|202|0|0|#CA0000|$${\color{#CA0000}SAMPLECOLOR}$$|
|730|200|0|0|#C80000|$${\color{#C80000}SAMPLECOLOR}$$|
|731|198|0|0|#C60000|$${\color{#C60000}SAMPLECOLOR}$$|
|732|196|0|0|#C40000|$${\color{#C40000}SAMPLECOLOR}$$|
|733|194|0|0|#C20000|$${\color{#C20000}SAMPLECOLOR}$$|
|734|192|0|0|#C00000|$${\color{#C00000}SAMPLECOLOR}$$|
|735|190|0|0|#BE0000|$${\color{#BE0000}SAMPLECOLOR}$$|
|736|188|0|0|#BC0000|$${\color{#BC0000}SAMPLECOLOR}$$|
|737|186|0|0|#BA0000|$${\color{#BA0000}SAMPLECOLOR}$$|
|738|185|0|0|#B90000|$${\color{#B90000}SAMPLECOLOR}$$|
|739|183|0|0|#B70000|$${\color{#B70000}SAMPLECOLOR}$$|
|740|181|0|0|#B50000|$${\color{#B50000}SAMPLECOLOR}$$|
|741|179|0|0|#B30000|$${\color{#B30000}SAMPLECOLOR}$$|
|742|177|0|0|#B10000|$${\color{#B10000}SAMPLECOLOR}$$|
|743|175|0|0|#AF0000|$${\color{#AF0000}SAMPLECOLOR}$$|
|744|173|0|0|#AD0000|$${\color{#AD0000}SAMPLECOLOR}$$|
|745|171|0|0|#AB0000|$${\color{#AB0000}SAMPLECOLOR}$$|
|746|169|0|0|#A90000|$${\color{#A90000}SAMPLECOLOR}$$|
|747|167|0|0|#A70000|$${\color{#A70000}SAMPLECOLOR}$$|
|748|165|0|0|#A50000|$${\color{#A50000}SAMPLECOLOR}$$|
|749|163|0|0|#A30000|$${\color{#A30000}SAMPLECOLOR}$$|
|750|161|0|0|#A10000|$${\color{#A10000}SAMPLECOLOR}$$|
|751|159|0|0|#9F0000|$${\color{#9F0000}SAMPLECOLOR}$$|
|752|157|0|0|#9D0000|$${\color{#9D0000}SAMPLECOLOR}$$|
|753|155|0|0|#9B0000|$${\color{#9B0000}SAMPLECOLOR}$$|
|754|153|0|0|#990000|$${\color{#990000}SAMPLECOLOR}$$|
|755|151|0|0|#970000|$${\color{#970000}SAMPLECOLOR}$$|
|756|149|0|0|#950000|$${\color{#950000}SAMPLECOLOR}$$|
|757|147|0|0|#930000|$${\color{#930000}SAMPLECOLOR}$$|
|758|145|0|0|#910000|$${\color{#910000}SAMPLECOLOR}$$|
|759|143|0|0|#8F0000|$${\color{#8F0000}SAMPLECOLOR}$$|
|760|141|0|0|#8D0000|$${\color{#8D0000}SAMPLECOLOR}$$|
|761|138|0|0|#8A0000|$${\color{#8A0000}SAMPLECOLOR}$$|
|762|136|0|0|#880000|$${\color{#880000}SAMPLECOLOR}$$|
|763|134|0|0|#860000|$${\color{#860000}SAMPLECOLOR}$$|
|764|132|0|0|#840000|$${\color{#840000}SAMPLECOLOR}$$|
|765|130|0|0|#820000|$${\color{#820000}SAMPLECOLOR}$$|
|766|128|0|0|#800000|$${\color{#800000}SAMPLECOLOR}$$|
|767|126|0|0|#7E0000|$${\color{#7E0000}SAMPLECOLOR}$$|
|768|124|0|0|#7C0000|$${\color{#7C0000}SAMPLECOLOR}$$|
|769|122|0|0|#7A0000|$${\color{#7A0000}SAMPLECOLOR}$$|
|770|119|0|0|#770000|$${\color{#770000}SAMPLECOLOR}$$|
|771|117|0|0|#750000|$${\color{#750000}SAMPLECOLOR}$$|
|772|115|0|0|#730000|$${\color{#730000}SAMPLECOLOR}$$|
|773|113|0|0|#710000|$${\color{#710000}SAMPLECOLOR}$$|
|774|111|0|0|#6F0000|$${\color{#6F0000}SAMPLECOLOR}$$|
|775|109|0|0|#6D0000|$${\color{#6D0000}SAMPLECOLOR}$$|
|776|106|0|0|#6A0000|$${\color{#6A0000}SAMPLECOLOR}$$|
|777|104|0|0|#680000|$${\color{#680000}SAMPLECOLOR}$$|
|778|102|0|0|#660000|$${\color{#660000}SAMPLECOLOR}$$|
|779|100|0|0|#640000|$${\color{#640000}SAMPLECOLOR}$$|
|780|97|0|0|#610000|$${\color{#610000}SAMPLECOLOR}$$|

$${\color{#00FF00}Welcome \space \color{lightblue}To \space \color{lightgreen}Github}$$
