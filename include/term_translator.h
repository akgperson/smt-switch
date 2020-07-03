/*********************                                                        */
/*! \file term_translator.h
** \verbatim
** Top contributors (to current version):
**   Makai Mann
** This file is part of the smt-switch project.
** Copyright (c) 2020 by the authors listed in the file AUTHORS
** in the top-level source directory) and their institutional affiliations.
** All rights reserved.  See the file LICENSE in the top-level source
** directory for licensing information.\endverbatim
**
** \brief Class for translating terms from one solver to another. Keeps
**        a cache so it can be called multiple times (without redeclaring
**        symbols, which would throw an exception).
**/

#ifndef SMT_TERM_TRANSLATOR_H
#define SMT_TERM_TRANSLATOR_H

#include <unordered_map>

#include "smt_defs.h"
#include "solver.h"
#include "sort.h"
#include "term.h"

namespace smt {
class TermTranslator
{
 public:
  TermTranslator(SmtSolver & s) : solver(s) {}
  Sort transfer_sort(const Sort & sort) const;
  Term transfer_term(const Term & term);
  /* Returns reference to cache -- can be used to populate with symbols */
  UnorderedTermMap & get_cache() { return cache; };
  SmtSolver & get_solver() { return solver; };

 protected:
  /** Creates a term value from a string of the given sort
   *  @param val the string representation of the value
   *  @param orig_sort the sort from the original solver (transfer_sort is
   *  called in this function)
   *  @return a term with the given value
   */
  Term value_from_smt2(const std::string val, const Sort sort) const;

  /** identifies relevant casts to perform an operation
   *  assumes the operation is currently not well-sorted
   *  e.g. check_sortedness returns false
   *  could be more general in the future, for now focusing on
   *  Bool / BV1 case
   *  It can either change the operator or cast the terms
   *  @param op the operator that should be applied
   *  @param terms the terms to apply it to
   *  @return a well-sorted term with an operator applied to casted terms
   *  Note: the operator can change, e.g. BVAnd -> And
   *  This method uses cast_term
   */
  Term cast_op(Op op, const TermVec & terms) const;

  /** casts a term to a different sort
   *  could be more general in future, for now just does a few common
   * conversions such as: Bool <-> BV1 Int  <-> Real
   *  @param term the term to cast
   *  @param the sort to cast it to
   *  @return the new term
   *  throws a NotImplementedException if it cannot interpret the cast
   *  the term and sort MUST belong to the same solver
   */
  Term cast_term(const Term & term, const Sort & sort) const;

  /** casts a value term to a different sort
   *  could be more general in future, for now just does
   * conversions such as: Bool <-> BV1
   *  @param val the value term to cast
   *  @param the sort to cast it to
   *  @return the new term
   *  throws a NotImplementedException if it cannot interpret the cast
   *  the term and sort MUST belong to the same solver
   */
  Term cast_value(const Term & term, const Sort & sort) const;

  SmtSolver & solver;
  UnorderedTermMap cache;
};
}  // namespace smt

#endif
