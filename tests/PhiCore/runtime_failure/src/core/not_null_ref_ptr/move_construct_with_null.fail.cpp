#include "SetupRuntimeFailure.hpp"

#include <phi/compiler_support/warning.hpp>
#include <phi/core/move.hpp>

// NOTE: Very evil macro hack to create an invalid not_null_ref_ptr
PHI_CLANG_SUPPRESS_WARNING("-Wkeyword-macro")
#define private public

#include <phi/core/ref_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    phi::not_null_ref_ptr<int> not_null = new int(21);

    // Create invalid state
    not_null.m_ControlBlock = nullptr;

    phi::not_null_ref_ptr<int> ptr(phi::move(not_null));
}
