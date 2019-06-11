

typedef struct tagUNIT UNIT;
struct tagUNIT
{
  VOID (*Init)( UNIT *Uni, ANIM *Ani );
  VOID (*Close)( UNIT *Uni, ANIM *Ani );
  VOID (*Response)( UNIT *Uni, ANIM *Ani );
  VOID (*Render)( UNIT *Uni, ANIM *Ani );
};