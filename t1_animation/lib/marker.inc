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