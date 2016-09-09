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

#macro DrawSPLine(SPLineObj)//----------------------------------------
union{
    #declare Nr = 0;     // start
    #declare EndNr = 1; // end
    #while (Nr< EndNr)
        sphere{ <0,0,0>,0.01
            scale<1,1,1>
            texture{ pigment{color rgb <1-Nr/2,0.75+Nr/4,0>}
                finish {ambient 0.15 diffuse 0.85 phong 1}
            }
            translate SPLineObj(Nr)
        } // end of sphere
        #declare Nr = Nr + 0.0005;  // next Nr
    #end // --------------- end of loop
    rotate<0,0,0>
    translate<0,0,0>
} /// end of union  ----------------------------------------
#end//-----------------------------------------------------------

#macro Tracker(Position, Color )//----------------------------------------
union{
  sphere  { <0,0,0>, 0.15
            texture { pigment{ color Color }
                      finish { ambient 0.1 diffuse 0.85  phong 1}
                    } // end of texture
            translate Position
          }  // end of sphere -----------------------------------
}  // end of union
#end//-----------------------------------------------------------
