// planets.pov
// -w320 -h240
// -w800 -h600
// -w1024 -h768
// -w1400 -h1050

#include "colors.inc"
#include "textures.inc"
#include "shapes.inc"
#include "metals.inc"
#include "glass.inc"
#include "woods.inc"
#include "marker.inc"
#include "orbits.inc"

global_settings {max_trace_level 5}

#declare Zoom_Start  = 0.5;
#declare Zomm_Dist = 15;
#declare camTime = clock-Zoom_Start;
#declare turbMod = abs(cos(pi*clock));
#if (clock < Zoom_Start )
    #declare Camera_Y = 15.00;
    #declare Camera_Z = -5.00;
#else
    #declare Camera_Y = 15.00  + Zomm_Dist * 0.5*(1-cos(4*pi*(camTime)));
    #declare Camera_Z = -5.00 - Zomm_Dist * 0.5*(1-cos(4*pi*(camTime)));
#end

#if (clock <= 0.125)
    #declare camPos = CamLine(clamp(clock,0,0.125));
    //object{ Tracker(camPos, Red )  }
    ////object{ Tracker(CamLine(clock*4), Red )  }
#else
    #declare camPos = CamLine(clock);
    //object{ Tracker(camPos, Blue )  }
#end
camera {
    //location <5, Camera_Y,Camera_Z>
    //location <5, 30,-20>

    //location <5, 5,-5>
    //look_at <0,0,0>//<2*sin((3*2)*orbitPoint),0,2*cos((3*2)*orbitPoint)>

    location camPos
    look_at OrbitLine1(clamp(clock*8, 0, 1))
}

light_source { <20, 20, -20> color White }
/*/ show the Positions
object{ Marker(<0,1,0>, Red ) objTranslation(2,2,3,0)}
object{ Marker(<0,1,0>, Red ) objTranslation(2,2,3,0.25)}
object{ Marker(<0,1,0>, Red ) objTranslation(2,2,3,0.5)}
object{ Marker(<0,1,0>, Red ) objTranslation(2,2,3,0.75)}
*/
object{ DrawSPLine(OrbitLine1) }
object{ DrawSPLine(OrbitLine2) }
object{ DrawSPLine(OrbitLine3) }
//object{ DrawSPLine(CamLine) }

#declare lineLength = 50;
#declare xLine = cylinder { <0.01,0,0> <1,0,0> 0.01 pigment { color Red} };
#declare yLine = cylinder { <0,0.01,0> <0,1,0> 0.01 pigment { color Blue} };
#declare zLine = cylinder { <0,0,0.01> <0,0,1> 0.01 pigment { color Green} };

//object { xLine transform { scale <lineLength,0,0> } }
//object { yLine transform { scale <0,lineLength,0> } }
//object { zLine transform { scale <0,0,lineLength> } }

// Uncomment the area lights only if you've got lots of time.
#declare Dist=80.0;
light_source {
    <0, 0, 0>
    color rgb <0.8, 0.4, 0.0>
    fade_distance Dist
    fade_power 2
    looks_like {
        sphere { <0,0,0>,0.85 }
        texture {
        pigment {
           gradient y
           colour_map { [0.00, Red] [0.10, Yellow] [0.20, Red] [0.30, Yellow] [0.40, Red] [0.50, Yellow] [0.60, Red] [0.70, Yellow] [0.80, Red] [0.90, Yellow] [1.00, Red] }
          turbulence turbMod
          scale <1, 1, 1>
        }
        normal { bumps 0.4 scale 0.2 }
        finish { ambient 1}
        rotate <0, -clock*360,0>
      }
    }
} /*
#include "stars.inc"
sphere{ <0,0,0>, 1
        texture{ Starfield1 scale 0.5 }
        scale 10000
      } //end of sphere ---------------
*/
sky_sphere {
    pigment {
        gradient y
        color_map {
            [0, 1  color Black color Black]
        }
    }
}
// An infinite planar surface
// plane {<A, B, C>, D } where: A*x + B*y + C*z = D
plane {
  y, // <X Y Z> unit surface normal, vector points "away from surface"
  -5.0 // distance from the origin in the direction of the surface normal
  pigment {color rgb <0.5,0.5,0.5>}
}
//*/
#declare Planet_1 =
sphere { <0, 0, 0>, 0.5
  texture {
    pigment{ color rgb <0.55,0.45,0.3>}
    normal { granite 1.5  scale 1}
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

#declare Planets =
union {
    object { Planet_1 transform days(1) translate OrbitLine1(clamp(clock*8, 0, 1)) }
    object { Planet_2 transform days(1) translate OrbitLine2(clamp(clock*4, 0, 1)) }
    object { Planet_3 transform days(1) translate OrbitLine3(clamp(clock*2, 0, 1)) }
}

union {
    object { Planets }
}
