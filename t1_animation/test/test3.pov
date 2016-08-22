#include "colors.inc"
 #include "textures.inc"
 background { rgb<0.8, 0.8, 0.8> }
 camera {
   location <1.5, 1, -30>
   look_at <0, 1, 0>
   angle 10
 }
 light_source { <-100, 20, -100> color White }
 // flag
 polygon {
   5, <0, 0>, <0, 1>, <1, 1>, <1, 0>, <0, 0>
   pigment { Blue }
   normal {
     gradient x
     phase clock
     scale <0.2, 1, 1>
     sine_wave
   }
   scale <3, 2, 1>
   translate <-1.5, 0, 0>
 }
 // flagpole
 cylinder {
   <-1.5, -4, 0>, <-1.5, 2.25, 0>, 0.05
   texture { Silver_Metal }
 }
 // polecap
 sphere {
   <-1.5, 2.25, 0>, 0.1
   texture { Silver_Metal }
 }
