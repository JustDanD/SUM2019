
#include <math.h>


#define PI 3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

/* ������� ������������ ��� */
typedef double DBL;
/* ��� ��� ������� � ����������� */


/* ��� ��� ������� - ������ � ��������� */
typedef struct 
{
  DBL A[4][4];
} MATR;

typedef struct 
{
  DBL X, Y, Z;
} VEC;

/* ������� ���������� */

_inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC v = {X, Y, Z};

  return v;
} /* End of 'VecSet' function */

_inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
}

_inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
} 

_inline VEC VecMulNum( VEC V1, DBL N )
{
  return VecSet(V1.X * N, V1.Y * N, V1.Z * N);
}

_inline VEC VecDivNum( VEC V1, DBL N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
}

_inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);
}

/* ��������� ������������ �������� */
_inline DBL VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V1.Y  + V1.Z * V2.Z;
}
/* ��������� ������������ �������� */
/*_inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return {
    {1, 1, 1},
    {V1.X, V1.Y, V1.Z},
    {V2.X, V2.Y, V2.Y}
  };
} */

DBL VecLen2( VEC V )
{
  return V.X * V.X + V.Y * V.Y + V.Z * V.Z;
}
DBL VecLen( VEC V )
{
  return sqrt(VecLen2(V));
}

_inline VEC VecMulMatr( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.X * M.A[0][1] + V.X * M.A[0][2] + + V.X * M.A[0][3], V.Y * M.A[1][0] + V.Y * M.A[1][1] + V.Y * M.A[1][2] + + V.Y * M.A[1][3], V.Z * M.A[2][0] + V.Z * M.A[2][1] + V.Z * M.A[2][2] + + V.Z * M.A[2][3]);
}

/* ��������������: */
VEC PointTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.X * M.A[0][1] + V.X * M.A[0][2] + + V.X * M.A[0][3], V.Y * M.A[1][0] + V.Y * M.A[1][1] + V.Y * M.A[1][2] + + V.Y * M.A[1][3], V.Z * M.A[2][0] + V.Z * M.A[2][1] + V.Z * M.A[2][2] + + V.Z * M.A[2][3]);
}
_inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.X * M.A[0][1] + V.X * M.A[0][2] + + V.X * M.A[0][3], V.Y * M.A[1][0] + V.Y * M.A[1][1] + V.Y * M.A[1][2] + + V.Y * M.A[1][3], V.Z * M.A[2][0] + V.Z * M.A[2][1] + V.Z * M.A[2][2] + + V.Z * M.A[2][3]);
}





/* ��������� ������� */

/*_inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
}

MATR MatrTranslate( VEC T )
{
  MATR m = UnitMatrix;

  m.A[3][0] = T.X;
  m.A[3][1] = T.Y;
  m.A[3][2] = T.Z;
  return m;
} 

MATR MatrScale( VEC S  )
{
    return {
      {S.X, 0, 0, 0},
    {0, S.Y, 0, 0},
      {0, 0, S.Z, 0},
    {0, 0, 0, 1}
  };
} */
/*MATR MatrRotateX( DBL AngleInDegree )
{
  return {
    {1, 0, 0, 0},
    {0, cos(D2R(AngleInDegree)), sin(D2R(AngleInDegree)), 0},
    {0, -sin(D2R(AngleInDegree)), cos(D2R(AngleInDegree)), 0},
    {0, 0, 0, 1}
  };
}
MATR MatrRotateY( DBL AngleInDegree )
{
  return {
    {cos(D2R(AngleInDegree)), 0, -sin(D2R(AngleInDegree)), 0},
    {0, 1, 0, 0},
    {sin(D2R(AngleInDegree)), 0, cos(D2R(AngleInDegree)), 0},
    {0, 0, 0, 1}
  };
}
MATR MatrRotateZ( DBL AngleInDegree )
{
  return {
    {cos(D2R(AngleInDegree)), sin(D2R(AngleInDegree)), 0, 0},
    {-sin(D2R(AngleInDegree)), cos(D2R(AngleInDegree)), 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  };
}*/


_inline MATR MatrMulMatr( MATR M1, MATR M2 ) 
{
  MATR r;
  int i, j, k;
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.A[i][j] = 0, k = 0; k < 4; k++)
        r.A[i][j] += M1.A[i][k] * M2.A[k][j];
  return r;
}
__inline MATR MatrTranspose( MATR M )
{
  MATR M1;

  M1.A[0][0] = M.A[0][0];
  M1.A[0][1] = M.A[1][0];
  M1.A[0][2] = M.A[2][0];
  M1.A[0][3] = M.A[3][0];
  M1.A[1][0] = M.A[0][1];
  M1.A[1][1] = M.A[1][1];
  M1.A[1][2] = M.A[2][1];
  M1.A[1][3] = M.A[3][1];
  M1.A[2][0] = M.A[0][2];
  M1.A[2][1] = M.A[1][2];
  M1.A[2][2] = M.A[2][2];
  M1.A[2][3] = M.A[3][2];
  M1.A[3][0] = M.A[0][3];
  M1.A[3][1] = M.A[1][3];
  M1.A[3][2] = M.A[2][3];
  M1.A[3][3] = M.A[3][3];
  return M1;
}


DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                   DBL A21, DBL A22, DBL A23,
                   DBL A31, DBL A32, DBL A33 )
{
  return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 + 
         A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
}


DBL MatrDeterm( MATR M )
{
  return
    M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                              M.A[2][1], M.A[2][2], M.A[2][3],
                              M.A[3][1], M.A[3][2], M.A[3][3]) +
    -M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                               M.A[2][0], M.A[2][2], M.A[2][3],
                               M.A[3][0], M.A[3][2], M.A[3][3]) +
    M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                              M.A[2][0], M.A[2][1], M.A[2][3],
                              M.A[3][0], M.A[3][1], M.A[3][3]) +
    -M.A[0][3] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                               M.A[2][0], M.A[2][1], M.A[2][2],
                               M.A[3][0], M.A[3][1], M.A[3][2]);
}

MATR MatrInverse( MATR M )
{
  MATR r;
  DBL det = MatrDeterm(M);

  /*if (det == 0)
    return UnitMatrix;
  */
  /* ������ �������������� ������� */ /* build adjoint matrix */
  r.A[0][0] =
    MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                  M.A[2][1], M.A[2][2], M.A[2][3],
                  M.A[3][1], M.A[3][2], M.A[3][3]);
  r.A[1][0] =
    -MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[2][0], M.A[2][2], M.A[2][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]);
  r.A[2][0] =
    MatrDeterm3x3( M.A[1][0], M.A[1][1], M.A[1][3],
                   M.A[2][0], M.A[2][1], M.A[2][3],
                   M.A[3][0], M.A[3][1], M.A[3][3]);
  r.A[3][0] =
    -MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][0],
                   M.A[2][0], M.A[2][1], M.A[2][0],
                   M.A[3][0], M.A[3][1], M.A[3][0]);

  r.A[0][1] =
    -MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                  M.A[2][1], M.A[2][2], M.A[2][3],
                  M.A[3][1], M.A[3][2], M.A[3][3]);
  r.A[1][1] =
    MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[2][0], M.A[2][2], M.A[2][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]);
  r.A[2][1] =
    -MatrDeterm3x3( M.A[0][0], M.A[0][1], M.A[0][3],
                   M.A[2][0], M.A[2][1], M.A[2][3],
                   M.A[3][0], M.A[3][1], M.A[3][3]);
  r.A[3][1] =
    MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[2][0], M.A[2][1], M.A[2][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]);
  
  r.A[0][2] =
    MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                  M.A[1][1], M.A[1][2], M.A[1][3],
                  M.A[3][1], M.A[3][2], M.A[3][3]);
  r.A[1][2] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[3][0], M.A[3][2], M.A[3][3]);
  r.A[2][2] =
    MatrDeterm3x3( M.A[0][0], M.A[0][1], M.A[0][3],
                   M.A[1][0], M.A[1][1], M.A[1][3],
                   M.A[3][0], M.A[3][1], M.A[3][3]);
  r.A[3][2] =
    -MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]);
  r.A[0][3] =
    -MatrDeterm3x3(M.A[0][1], M.A[0][2], M.A[0][3],
                  M.A[1][1], M.A[1][2], M.A[1][3],
                  M.A[2][1], M.A[2][2], M.A[2][3]);
  r.A[1][3] =
    MatrDeterm3x3(M.A[0][0], M.A[0][2], M.A[0][3],
                   M.A[1][0], M.A[1][2], M.A[1][3],
                   M.A[2][0], M.A[2][2], M.A[2][3]);
  r.A[2][3] =
    -MatrDeterm3x3( M.A[0][0], M.A[0][1], M.A[0][3],
                   M.A[2][0], M.A[2][1], M.A[2][3],
                   M.A[3][0], M.A[3][1], M.A[3][3]);
  r.A[3][3] =
    MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][0],
                   M.A[2][0], M.A[2][1], M.A[2][0],
                   M.A[3][0], M.A[3][1], M.A[3][0]);



  /* ����� �� ������������ */
  r.A[1][0] /= det;
  r.A[2][0] /= det;
  r.A[3][0] /= det;
  r.A[1][1] /= det;
  r.A[2][1] /= det;
  r.A[3][1] /= det;
  r.A[1][2] /= det;
  r.A[2][2] /= det;
  r.A[3][2] /= det;
  r.A[1][3] /= det;
  r.A[2][3] /= det;
  r.A[3][3] /= det;
  r.A[0][0] /= det;
  r.A[0][1] /= det;
  r.A[0][2] /= det;
  r.A[0][3] /= det;
  return r;
}

/* �������� (�������)
void main( void )
{
  MATR m =
  {
    {1, 1, 1, 0},
    {1, 1, 2, 0},
    {1, 2, 1, 1},
    {2, 1, 1, 1}
  }, m1, m2;

  m1 = MatrInverse(m);
  m2 = MatrMulMatr(m, m1);
  m2 = MatrMulMatr(m1, m);

  m = MatrRotate(90, 0, 1, 0);
  m1 = MatrInverse(m);
}
*/

