#ifndef EX2_EX2EXCEPTIONS_H
#define EX2_EX2EXCEPTIONS_H
#include "exception"

class Ex2Exceptions : std::exception{};

class invalid_input : Ex2Exceptions{};

class not_in_hash : Ex2Exceptions {};

class already_in_hash : Ex2Exceptions{};

class failure: Ex2Exceptions{};

#endif //EX2_EX2EXCEPTIONS_H
