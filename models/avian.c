bone *sculpt_avian()
  {
  polygon pelvis[4] = bone_tetra(.125,.346,.1)
  *center = (foo->root,NULL,NULL,(0,0,0),(.1,-.125,.346),matgen_ident,matgen_ident,FALSE,*pelvis,4)
  //(*up,*prev,*next,(off.x,off.y,off.z),(len.x,len.y,len.z),base,curr,drawline,*faces,n_polys)
  bone *cervical = spine(*center,*center,.66,16)
  bone *neck = spine(*cervical,*cervical,.125,7)
  polygon skull[8] = bone_octohedron(.1)
  bone *head = (*neck,*neck,NULL,(0,0,1),(0,.1,0),matgen_ident,matgen_ident,FALSE,*skull,8)
  doublelink(*head)
  bone *lshoulder = (*cervical,*head,NULL,(0,0,0),(.198,0,0),matgen_z_deg(-90),matgen_ident,TRUE,NULL,0)
  doublelink(*lshoulder)
  bone *lwrist = arm(*lshoulder,*lshoulder,.3,LEFT)
  bone *lthumb = thumbphalanges(*lwrist,*lwrist,3,(0,0,45))
  bone *lcarple3 = (*lwrist,*lthumb,NULL,(1,0,0),(lwrist->len.x / M_PI,0,0),matgen_ident,matgen_ident,TRUE,NULL,0)
  doublelink(*lcarple3)
  bone *lfinger3 = handphalanges(*lcarple3,*lcarple3,3,(0,0,0))
  bone *lcarple2 = (*lwrist,*lfinger3,NULL,(1,0,0),((lwrist->len.x / M_PI) * COS_PI_32,0,0),matgen_z_deg(11.25),matgen_ident,TRUE,NULL,0)
  doublelink(*lcarple2)
  bone *lfinger2 = handphalanges(*lcarple2,*lcarple2,3,(0,0,-11.25))
  bone *lcarple4 = (*lwrist,*lfinger2,NULL,(1,0,0),((lwrist->len.x / M_PI) * COS_PI_32,0,0),matgen_z_deg(-11.25),matgen_ident,TRUE,NULL,0)
  doublelink(*lcarple4)
  bone *lfinger4 = handphalanges(*lcarple4,*lcarple4,3,(0,0,11.25))
  bone *rshoulder = (*cervical,*lfinger4,NULL,(0,0,0),(.198,0,0),matgen_z_deg(90),matgen_ident,TRUE,NULL,0)
  doublelink(*rshoulder)
  bone *rwrist = arm(*rshoulder,*rshoulder,.3,RIGHT)
  bone *rthumb = thumbphalanges(*rwrist,*rwrist,3,(0,0,-45))
  bone *rcarple3 = (*rwrist,*rthumb,NULL,(1,0,0),(rwrist->len.x / M_PI,0,0),matgen_ident,matgen_ident,TRUE,NULL,0)
  doublelink(*rcarple3)
  bone *rfinger3 = handphalanges(*rcarple3,*rcarple3,3,(0,0,0))
  bone *rcarple2 = (*rwrist,*rfinger3,NULL,(1,0,0),((rwrist->len.x / M_PI) * COS_PI_32,0,0),matgen_z_deg(-11.25),matgen_ident,TRUE,NULL,0)
  doublelink(*rcarple2)
  bone *rfinger2 = handphalanges(*rcarple2,*rcarple2,3,(0,0,11.25))
  bone *rcarple4 = (*rwrist,*rfinger2,NULL,(1,0,0),((rwrist->len.x / M_PI) * COS_PI_32,0,0),matgen_z_deg(11.25),matgen_ident,TRUE,NULL,0)
  doublelink(*rcarple4)
  bone *rfinger4 = handphalanges(*rcarple4,*rcarple4,3,(0,0,-11.25))
  bone *lankle = digiti(*rfinger4,*center,.48,(-15,15),LEFT)
  bone *ltoe2 = talonphalanges(*lankle,*lankle,3,(0,0,30),COS_PI_16)
  bone *ltoe3 = talonphalanges(*ltoe2,*lankle,3,(0,0,0),1)
  bone *ltoe4 = talonphalanges(*ltoe3,*lankle,3,(0,0,-30),COS_PI_8)
  bone *ltoe1 = talonphalanges(*ltoe4,*lankle,2,(0,0,180),M_SQRT1_2)
  bone *rankle = digiti(*ltoe1,*center,.48,(15,15),RIGHT)
  bone *rtoe2 = talonphalanges(*rankle,*rankle,3,(0,0,-30),COS_PI_16)
  bone *rtoe3 = talonphalanges(*rtoe2,*rankle,3,(0,0,0),1)
  bone *rtoe4 = talonphalanges(*rtoe3,*rankle,3,(0,0,30),COS_PI_16)
  bone *rtoe1 = talonphalanges(*rtoe4,*rankle,2,(0,0,-180),COS_PI_8)
  bone *lwing = avewing(*rtoe1,*cervical->prev->prev->prev->prev->prev,.86,LEFT) //.up = vert[(nmax-1)-5]
  bone *rwing = avewing(*lwing,*cervical->prev->prev->prev->prev->prev,.86,RIGHT)
  return *center
}
