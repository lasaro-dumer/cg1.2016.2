#include "colors.inc"
#declare turbMod = cos(pi*clock);



  camera {
    location <5, 5, -6>
    look_at <0, 0, 0>
  }
  light_source { <20, 20, -20> color White }
  plane {
    y, 0
    pigment { checker color White color Black }
  }
  sphere {
    <0, 0, 0> , 1
    texture {
      pigment { color Yellow }
      normal { bumps 0.4 scale 0.2 }
      finish { phong 1 }
      rotate <0, -clock*360,0>
    }
    rotate <0, -clock*360,0>
    translate <-pi, 1, 0>
    //translate <sin(2*pi*clock), 0,cos(2*pi*clock)>
    //translate <1+clock, 0,0>
  }

  sphere {
    <0, 0, 0> , 1
    texture {
      pigment {
        wood
        color_map {
          [0.0 color Red]
          [0.5 color Red]
          [0.5 color Blue]
          [1.0 color Blue]
        }
        scale <0.2, 0.3, 1>
      }
      finish { phong 1 }
      rotate <0, -clock*360,0>
    }
    rotate <0, -clock*360,0>
    translate <0, 1, 0>
    //translate <sin(2*pi*clock), 0,cos(2*pi*clock)>
    //translate <1+clock, 0,0>
  }

    sphere {
      <0, 0, 0> , 1
      texture {
        pigment {
           gradient y
           colour_map {
              [0.00, Red]   
              [0.10, Yellow] 
              [0.20, Red]   
              [0.30, Yellow]
              [0.40, Red]   
              [0.50, Yellow]
              [0.60, Red]   
              [0.70, Yellow]
              [0.80, Red]   
              [0.90, Yellow]
              [1.00, Red]   
           }
          turbulence turbMod
          scale <1, 1, 1>
        }        
        normal { bumps 0.4 scale 0.2 }
        finish { phong 1 }
        rotate <0, -clock*360,0>
      }
      rotate <0, -clock*360,0>
      translate <pi, 1, 0>
      //translate <sin(2*pi*clock), 0,cos(2*pi*clock)>
      //translate <1+clock, 0,0>
    }
       /*  
    sphere {
      <0, 0, 0> , 1
      texture {
        pigment{ wrinkles scale 0.20
         color_map{[0.0 color rgb <1,0,0.3>]
                   [1.0 color rgb <1,1,1>]
                  }//end of color_map
         turbulence turbMod
        } // end of pigment
        //rotate <0, -clock*360,0>
      }
      //rotate <0, -clock*360,0>
      translate <pi, 1, -pi>
      //translate <sin(2*pi*clock), 0,cos(2*pi*clock)>
      //translate <1+clock, 0,0>
    }*/