
#ifndef _MATH_H
#define _MATH_H
#include <windows.h>
#include <math.h>

#define PI 3.14159265358979323846
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)


typedef double DBL;

typedef struct
{
  DBL X, Y, Z;
} VEC;



typedef struct 
{
  DBL A[4][4];
}MATR;

#endif
__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC v = {X, Y, Z};

  return v;
} 

__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
}

__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X - V2.X, V1.Y - V2.Y, V1.Z - V2.Z);
}
                                                                    
__inline VEC VecMulNum( VEC V1, DBL N )
{
  return VecSet(N * V1.X, N * V1.Y, N * V1.Z);
}

__inline VEC VecDivNum( VEC V1, DBL N )
{
  return VecSet(V1.X / N, V1.Y / N, V1.Z / N);
}

__inline VEC VecNeg( VEC V )
{
  return VecSet(-V.X, -V.Y, -V.Z);  
}

__inline DBL VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
}

__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  /*
  MATR m;
  
  m.A[0][0] = 1; 
  m.A[0][1] = 1; 
  m.A[0][2] = 1; 

  m.A[1][0] = V1.X;
  m.A[1][1] = V1.Y; 
  m.A[1][2] = V1.Z; 
  
  m.A[2][0] = V2.X; 
  m.A[2][1] = V2.Y;
  m.A[2][2] = V2.Z;
  */
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X);
}

__inline DBL VecLen2( VEC V )
{
  return (V.X * V.X + V.Y * V.Y + V.Z * V.Z);
}

__inline DBL VecLen( VEC V )
{
  return sqrt(V.X * V.X + V.Y * V.Y + V.Z * V.Z);
}

__inline VEC VecMulMatr( VEC V, MATR M )
{
 return VecSet(V.X * M.A[0][0] + V.X * M.A[0][1] + V.X * M.A[0][2] + + V.X * M.A[0][3], V.Y * M.A[1][0] + V.Y * M.A[1][1] + V.Y * M.A[1][2] + + V.Y * M.A[1][3], V.Z * M.A[2][0] + V.Z * M.A[2][1] + V.Z * M.A[2][2] + + V.Z * M.A[2][3]); 
}

__inline VEC PointTransform( VEC V, MATR M )
{
 return VecSet(V.X * M.A[0][0] + V.X * M.A[0][1] + V.X * M.A[0][2] +  V.X * M.A[0][3], V.Y * M.A[1][0] + V.Y * M.A[1][1] + V.Y * M.A[1][2] +  V.Y * M.A[1][3], V.Z * M.A[2][0] + V.Z * M.A[2][1] + V.Z * M.A[2][2] + + V.Z * M.A[2][3]);
}

__inline VEC VectorTransform( VEC V, MATR M )
{
  // это радиус вектор - поэтому это стоит учесть при вводе из файла
 return VecSet(V.X * M.A[0][0] + V.X * M.A[0][1] + V.X * M.A[0][2] + + V.X * M.A[0][3], V.Y * M.A[1][0] + V.Y * M.A[1][1] + V.Y * M.A[1][2] + + V.Y * M.A[1][3], V.Z * M.A[2][0] + V.Z * M.A[2][1] + V.Z * M.A[2][2] + + V.Z * M.A[2][3]);
}

//MATR Q = MatrTranspose(MatrInverse(M));
//N1 = VectorTransform(N, Q);


static MATR UnitMatrix =
/// #define UnitMatrix .... \ ... \ 
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};

__inline MATR SetMatr( DBL A00, DBL A01, DBL A02, DBL A03,
              DBL A10, DBL A11, DBL A12, DBL A13,
              DBL A20, DBL A21, DBL A22, DBL A23,
              DBL A30, DBL A31, DBL A32, DBL A33 )
{
  MATR m;
  
  m.A[0][0] = A00; 
  m.A[0][1] = A01; 
  m.A[0][2] = A02; 
  m.A[0][3] = A03;
  m.A[1][0] = A10;
  m.A[1][1] = A11; 
  m.A[1][2] = A12; 
  m.A[1][3] = A13;
  m.A[2][0] = A20; 
  m.A[2][1] = A21;
  m.A[2][2] = A22;
  m.A[2][3] = A23;
  m.A[3][0] = A30; 
  m.A[3][1] = A31;
  m.A[3][2] = A32;
  m.A[3][3] = A33;

  return m;
}

__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
}

__inline MATR MatrTranslate( VEC T )
{
  MATR m = UnitMatrix;

  m.A[3][0] = T.X;
  m.A[3][1] = T.Y;
  m.A[3][2] = T.Z;
  return m;
}

__inline MATR MatrScale( VEC S )
{
  return SetMatr(S.X, 0, 0, 0, 0, S.Y, 0, 0, 0, 0, S.Z, 0, 0, 0, 0, 1);
}

__inline MATR MatrRotateX( DBL AngleInDegree )
{
  return SetMatr(1, 0, 0, 0,
    0, cos(D2R(AngleInDegree)), sin(D2R(AngleInDegree)), 0,
    0, -sin(D2R(AngleInDegree)), cos(D2R(AngleInDegree)), 0,
    0, 0, 0, 1); 
}

__inline MATR MatrRotateY( DBL AngleInDegree )
{
  return SetMatr(cos(D2R(AngleInDegree)), 0, -sin(D2R(AngleInDegree)), 0,
    0, 1, 0, 0,
    sin(D2R(AngleInDegree)), 0, cos(D2R(AngleInDegree)), 0,
    0, 0, 0, 1);
}
__inline MATR MatrRotateZ( DBL AngleInDegree )
{
  return SetMatr(cos(D2R(AngleInDegree)), sin(D2R(AngleInDegree)), 0, 0,
    -sin(D2R(AngleInDegree)), cos(D2R(AngleInDegree)), 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1);
}

__inline MATR MatrMulMatr( MATR M1, MATR M2 ) 
{
  INT i, j, k;
  MATR r;

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (r.A[i][j] = 0, k = 0; k < 4; k++)
        r.A[i][j] += M1.A[i][k] * M2.A[k][j];
 

    /*r.A[0][0] = M1.A[0][0] * M2.A[0][0] + M1.A[0][0] * M2.A[1][0] + M1.A[0][0] * M2.A[2][0] + M1.A[0][0] * M2.A[3][0];
    r.A[0][1] = M1.A[0][1] * M2.A[0][0] + M1.A[0][1] * M2.A[1][0] + M1.A[0][1] * M2.A[2][0] + M1.A[0][1] * M2.A[3][0];
    r.A[0][2] = M1.A[0][2] * M2.A[0][0] + M1.A[0][2] * M2.A[1][0] + M1.A[0][2] * M2.A[2][0] + M1.A[0][2] * M2.A[3][0];
    r.A[0][3] = M1.A[0][3] * M2.A[0][0] + M1.A[0][3] * M2.A[1][0] + M1.A[0][3] * M2.A[2][0] + M1.A[0][3] * M2.A[3][0];

    r.A[1][0] = M1.A[1][0] * M2.A[0][1] + M1.A[1][0] * M2.A[1][1] + M1.A[1][0] * M2.A[2][1] + M1.A[1][0] * M2.A[3][1];
    r.A[1][1] = M1.A[1][1] * M2.A[0][1] + M1.A[1][1] * M2.A[1][1] + M1.A[1][1] * M2.A[2][1] + M1.A[1][1] * M2.A[3][1];
    r.A[1][2] = M1.A[1][2] * M2.A[0][1] + M1.A[1][2] * M2.A[1][1] + M1.A[1][2] * M2.A[2][1] + M1.A[1][2] * M2.A[3][1];
    r.A[1][3] = M1.A[1][3] * M2.A[0][1] + M1.A[1][3] * M2.A[1][1] + M1.A[1][3] * M2.A[2][1] + M1.A[1][3] * M2.A[3][1];

    r.A[2][0] = M1.A[2][0] * M2.A[0][2] + M1.A[2][0] * M2.A[1][2] + M1.A[2][0] * M2.A[2][2] + M1.A[2][0] * M2.A[3][2];
    r.A[2][1] = M1.A[2][1] * M2.A[0][2] + M1.A[2][1] * M2.A[1][2] + M1.A[2][1] * M2.A[2][2] + M1.A[2][1] * M2.A[3][2];
    r.A[2][2] = M1.A[2][2] * M2.A[0][2] + M1.A[2][2] * M2.A[1][2] + M1.A[2][2] * M2.A[2][2] + M1.A[2][2] * M2.A[3][2];
    r.A[2][3] = M1.A[2][3] * M2.A[0][2] + M1.A[2][3] * M2.A[1][2] + M1.A[2][3] * M2.A[2][2] + M1.A[2][3] * M2.A[3][2];

    r.A[3][0] = M1.A[3][0] * M2.A[0][3] + M1.A[3][0] * M2.A[1][3] + M1.A[3][0] * M2.A[2][3] + M1.A[3][0] * M2.A[3][3];
    r.A[3][1] = M1.A[3][1] * M2.A[0][3] + M1.A[3][1] * M2.A[1][3] + M1.A[3][1] * M2.A[2][3] + M1.A[3][1] * M2.A[3][3];
    r.A[3][2] = M1.A[3][2] * M2.A[0][3] + M1.A[3][2] * M2.A[1][3] + M1.A[3][2] * M2.A[2][3] + M1.A[3][2] * M2.A[3][3];
    r.A[3][3] = M1.A[3][3] * M2.A[0][3] + M1.A[3][3] * M2.A[1][3] + M1.A[3][3] * M2.A[2][3] + M1.A[3][3] * M2.A[3][3];
     */
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

__inline DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13,
                   DBL A21, DBL A22, DBL A23,
                   DBL A31, DBL A32, DBL A33 )
{
  return A11 * A22 * A33 - A11 * A23 * A32 - A12 * A21 * A33 + 
         A12 * A23 * A31 + A13 * A21 * A32 - A13 * A22 * A31;
}


__inline DBL MatrDeterm( MATR M )
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

__inline 
MATR MatrInverse( MATR M )
{
  MATR r;
  DBL det = MatrDeterm(M);

  if (det == 0)
    return UnitMatrix;

  /* строим присоединенную матрицу */ /* build adjoint matrix */
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
    -MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[2][0], M.A[2][1], M.A[2][2],
                   M.A[3][0], M.A[3][1], M.A[3][2]);

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
    MatrDeterm3x3(M.A[0][0], M.A[0][1], M.A[0][2],
                   M.A[1][0], M.A[1][1], M.A[1][2],
                   M.A[2][0], M.A[2][1], M.A[2][2]);



  /* делим на определитель */
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


__inline void Swap1( double *a, double *b )
{
  double tmp = *a;

  *a = *b;
  *b = tmp;
}


