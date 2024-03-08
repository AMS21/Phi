#include "SetupRuntimeFailure.hpp"

#include <phi/core/ref_ptr.hpp>

int main()
{
    SetupRuntimeFailure();

    // NOTE: You should not use anything from the detail namespace this is just to verify the assertion logic is correct.
    // But the actual problem should never be hit by ref_ptr.
    phi::detail::ref_ptr_control_block control_block;

    // Starts with ref_count = 1
    control_block.decrement_ref_count(); // ref_count = 0
    control_block.decrement_ref_count(); // double free error
}
