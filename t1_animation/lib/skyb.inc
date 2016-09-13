
#macro nebulaOne(skyMod)
sphere { < 0, 0, 0>, 2
    pigment { rgbt 1 } // surface of sphere is transparent
    interior {
        media {
            emission 0.02
            intervals 1
            samples 25
            method 3
            density {
                spherical
                ramp_wave
        translate skyMod*y  // replace 1.0 = t   by time for animation
        warp { turbulence 2.5 }
        translate (-skyMod)*y // replace -1.0 = -t  by time for animation
                color_map {
                    [0.0 color rgb <0, 0, 0> * 0.5]
                    [0.1 color rgb <0, 1, 0> * 0.5]
                    [0.5 color rgb <1, 1, 0> * 0.5]
                    [1.0 color rgb <1, 0, 0> * 0.5]
                }
            }
            density {
                spherical
                ramp_wave
                color_map {
                    [0.0 color rgb 1]
                    [0.2 color rgb 1]
                    [0.3 color rgb 0]
                    [1.0 color rgb 0]
                }
            }
        }
    }
    scale 25
    hollow
}
#end
