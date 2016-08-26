
//#declare orbitPoint = pi*clock;
// macros can have parameters and are useful for 'programming' scenes
#macro objTranslation(majorR,minorR,speed,orbitPoint)
        transform { translate <majorR*sin((speed*2)*pi*orbitPoint),0,minorR*cos((speed*2)*pi*orbitPoint)> }
#end

#declare majorR = 2;
#declare minorR = 2;
#declare P1 = vtransform(<0,0,0>,objTranslation(majorR,minorR,1,0));
#declare P2 = vtransform(<0,0,0>,objTranslation(majorR,minorR,1,0.125));
#declare P3 = vtransform(<0,0,0>,objTranslation(majorR,minorR,1,0.250));
#declare P4 = vtransform(<0,0,0>,objTranslation(majorR,minorR,1,0.375));
#declare P5 = vtransform(<0,0,0>,objTranslation(majorR,minorR,1,0.5));
#declare P6 = vtransform(<0,0,0>,objTranslation(majorR,minorR,1,0.625));
#declare P7 = vtransform(<0,0,0>,objTranslation(majorR,minorR,1,0.75));
#declare P8 = vtransform(<0,0,0>,objTranslation(majorR,minorR,1,0.875));
//linear_spline   //= Straight lines are connecting the anchor points (This is default).
//quadratic_spline// = Connecting the anchor points by a smooth curve of 2nd order.
//cubic_spline    //= Connecting the anchor points by a more smooth curve of 3rd order.
//natural_spline  //= Connecting the anchor points by a very smooth curve of 3rd order

#declare Spline_1 =
  spline {
    natural_spline
    0.000, P1, // control point
    0.000, P1, // starting point
    0.125, P2,
    0.250, P3,
    0.375, P4,
    0.500, P5,
    0.625, P6,
    0.750, P7,
    0.875, P8,
    1.000, P1, // end point
    1.000, P2  // control point
  }// end of spline ---------------
