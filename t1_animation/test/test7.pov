#include "colors.inc"
#declare lineLength = 50;
#declare lookAtRadius = 0.5;
//#declare moveX = clock  ;
#declare moveX = 0;//sin(2*pi*clock);
#declare moveZ = 0;//cos(2*pi*clock);


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

//--------------------------------------------------------------------------
//---------------------------   scenery objects  ---------------------------
//--------------------------------------------------------------------------
#macro Marker(Position, Color )//----------------------------------------
union{
  sphere  { <0,0,0>, 0.15 
            texture { pigment{ color Color } 
                      finish { ambient 0.1 diffuse 0.85  phong 1}
                    } // end of texture 
            translate Position  
          }  // end of sphere ----------------------------------- 
  cylinder{ <0,-0.0001,0>,<0,Position.y,0>,0.05 
            texture { pigment { color White*1.2}
                     finish  { ambient 0.15 diffuse 0.85 phong 1}
                   } // end of texture
             translate<Position.x,0,Position.z>
          } // end of cylinder

}  // end of union
#end//-----------------------------------------------------------

#declare P1 = <-2.00, 0.20, -2.00>;
#declare P2 = < 1.00, 0.20, -2.00>;
#declare P3 = < 2.00, 0.70, -1.00>;
#declare P4 = < 2.00, 1.20,  2.00>;
#declare P5 = < 0.00, 0.20,  2.00>;
#declare P6 = <-2.00, 3.20,  1.50>;
#declare P7 = <-2.00, 0.70, -1.00>;
#declare P8 = <-2.00, 0.00, -2.00>;
             
// show the Positions
//object{ Marker(P1, Red )}
//object{ Marker(P2, Orange )}
//object{ Marker(P3, Orange )}
//object{ Marker(P4, Orange )}
//object{ Marker(P5, Orange )}
//object{ Marker(P6, Orange )}
//object{ Marker(P7, Orange )}
//object{ Marker(P8, Red )}
 
#declare Spline_1 =
  spline {               

    //linear_spline   //= Straight lines are connecting the anchor points (This is default).
    //quadratic_spline// = Connecting the anchor points by a smooth curve of 2nd order.
    //cubic_spline    //= Connecting the anchor points by a more smooth curve of 3rd order.
    natural_spline  //= Connecting the anchor points by a very smooth curve of 3rd order
   -0.250, P7, // control point
    0.000, P1, // starting point
    0.125, P2,
    0.250, P3,
    0.420, P4,
    0.490, P5,
    0.780, P6,
    0.900, P7,
    1.000, P1, // end point
    1.125, P2  // control point
  }/*/ end of spline ---------------
                              
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
} */// end of union  ----------------------------------------

camera {
        location Spline_1(clock)//<5+moveX, 5, -6>
        look_at <0+moveX, 0, 0+moveZ>
}

   /*
sphere{ <0,0,0>, 0.25
        texture{
                 pigment{ color Blue}
                 finish { diffuse 0.9
                          phong 1}
               } // end of texture
   translate Spline_1(clock) //<--!!
}  // end of sphere -------------

     */
