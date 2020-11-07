#ifndef INCG_PHI_CORE_FINALACTION_HPP
#define INCG_PHI_CORE_FINALACTION_HPP

#include "Phi/PhiConfig.hpp"

#include <type_traits>
#include <utility>

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename ActionT>
class FinalAction
{
private:
    static_assert(!std::is_reference_v<ActionT> && !std::is_const_v<ActionT> &&
                          !std::is_volatile_v<ActionT>,
                  "FinalAction should store its callable by value");

public:
    constexpr explicit FinalAction(ActionT action) noexcept
        : m_Action(std::move(action))
    {}

    FinalAction(FinalAction&&)      = delete;
    FinalAction(const FinalAction&) = delete;

    FinalAction& operator=(const FinalAction&) = delete;
    FinalAction& operator=(FinalAction&&) = delete;

    ~FinalAction() noexcept
    {
        m_Action();
    }

private:
    ActionT m_Action;
};

template <typename ActionT>
[[nodiscard]] constexpr FinalAction<
        typename std::remove_cv_t<typename std::remove_reference_t<ActionT>>>
finally(ActionT&& action) noexcept
{
    return FinalAction<typename std::remove_cv_t<typename std::remove_reference_t<ActionT>>>(
            std::forward<ActionT>(action));
}

DETAIL_PHI_END_NAMESPACE()

#endif // INCG_PHI_CORE_FINALACTION_HPP
