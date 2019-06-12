/*  *FILENAME: UNITS.c 
    *PROGRAMMER: Pimenov Danila
    *DATE: 11.06.2019 
    *PURPOSE: project*/
#include <windows.h>

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "Z:/SUM2019/T08ANIM/DEF.H"
#include "ANIM.h"


static VOID DP3_UnitInit( dp3UNIT *Uni, dp3ANIM *Ani )
{
} /* End of 'DP3_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       DP3_UNIT *Uni;
 *   - animation context:
 *       DP3_ANIM *Ani;
 * RETURNS: None.
 */
static VOID DP3_UnitClose( dp3UNIT *Uni, dp3ANIM *Ani )
{
} /* End of 'DP3_UnitClose' function */
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       DP3_UNIT *Uni;
 *   - animation context:
 *       DP3_ANIM *Ani;
 * RETURNS: None.
 */
static VOID DP3_UnitResponse( dp3UNIT *Uni, dp3ANIM *Ani )
{
} /* End of 'DP3_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       DP3_UNIT *Uni;
 *   - animation context:
 *       DP3_ANIM *Ani;
 * RETURNS: None.
 */
static VOID DP3_UnitRender( dp3UNIT *Uni, dp3ANIM *Ani )
{
} /* End of 'DP3_UnitRender' function */



/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (DP3_UNIT *) pointer to created unit.
 */
dp3UNIT * DP3_AnimUnitCreate( VOID )
{
  dp3UNIT *Uni;

  /* Memory allocation */
  if (sizeof(dp3UNIT) < sizeof(dp3UNIT) || (Uni = malloc(sizeof(dp3UNIT))) == NULL)
    return NULL;
  memset(Uni, 0, sizeof(dp3UNIT));

  /* Setup unit methods */
  Uni->Init = DP3_UnitInit;
  Uni->Close = DP3_UnitClose;
  Uni->Response = DP3_UnitResponse;
  Uni->Render = DP3_UnitRender;
  return Uni;
}