// planets.pov
// -w320 -h240
// -w800 -h600 +a0.3

#include "colors.inc"
#include "textures.inc"
#include "shapes.inc"
#include "metals.inc"
#include "glass.inc"   
#include "woods.inc"    
//#include "transform.inc"
#include "..\marker.inc"

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
    #declare Camera_Z = -5.00 - Zomm_Dist * 0.5*(1-cos(4*pi*(camTime)));
#end

//#declare orbitPoint = pi*clock;
// macros can have parameters and are useful for 'programming' scenes
#macro objTranslation(majorR,minorR,speed,orbitPoint)
        transform { translate <majorR*sin((speed*2)*pi*orbitPoint),0,minorR*cos((speed*2)*pi*orbitPoint)> }
#end

#declare day4 = transform { rotate <0,4*(-clock*360),0>}
#declare day2 = transform { rotate <0,2*(-clock*360),0>}
#declare orbit_1 = objTranslation(10,10,1,clock);
#declare orbit_2 = objTranslation(8,4,2,clock);
#declare orbit_3 = objTranslation(2,2,3,clock);

camera {
    //location <5, Camera_Y,Camera_Z>
    //location <5, 30,-20>
    location <5, 5,-5>
    look_at <0,0,0>//<2*sin((3*2)*orbitPoint),0,2*cos((3*2)*orbitPoint)>
}
 
light_source { <20, 20, -20> color White }
/*/ show the Positions                                                         
object{ Marker(<0,1,0>, Red ) objTranslation(2,2,3,0)}
object{ Marker(<0,1,0>, Red ) objTranslation(2,2,3,0.25)}
object{ Marker(<0,1,0>, Red ) objTranslation(2,2,3,0.5)}
object{ Marker(<0,1,0>, Red ) objTranslation(2,2,3,0.75)}      
*/                    
#declare P1 = vtransform(<0,1,0>,objTranslation(2,2,3,0));
#declare P2 = vtransform(<0,1,0>,objTranslation(2,2,3,0.125)); 
#declare P3 = vtransform(<0,1,0>,objTranslation(2,2,3,0.250)); 
#declare P4 = vtransform(<0,1,0>,objTranslation(2,2,3,0.5)); 
#declare P5 = vtransform(<0,1,0>,objTranslation(2,2,3,0.625));  
#declare P6 = vtransform(<0,1,0>,objTranslation(2,2,3,0.75));  
#declare P7 = vtransform(<0,1,0>,objTranslation(2,2,3,0.875));  
//#declare P8 = vtransform(<0,1,0>,objTranslation(2,2,3,1));  
                         
object{ Marker(P1, White ) }
object{ Marker(P2, Blue ) }
object{ Marker(P3, Green )}
object{ Marker(P4, Black )}
object{ Marker(P5, Yellow )}
object{ Marker(P6, Gray )}
object{ Marker(P7, Orange )}

#declare Spline_1 =
  spline {               

    //linear_spline   //= Straight lines are connecting the anchor points (This is default).
    quadratic_spline// = Connecting the anchor points by a smooth curve of 2nd order.
    //cubic_spline    //= Connecting the anchor points by a more smooth curve of 3rd order.
    //natural_spline  //= Connecting the anchor points by a very smooth curve of 3rd order
    0.000, P1, // control point
    0.000, P1, // starting point
    0.125, P2,
    0.250, P3,
    0.420, P4,
    0.490, P5,
    0.780, P6,
    0.900, P7,
    1.000, P1, // end point
    1.000, P2  // control point
  }// end of spline ---------------
                     
union{
 #declare Nr = 0;     // start
 #declare EndNr = 1; // end
 #while (Nr< EndNr) 

 sphere{ <0,0,0>,0.07
         scale<1,1,1>
     
	 texture{ pigment{color rgb <1-Nr/2,0.75+Nr/4,0>}
	          finish {ambient 0.15 diffuse 0.85 phong 1}
                }
                
         translate Spline_1(Nr) 
       } // end of sphere

 #declare Nr = Nr + 0.0005;  // next Nr
 #end // --------------- end of loop 

rotate<0,0,0> 
translate<0,0,0>
} /// end of union  ----------------------------------------  
 
#declare lineLength = 50;
#declare xLine = cylinder { <0.1,0,0> <1,0,0> 0.05 pigment { color Red} };
#declare yLine = cylinder { <0,0.1,0> <0,1,0> 0.05 pigment { color Blue} };
#declare zLine = cylinder { <0,0,0.1> <0,0,1> 0.05 pigment { color Green} };

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
        sphere { <0,0,0>,1 }
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

#declare Planets =
union {
   object { Planet_1 transform day2 transform orbit_1 }
   object { Planet_2 transform orbit_2 }
   object { Planet_3 transform day4 transform orbit_3 }
}

union {
    object { Planets }
}
