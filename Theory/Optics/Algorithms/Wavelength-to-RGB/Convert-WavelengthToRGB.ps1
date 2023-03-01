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


380..780 | Convert-WavelengthToRgb | Out-GridView