/*********************                                                        */
/*! \file sort_inference.h
** \verbatim
** Top contributors (to current version):
**   Makai Mann
** This file is part of the smt-switch project.
** Copyright (c) 2020 by the authors listed in the file AUTHORS
** in the top-level source directory) and their institutional affiliations.
** All rights reserved.  See the file LICENSE in the top-level source
** directory for licensing information.\endverbatim
**
** \brief Utility functions for checking sortedness and computing the
**        expected sort when building a term.
**
**/

#include <initializer_list>

#include "ops.h"
#include "sort.h"
#include "term.h"

namespace smt {

// main functions for sort checking and inference

/** Checks if applying the operator to the terms is well-sorted
 *  @param op the op to apply
 *  @param terms the vector of terms to apply it to
 *  @return true iff this is a well-sorted operation
 */
bool check_sortedness(Op op, const TermVec & terms);

// useful helper functions -- used for sort checking

/** Checks that the sorts are equivalent
 *  @param sorts a non-empty vector of sorts
 *  @return true iff they're all equal
 */
bool equal_sorts(const SortVec & sorts);

/** Checks that the sorts have the same SortKind
 *  @param sorts a non-empty vector of sorts
 *  @return true iff they're all equal
 */
bool equal_sortkinds(const SortVec & sorts);

/** Checks that Ite arguments are well-sorted
 *  @param sorts a vector of sorts
 *  @return true iff only the sorts are valid for an ite
 */
bool check_ite_sorts(const SortVec & sorts);

/** Returns true iff all the sorts have SortKind sk
 *  @param sk the expected SortKind
 *  @param sorts the vector of Sorts to check
 *  @return true iff all SortKinds have sort sk
 */
bool check_sortkind_matches(SortKind sk, const SortVec & sorts);

/** Checks if the sorts are well-sorted for an apply operator
 *  @param sorts the vector of sorts
 *  @param returns true iff the first sort is a function sort
 *         and the rest of the sorts match the domain of the
 *         function
 */
bool check_apply_sorts(const SortVec & sorts);

/** Checks if the sorts are well-sorted for a select operator
 *  @param sorts the vector of sorts
 *  @param returns true iff the first sort is an array sort
 *         and the second sort is the index sort
 */
bool check_select_sorts(const SortVec & sorts);

/** Checks if the sorts are well-sorted for a store operator
 *  @param sorts the vector of sorts
 *  @param returns true iff the first sort is an array sort
 *         and the next two match the index and element sort
 */
bool check_store_sorts(const SortVec & sorts);

bool bool_sorts(const SortVec & sorts)
{
  return check_sortkind_matches(BOOL, sorts);
};

bool bv_sorts(const SortVec & sorts)
{
  return check_sortkind_matches(BV, sorts);
};

bool real_sorts(const SortVec & sorts)
{
  return check_sortkind_matches(REAL, sorts);
};

bool int_sorts(const SortVec & sorts)
{
  return check_sortkind_matches(INT, sorts);
};

bool arithmetic_sorts(const SortVec & sorts)
{
  return check_sortkind_matches(INT, sorts)
         || check_sortkind_matches(REAL, sorts);
}

bool array_sorts(const SortVec & sorts)
{
  return check_sortkind_matches(ARRAY, sorts);
};

bool function_sorts(const SortVec & sorts)
{
  return check_sortkind_matches(FUNCTION, sorts);
};

}  // namespace smt