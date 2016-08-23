#include "colors.inc"              
#declare lineLength = 50;
#declare lookAtRadius = 0.5;  
//#declare moveX = clock  ;      
#declare moveX = sin(2*pi*clock);
#declare moveZ = cos(2*pi*clock);
//#declare mainCamera = 
camera {
        location <5+moveX, 5, -6>
        look_at <0+moveX, 0, 0+moveZ>
}

light_source { <20, 20, -20> color White }
plane {
        y, 0
        pigment { checker color White color Black }
}                     

#declare xLine = cylinder { <0,0,0> <1,0,0> 0.05 pigment { color Red} };
#declare yLine = cylinder { <0,0,0> <0,1,0> 0.05 pigment { color Blue} };
#declare zLine = cylinder { <0,0,0> <0,0,1> 0.05 pigment { color Green} };
                                              
object { xLine transform { scale <lineLength,0,0> } }
object { yLine transform { scale <0,lineLength,0> } }
object { zLine transform { scale <0,0,lineLength> } }      

// create a sphere shape
sphere { <0, 0, 0>  lookAtRadius
  // scale <1,2,1> // <= Note: Spheres can become ellipses by uneven scaling
        texture {
                pigment { color Yellow }
                normal { bumps 0.5 scale 0.1 }
                finish { phong 1 }
                rotate <0,-clock*360,0>
        }          
        translate <0,lookAtRadius,0>       
        translate <moveX,0,0+moveZ>
}              