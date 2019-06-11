/*  *FILENAME: ANIM.c 
    *PROGRAMMER: Kiselev Igor
    *DATE: 11.06.2019 
    *PURPOSE: project*/
#include "..\DEF.h"

VOID DP3_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < DP3_Anim.NumOfUnits; i++)
  {
    DP3_Anim.Units[i]->Close(DP3_Anim.Units[i], &DP3_Anim);
    free(DP3_Anim.Units[i]);
    DP3_Anim.Units[i] = NULL;
  }
  DP3_Anim.NumOfUnits = 0;
  DP3_RndClose();
}

VOID DP3_AnimRender( VOID )
{
  INT i;

  for (i = 0; i < DP3_Anim.NumOfUnits; i++)
    DP3_Anim.Units[i]->Response(DP3_Anim.Units[i], &DP3_Anim);

  DP3_RndStart();
  for (i = 0; i < DP3_Anim.NumOfUnits; i++)
    DP3_Anim.Units[i]->Render (DP3_Anim.Units[i], &DP3_Anim);
  //DP3_RndEnd();
}

/* End of "ANIM.c" function */