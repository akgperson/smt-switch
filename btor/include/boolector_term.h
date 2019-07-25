#ifndef SMT_BOOLECTOR_TERM_H
#define SMT_BOOLECTOR_TERM_H

#include <vector>

#include "boolector.h"

#include "fun.h"
#include "term.h"
#include "utils.h"

#include "boolector_fun.h"
#include "boolector_sort.h"

namespace smt {

// forward declaration
class BoolectorSolver;

class BoolectorTermIter : public TermIterBase
{
 public:
  BoolectorTermIter(const std::vector<Term>::const_iterator v_it)
      : v_it(v_it){};
  BoolectorTermIter(const BoolectorTermIter & it) { v_it = it.v_it; };
  ~BoolectorTermIter(){};
  BoolectorTermIter & operator=(const BoolectorTermIter & it);
  void operator++() override;
  void operator++(int junk);
  const Term operator*() const override;
  bool operator==(const BoolectorTermIter & it);
  bool operator!=(const BoolectorTermIter & it);

 protected:
  bool equal(const TermIterBase & other) const override;

 private:
  std::vector<Term>::const_iterator v_it;
};

class BoolectorTerm : public AbsTerm
{
 public:
   BoolectorTerm(Btor * b, BoolectorNode * n, std::vector<Term> c, Fun o, bool is_sym)
     : btor(b), node(n), children(c), f(o), is_sym(is_sym){};
   BoolectorTerm(Btor * b, BoolectorNode * n, std::vector<Term> c, Op o, bool is_sym)
     : btor(b), node(n), children(c), f(Fun(new BoolectorFun(o))), is_sym(is_sym){};
   BoolectorTerm(Btor * b, BoolectorNode * n, std::vector<Term> c, PrimOp o, bool is_sym)
     : btor(b), node(n), children(c), f(Fun(new BoolectorFun(Op(o)))), is_sym(is_sym){};
  ~BoolectorTerm();
  std::size_t hash() const override;
  bool compare(const Term & absterm) const override;
  Fun get_fun() const override;
  Sort get_sort() const override;
  bool is_symbolic_const() const override;
  bool is_interpreted_const() const override;
  virtual std::string to_string() const override;
  uint64_t to_int() const override;
  /** Iterators for traversing the children
   */
  TermIter begin() override;
  TermIter end() override;

 protected:
  Btor * btor;
  BoolectorNode * node;
  std::vector<Term> children;
  Fun f;
  bool is_sym;

  friend class BoolectorSolver;
  friend class BoolectorTermIter;
};

}  // namespace smt

#endif
