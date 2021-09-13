#ifndef INCG_PHI_UNITTEST_TESTTYPES_HPP
#define INCG_PHI_UNITTEST_TESTTYPES_HPP

#include <Phi/Core/Nullptr.hpp>

class Class
{
public:
    ~Class();
};

struct Struct
{
    ~Struct();
};

class Empty
{};

class NotEmpty
{
public:
    virtual ~NotEmpty();
};

union Union
{};

union NonEmptyUnion
{
    int      x;
    unsigned y;
};

struct bit_zero
{
    int : 0;
};

struct bit_one
{
    int : 1;
};

class Abstract
{
    virtual ~Abstract() = 0;
};

template <typename>
struct AbstractTemplate
{
    virtual ~AbstractTemplate() = 0;

    virtual void test() = 0;
};

template <>
struct AbstractTemplate<double>
{};

enum Enum
{
    zero,
    one
};

enum EnumSigned : int
{
    two
};

enum EnumUnsigned : unsigned
{
    three
};

enum class EnumClass
{
    zero,
    one
};

struct incomplete_type;

using Function = void();

using FunctionPtr = void (*)();

using MemberObjectPtr = int Class::*;

using MemberFunctionPtr = void (Class::*)();

#endif // INCG_PHI_UNITTEST_TESTTYPES_HPP
