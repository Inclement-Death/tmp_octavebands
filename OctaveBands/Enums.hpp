#pragma once

#include "pch.hpp"

enum FractionalOctaves
{
  None = 0,
  Full = 0x01,
  TwoThird = 0x02,
  Half = 0x04,
  Third = 0x08,
  Sixth = 0x10
};

enum ProcessingFlags
{
  Adjust = 0x01,
  Output = 0x02,
  Both = Adjust | Output
};

enum LimitCalcType
{
  Lower = 1,
  Upper = 2,
  Width = 4
};

enum OctavePosition
{
  High,
  Low
};

enum RenardOctaveIterMax
{
  FullMax = 12,
  HalfMax = 23,
  ThirdMax = 34,
};

enum RenardInterval
{
  R10 = 10,
  R20 = 20,
};
