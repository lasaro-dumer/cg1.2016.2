// macros can have parameters and are useful for 'programming' scenes
#macro objTranslation(majorR,minorR,orbitPoint)
  transform { translate <majorR*sin(2*pi*orbitPoint),0,minorR*cos(2*pi*orbitPoint)> }
#end
#macro days(daysPerOrbit)
  { rotate <0,daysPerOrbit*(-clock*360),0> }
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
  }

#declare OrbitLine2 =
  spline {
    natural_spline
    CirclePoints(8,4)
  }

#declare OrbitLine3 =
  spline {
    natural_spline
    CirclePoints(10,10)
  }

#declare aRCam = 1;
#declare bRCam = 1;
#declare CamLine =
  spline {
    natural_spline
    0.0000, vtransform(<0,0,0>,objTranslation(aRCam,bRCam,0))	, // control point
    0.0000, vtransform(<0,0,0>,objTranslation(aRCam,bRCam,0))	, // starting point
    0.01563, vtransform(<0,0,0>,objTranslation(aRCam,bRCam,0.125)),
    0.03125, vtransform(<0,0,0>,objTranslation(aRCam,bRCam,0.250)),
    0.04688, vtransform(<0,0,0>,objTranslation(aRCam,bRCam,0.375)),
    0.06250, vtransform(<0,0,0>,objTranslation(aRCam,bRCam,0.5))	,
    0.07813, vtransform(<0,0,0>,objTranslation(aRCam,bRCam,0.625)),
    0.09375, vtransform(<0,0,0>,objTranslation(aRCam,bRCam,0.75))	,
    0.10938, vtransform(<0,0,0>,objTranslation(aRCam,bRCam,0.875)),
    0.12500, vtransform(<0,0,0>,objTranslation(aRCam,bRCam,0))	, // end point....../// <0,0,1>
    //0.5625, <-0.2,0.2,1>,
    //0.6250, <-0.4,0.4,1>,
    //0.6875, <-0.6,0.6,1>,
    //0.7500, <-0.8,0.8,1>,
    //0.8125, <-1.5,1.5,1>,
    0.5000, <-1.5,1.5,1>,
    //0.8750, <-1.2,1.2,0.8>,
    //0.9375, <-1.4,1.4,0.6>,
    1.0000, <0,0,1>,
    1.0000, <0,0,1>
  }
