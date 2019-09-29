#include "prog1.h"
#include "slp.h"

#include <stdio.h>
#include <string.h>

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

typedef struct table {
  string id;
  int value;
  struct table* next;
} table;

static table* insert_value(table* t, string name, int value)
{
  table* new_table = checked_malloc(sizeof *new_table);
  new_table->id = String(name);
  new_table->value = value;
  new_table->next = t;
  return new_table;
}

static void do_interp(A_stm stm, table** t);

static int look_up_value(table* p, string id)
{
  while (p) {
    if (strcmp(p->id, id) == 0) {
      return p->value;
    }
    p = p->next;
  }
  fprintf(stderr, "identifier '%s' not found", id);
  assert(FALSE);
  return 0;
}

/// returns evaluation result of 'exp'
static int do_interp_exp(A_exp exp, table** t)
{
  switch (exp->kind) {
  case A_idExp:
    return look_up_value(*t, exp->u.id);
  case A_numExp:
    return exp->u.num;
  case A_opExp: {
    int lhs = do_interp_exp(exp->u.op.left, t);
    int rhs = do_interp_exp(exp->u.op.right, t);
    switch (exp->u.op.oper) {
    case A_plus:
      return lhs + rhs;
    case A_minus:
      return lhs - rhs;
    case A_times:
      return lhs * rhs;
    case A_div:
      return lhs / rhs;
    }
  } break;
  case A_eseqExp:
    do_interp(exp->u.eseq.stm, t);
    return do_interp_exp(exp->u.eseq.exp, t);
  }
  assert(FALSE);
  return 0;
}

static void do_interp(A_stm stm, table** t)
{
  switch (stm->kind) {
  case A_compoundStm:
    do_interp(stm->u.compound.stm1, t);
    do_interp(stm->u.compound.stm2, t);
    break;
  case A_assignStm:
    *t = insert_value(*t, stm->u.assign.id, do_interp_exp(stm->u.assign.exp, t));
    break;
  case A_printStm: {
    A_expList exps = stm->u.print.exps;
    while (exps->kind != A_lastExpList) {
      printf("%d ", do_interp_exp(exps->u.pair.head, t));
      exps = exps->u.pair.tail;
    }
    printf("%d\n", do_interp_exp(exps->u.last, t));
  } break;
  }
}

void interp(A_stm stm)
{
  table* t = NULL;
  do_interp(stm, &t);
}
