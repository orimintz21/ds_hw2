
#ifndef EX2_RANKTREEEXCEPTIONS_H
#define EX2_RANKTREEEXCEPTIONS_H
#include "exception"

class RankTreeExceptions : std::exception{};
class not_in_tree : RankTreeExceptions {};
class already_in_tree : RankTreeExceptions{};

#endif //EX2_RANKTREEEXCEPTIONS_H
