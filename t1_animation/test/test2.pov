#include "colors.inc"
camera {
  location <0, 10, -6>
  look_at <0, 0, 0>
}
light_source { <20, 20, -20> color White }
plane {
  y, 0
  pigment { checker color White color Black }
}
#if ( clock <= 1 )
    sphere { <0, 0, 0> , 1
      pigment {
        gradient x
        color_map {
          [0.0 Blue  ]
          [0.5 Blue  ]
          [0.5 White ]
          [1.0 White ]
        }
        scale .25
      }
      rotate <0, 0, -clock*360>
      translate <-pi, 1, 0>
      translate <2*pi*clock, 0, 0>
    }
  #else
    // (if clock is > 1, we're on the second phase)
    // we still want to work with  a value from 0 - 1
    #declare ElseClock = clock - 1;
    sphere { <0, 0, 0> , 1
      pigment {
        gradient x
        color_map {
          [0.0 Blue  ]
          [0.5 Blue  ]
          [0.5 White ]
          [1.0 White ]
        }
        scale .25
      }
      rotate <0, 0, ElseClock*360>
      translate <-2*pi*ElseClock, 0, 0>
      rotate <0, 45, 0>
      translate <pi, 1, 0>
    }
  #end
