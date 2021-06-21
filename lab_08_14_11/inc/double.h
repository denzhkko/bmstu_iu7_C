#ifndef __DOUBLE_H__

#define __DOUBLE_H__

#define DOUBLE_TOL                      1e-05

#define IS_DOUBLE_EQ(F_NUM, S_NUM) (fabs(F_NUM - S_NUM) < DOUBLE_TOL)

#endif // __DOUBLE_H__
