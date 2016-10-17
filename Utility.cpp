//----------------------------------------------
//    Implementation of general utility routines
//----------------------------------------------
//
//  Programmer: Donald House
//  Date: March 8, 1999
//
//  Copyright (C) - Donald H. House. 2005
//

#include "Utility.h"

/*
  computes sqrt(a^2 + b^2) without destructive underflow or overflow
*/
double pythag(double a, double b)
{
  double absa, absb;

  absa = Abs(a);
  absb = Abs(b);

  if(absa > absb)
    return absa * sqrt(1.0 + Sqr(absb / absa));
  else if(absb > 0)
    return absb * sqrt(1.0 + Sqr(absa / absb));
  else
    return 0;
}

/*
  Utility message routines
*/
void prompt(const char *s)
{
  std::cout << s << " ";
}

void message(const char *s1, const char *s2, const char *s3)
{
  std::cout << s1;
  if(s2 != NULL && strlen(s2) > 0)
    std::cout << " " << s2;
  if(s3 != NULL && strlen(s3) > 0)
    std::cout << " " << s3;
  std::cout << std::endl;
}

void status(const char *s1, const char *s2, const char *s3)
{
  std::cout << "Status: ";
  message(s1, s2, s3);
}

void error(const char *s1, const char *s2, const char *s3)
{
  std::cerr << "Error: ";
  std::cerr << s1;
  if(s2 != NULL && strlen(s2) > 0)
    std::cerr << " " << s2;
  if(s3 != NULL && strlen(s3) > 0)
    std::cerr << " " << s3;
  std::cerr << std::endl;
}

void abort(const char *s1, const char *s2, const char *s3)
{
  error(s1, s2, s3);
  exit(1);
}
