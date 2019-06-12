/*  *FILENAME: ANIM.h 
    *PROGRAMMER: Pimenov Danila
    *DATE: 11.06.2019 
    *PURPOSE: project*/

#include "Z:/SUM2019/T08ANIM/DEF.H"
#include "../ANIM/ANIM.h"
#include "../ANIM/RND/RND.H"
#include "../ANIM/TIMER.H"
typedef struct 
{
  UNIT_BASE;
  dp3PRIM cow;
} dp3UNIT_COW;


static VOID DP3_UnitInit( dp3UNIT_COW *Uni, dp3ANIM *Ani )
{
  DP3_RndPrimLoad(&Uni->cow, "cow.object");
} /* End of 'DP3_UnitInit' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       DP3_UNIT *Uni;
 *   - animation context:
 *       dp3ANIM *Ani;
 * RETURNS: None.
 */
static VOID DP3_UnitClose( dp3UNIT_COW *Uni, dp3ANIM *Ani )
{
  DP3_RndPrimFree(&Uni->cow);
} /* End of 'DP3_UnitClose' function */
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       DP3_UNIT *Uni;
 *   - animation context:
 *       dp3ANIM *Ani;
 * RETURNS: None.
 */
static VOID DP3_UnitResponse( dp3UNIT_COW *Uni, dp3ANIM *Ani )
{
  //Uni->cow.Trans = MatrMulMatr(Uni->cow.Trans, MatrScale(VecSet(0.8, 0.8, 0.8)));
  Uni->cow.Trans = MatrMulMatr(Uni->cow.Trans, MatrRotateY(20 * DP3_ANIM.Time));
} /* End of 'DP3_UnitResponse' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       DP3_UNIT *Uni;
 *   - animation context:
 *       dp3ANIM *Ani;
 * RETURNS: None.
 */
static VOID DP3_UnitRender( dp3UNIT_COW *Uni, dp3ANIM *Ani )
{
  TimerResponse();
  DP3_InputRespons();
  DP3_RndCamSet(VecSet(0, 6, 100), VecSet(0, 0, 0), VecSet(0, 1, 0) );
  DP3_RndPrimDraw(&Uni->cow, MatrTranslate(VecSet(20 * DP3_ANIM.JX, 0, 0)));
} /* End of 'DP3_UnitRender' function */


/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (DP3_UNIT *) pointer to created unit.
 */
dp3UNIT * DP3_ANIMUnitCowCreate( VOID )
{
  dp3UNIT *Uni;

  /* Memory allocation */
  if (sizeof(dp3UNIT_COW) < sizeof(dp3UNIT) || (Uni = malloc(sizeof(dp3UNIT_COW))) == NULL)
    return NULL;
  memset(Uni, 0, sizeof(dp3UNIT_COW));

  /* Setup unit methods */
  Uni->Init = DP3_UnitInit;
  Uni->Close = DP3_UnitClose;
  Uni->Response = DP3_UnitResponse;
  Uni->Render = DP3_UnitRender;
  return Uni;
} /* End of 'dp3ANIMUnitCreate' function */
