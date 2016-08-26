
//#declare orbitPoint = pi*clock;
// macros can have parameters and are useful for 'programming' scenes
#macro objTranslation(majorR,minorR,orbitPoint)
        transform { translate <majorR*sin(2*pi*orbitPoint),0,minorR*cos(2*pi*orbitPoint)> }
#end
         
#macro CirclePoints(aR,bR)
    0.000, vtransform(<0,0,0>,objTranslation(aR,bR,0))	, // control point
    0.000, vtransform(<0,0,0>,objTranslation(aR,bR,0))	, // starting point
    0.125, vtransform(<0,0,0>,objTranslation(aR,bR,0.125)),
    0.250, vtransform(<0,0,0>,objTranslation(aR,bR,0.250)),
    0.375, vtransform(<0,0,0>,objTranslation(aR,bR,0.375)),
    0.500, vtransform(<0,0,0>,objTranslation(aR,bR,0.5))	,
    0.625, vtransform(<0,0,0>,objTranslation(aR,bR,0.625)),
    0.750, vtransform(<0,0,0>,objTranslation(aR,bR,0.75))	,
    0.875, vtransform(<0,0,0>,objTranslation(aR,bR,0.875)),
    1.000, vtransform(<0,0,0>,objTranslation(aR,bR,0))	, // end point
    1.000, vtransform(<0,0,0>,objTranslation(aR,bR,0.125))
#end
//linear_spline   //= Straight lines are connecting the anchor points (This is default).
//quadratic_spline// = Connecting the anchor points by a smooth curve of 2nd order.
//cubic_spline    //= Connecting the anchor points by a more smooth curve of 3rd order.
//natural_spline  //= Connecting the anchor points by a very smooth curve of 3rd order

#declare OrbitLine1 =
  spline {
    natural_spline
    CirclePoints(2,2)
  }// end of spline ---------------
