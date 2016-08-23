// planets.pov
// -w320 -h240
// -w800 -h600 +a0.3

#include "colors.inc"
#include "textures.inc"
#include "shapes.inc"
#include "metals.inc"
#include "glass.inc"
#include "woods.inc"

global_settings {max_trace_level 5}

#declare Zoom_Start  = 0.5;
#declare Zomm_Dist = 15;
//clock = 0.6;
#declare camTime = clock-Zoom_Start;
#declare turbMod = cos(pi*clock);
#if (clock < Zoom_Start )
    #declare Camera_Y = 15.00;
    #declare Camera_Z = -5.00;
#else
    #declare Camera_Y = 15.00  + Zomm_Dist * 0.5*(1-cos(4*pi*(camTime)));
    #declare Camera_Z =  -5.00 - Zomm_Dist * 0.5*(1-cos(4*pi*(camTime)));
#end

camera {
    location <0, Camera_Y,Camera_Z>
    look_at <0,0,0>
}

// Uncomment the area lights only if you've got lots of time.
#declare Dist=80.0;
light_source {
    <0, 0, 0>
    color rgb <0.8, 0.4, 0.0>
    fade_distance Dist
    fade_power 2
    looks_like {
        sphere { <0,0,0>,1 }
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
        finish { ambient 1}
        rotate <0, -clock*360,0>
      }
    }
}

sky_sphere {
    pigment {
        gradient y
        color_map {
            [0, 1  color Black color Black]
        }
    }
}

#declare Planet_1 =
sphere { <0,0, 0>, 0.7
    texture {
        pigment{ crackle scale 1.5 turbulence 0.35
            color_map {
                [0.00 color rgb<0,0,0>]
                [0.08 color rgb<0,0,0>]
                [0.32 color rgb<1,0.65,0>]
                [1.00 color rgb<1,1.0,0.5>]
            }
            scale 0.2
       }
    }
}


#declare Planet_2 =
sphere { <0, 0, 0>, 0.45
    texture {
        pigment{ color rgb <1,1,1>}
        normal { marble 1.5 scale 0.5 turbulence turbMod}
    }
}

#declare Planet_3 =
sphere { <0, 0, 0>, 0.5
    texture {
        pigment{ color rgb <0.55,0.45,0.3>}
        normal { granite 1.5  scale 1}
    }
}

/*
// The text: ------------------------
text { ttf "arial.ttf", "Rotation", 0.2 , 0
       texture{ pigment{ color rgb<1,0.65,0>}
                normal { bumps 0.5 scale 0.005}
                finish { diffuse 0.8 specular 1}
              } // end of texture

       scale<1,1.8,1>*0.75
       translate<-1.30 ,0.50, -0.0 >
       //rotate<0,-360*(clock+0.00),0>
       //rotate<0,-15,0>
     } // end of text object --------
*/

#declare day4
    = transform { rotate <0,4*(-clock*360),0>}
#declare day2
    = transform { rotate <0,2*(-clock*360),0>}
#declare orbitPoint = pi*clock;
#declare orbit_1
    = transform { translate <10*sin(2*orbitPoint),0,10*cos(2*orbitPoint)> }
#declare orbit_2
    = transform { translate <8*sin(4*orbitPoint),0,4*cos(4*orbitPoint)> }
#declare orbit_3
    = transform { translate <2*sin(6*orbitPoint),0,2*cos(6*orbitPoint)> }

#declare Planets =
union {
   object { Planet_1 transform day2 transform orbit_1 }
   object { Planet_2 transform orbit_2 }
   object { Planet_3 transform day4 transform orbit_3 }
}

union {
    object { Planets }
}
