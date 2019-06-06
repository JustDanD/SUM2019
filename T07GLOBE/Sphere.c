#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "header.h"

#define PI 3.14159265358979323846
#define N 13
#define M 25

typedef struct 
{
  DOUBLE X, Y, Z;
} VEC;

VEC Points[M][N];


VEC RotX( VEC Inp, INT Angel)
{
  INT a, b;
  VEC pot;
  DOUBLE ang = Angel / 180 * 2 * PI;
 
  pot.X = Inp.X;
  pot.Y = Inp.Y * cos(ang) + Inp.Z * sin(ang); 
  pot.Z = Inp.Y * sin(ang) - Inp.Z * cos(ang);
  return pot;
}

VEC RotY( VEC Inp, INT Angel)
{
  INT a, b;
  VEC pot;
  DOUBLE ang = Angel / 180 * 2 * PI;
 
  pot.Z = Inp.Z;
  pot.X = Inp.X * cos(ang) + Inp.Y * sin(ang); 
  pot.Y = Inp.X * sin(ang) - Inp.Y * cos(ang);
  return pot;
}

VOID GenSphere( INT X, INT Y, INT R)
{
  INT xs = X, ys = Y, zs = 0, a = 0, b = 0;
  DOUBLE  tet, alp;

  for (b = 0, tet = 0; b < M; b++, tet += 2 * PI / M)
  {
    for (a = 0, alp = 0; a < N; a++, alp += 2 * PI / N)
    {
      Points[b][a].X = X + R * cos(tet) * sin(alp);
      Points[b][a].Y = Y + R * sin(tet) * sin(alp); 
      Points[b][a].Z = R;
    }
  }
}
VOID DrawSphere(HDC hDC,  INT X, INT Y, INT R)
{
  INT xs = 0, ys = 0, a = 0, b = 0;

  DOUBLE t = clock() / CLOCKS_PER_SEC;
  GenSphere(X, Y, R);
  for (b = 0; b < M; b++)
  {
    for (a = 0; a < N; a++)
    {
      Points[b][a] = RotY(Points[b][a], 45 * t);
      Ellipse(hDC, Points[b][a].X - 1, Points[b][a].Y - 1, Points[b][a].X + 1, Points[b][a].Y + 10);
    }
  }
}
