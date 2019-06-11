/*  *FILENAME: UNITS.c 
    *PROGRAMMER: Kiselev Igor
    *DATE: 11.06.2019 
    *PURPOSE: project*/
#include "../DEF.h"


/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       DP3_UNIT *Uni;
 *   - animation context:
 *       DP3_ANIM *Ani;
 * RETURNS: None.
 */
static VOID DP3_UnitInit( DP3_UNIT *Uni, DP3_ANIM *Ani )
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
static VOID DP3_UnitClose( DP3_UNIT *Uni, DP3_ANIM *Ani )
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
static VOID DP3_UnitResponse( DP3_UNIT *Uni, DP3_ANIM *Ani )
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
static VOID DP3_UnitRender( DP3_UNIT *Uni, DP3_ANIM *Ani )
{
} /* End of 'DP3_UnitRender' function */


/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (DP3_UNIT *) pointer to created unit.
 */
DP3_UNIT * DP3_AnimUnitCreate( INT Size )
{
  DP3_UNIT *Uni;

  /* Memory allocation */
  if (Size < sizeof(DP3_UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
  memset(Uni, 0, Size);

  /* Setup unit methods */
  Uni->Init = DP3_UnitInit;
  Uni->Close = DP3_UnitClose;
  Uni->Response = DP3_UnitResponse;
  Uni->Render = DP3_UnitRender;
  return Uni;
} /* End of 'DP3_AnimUnitCreate' function */



/*   Тут живёт странный и непонятный кусок функции
static VOID DP3_UnitInit( DP3UNIT_BALL *Uni, DP3ANIM *Ani )
{
  Uni->Pos = VecSet(0, 1, 0);
} 
static VOID DP3_UnitResponse( DP3UNIT_BALL *Uni, DP3ANIM *Ani );
{
  Uni->Pos += Ani->DeltaTime * 2.4;
}  */


/* End of "UNITS.c" function */