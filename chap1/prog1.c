#include "prog1.h"
#include "slp.h"

A_stm prog(void)
{

  return A_CompoundStm(A_AssignStm("a", A_OpExp(A_NumExp(5), A_plus, A_NumExp(3))),
                       A_CompoundStm(A_AssignStm("b", A_EseqExp(A_PrintStm(A_PairExpList(A_IdExp("a"), A_LastExpList(A_OpExp(A_IdExp("a"), A_minus, A_NumExp(1))))),
                                                                A_OpExp(A_NumExp(10), A_times, A_IdExp("a")))),
                                     A_PrintStm(A_LastExpList(A_IdExp("b")))));
}

static int maxargs_exp(A_exp exp)
{
  if (exp->kind == A_eseqExp) {
    return maxargs(exp->u.eseq.stm);
  }
  return 0;
}

#define MAX(x, y) (x) > (y) ? (x) : (y)

int maxargs(A_stm stm)
{
  switch (stm->kind) {
  case A_compoundStm: {
    int m, n;
    m = maxargs(stm->u.compound.stm1);
    n = maxargs(stm->u.compound.stm2);
    return MAX(m, n);
  }
  case A_assignStm:
    return maxargs_exp(stm->u.assign.exp);
  case A_printStm: {
    int max = 0, n_args = 1;
    A_expList exps = stm->u.print.exps;
    while (exps->kind != A_lastExpList) {
      ++n_args;
      int n = maxargs_exp(exps->u.pair.head);
      max = MAX(max, n);
      exps = exps->u.pair.tail;
    }
    return MAX(max, n_args);
  }
  }
  return 0;
}
