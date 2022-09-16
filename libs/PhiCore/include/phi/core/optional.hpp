// This file is heavily inspired by Sy Brands Optional library https://github.com/TartanLlama/Optional
// licensed under CC0 https://github.com/TartanLlama/Optional/blob/master/COPYING
// Original file at https://github.com/TartanLlama/Optional/blob/master/include/tl/Optional.hpp

#ifndef INCG_PHI_CORE_OPTIONAL_HPP
#define INCG_PHI_CORE_OPTIONAL_HPP

#include "phi/phi_config.hpp"

#if PHI_HAS_EXTENSION_PRAGMA_ONCE()
#    pragma once
#endif

#include "phi/algorithm/swap.hpp"
#include "phi/compiler_support/constexpr.hpp"
#include "phi/compiler_support/cpp_standard.hpp"
#include "phi/compiler_support/extended_attributes.hpp"
#include "phi/compiler_support/nodiscard.hpp"
#include "phi/compiler_support/warning.hpp"
#include "phi/core/address_of.hpp"
#include "phi/core/assert.hpp"
#include "phi/core/boolean.hpp"
#include "phi/core/declval.hpp"
#include "phi/core/forward.hpp"
#include "phi/core/invoke.hpp"
#include "phi/core/move.hpp"
#include "phi/core/size_t.hpp"
#include "phi/generated/compiler_support/features.hpp"
#include "phi/type_traits/conjunction.hpp"
#include "phi/type_traits/decay.hpp"
#include "phi/type_traits/enable_if.hpp"
#include "phi/type_traits/invoke_result.hpp"
#include "phi/type_traits/is_assignable.hpp"
#include "phi/type_traits/is_constructible.hpp"
#include "phi/type_traits/is_convertible.hpp"
#include "phi/type_traits/is_copy_assignable.hpp"
#include "phi/type_traits/is_copy_constructible.hpp"
#include "phi/type_traits/is_lvalue_reference.hpp"
#include "phi/type_traits/is_move_assignable.hpp"
#include "phi/type_traits/is_move_constructible.hpp"
#include "phi/type_traits/is_nothrow_move_assignable.hpp"
#include "phi/type_traits/is_nothrow_move_constructible.hpp"
#include "phi/type_traits/is_nothrow_swappable.hpp"
#include "phi/type_traits/is_scalar.hpp"
#include "phi/type_traits/is_swappable.hpp"
#include "phi/type_traits/is_trivially_copy_assignable.hpp"
#include "phi/type_traits/is_trivially_copy_constructible.hpp"
#include "phi/type_traits/is_trivially_destructible.hpp"
#include "phi/type_traits/is_trivially_move_assignable.hpp"
#include "phi/type_traits/is_trivially_move_constructible.hpp"
#include "phi/type_traits/is_void.hpp"
#include "phi/type_traits/remove_const.hpp"
#include "phi/type_traits/void_t.hpp"
#include <functional>
#include <utility>

#if PHI_HAS_WORKING_IS_CONSTRUCTIBLE() && PHI_HAS_WORKING_IS_TRIVIALLY_ASSIGNABLE() &&             \
        PHI_HAS_WORKING_IS_TRIVIALLY_DESTRUCTIBLE() &&                                             \
        PHI_HAS_WORKING_IS_TRIVIALLY_MOVE_ASSIGNABLE() &&                                          \
        PHI_HAS_WORKING_IS_TRIVIALLY_MOVE_CONSTRUCTIBLE() &&                                       \
        PHI_HAS_WORKING_IS_TRIVIALLY_COPY_ASSIGNABLE() &&                                          \
        PHI_HAS_WORKING_IS_TRIVIALLY_COPY_CONSTRUCTIBLE() &&                                       \
        PHI_HAS_WORKING_IS_NOTHROW_CONSTRUCTIBLE() && PHI_HAS_WORKING_IS_MOVE_CONSTRUCTIBLE() &&   \
        PHI_HAS_WORKING_IS_SCALAR() && PHI_HAS_WORKING_IS_INVOCABLE()

#    define PHI_HAS_WORKING_OPTIONAL() 1

DETAIL_PHI_BEGIN_NAMESPACE()

/// Used to represent an optional with no data; essentially a bool
struct monostate
{};

///  A tag type to tell optional to construct its value in-place
struct in_place_t
{
    explicit in_place_t() = default;
};
/// A tag to tell optional to construct its value in-place
static constexpr in_place_t in_place{};

template <typename TypeT>
class optional;

namespace detail
{
    // Check if invoking F for some Us returns void
    template <typename FuncT, typename = void, typename... ArgsT>
    struct returns_void_impl;

    template <typename FuncT, typename... ArgsT>
    struct returns_void_impl<FuncT, void_t<invoke_result_t<FuncT, ArgsT...>>, ArgsT...>
        : public is_void<invoke_result_t<FuncT, ArgsT...>>
    {};

    template <typename FuncT, typename... ArgsT>
    using returns_void = returns_void_impl<FuncT, void, ArgsT...>;

    template <typename TypeT, typename... ArgsT>
    using enable_if_ret_void = enable_if_t<returns_void<TypeT&&, ArgsT...>::value>;

    template <typename TypeT, typename... ArgsT>
    using disable_if_ret_void = enable_if_t<!returns_void<TypeT&&, ArgsT...>::value>;

    template <typename TypeT, typename OtherT>
    using enable_forward_value = enable_if_t<is_constructible<TypeT, OtherT&&>::value &&
                                             !is_same<decay_t<OtherT>, in_place_t>::value &&
                                             !is_same<optional<TypeT>, decay_t<OtherT>>::value>;

    template <typename TypeT, typename OtherT>
    using enable_assign_forward =
            enable_if_t<!is_same<optional<TypeT>, decay_t<OtherT>>::value &&
                        !conjunction<is_scalar<TypeT>, is_same<TypeT, decay_t<OtherT>>>::value &&
                        is_constructible<TypeT, OtherT>::value &&
                        is_assignable<TypeT&, OtherT>::value>;

    template <typename TypeT, typename Type2T, typename OtherT>
    using enable_from_other =
            enable_if_t<is_constructible<TypeT, OtherT>::value &&
                        !is_constructible<TypeT, optional<Type2T>&>::value &&
                        !is_constructible<TypeT, optional<Type2T>&&>::value &&
                        !is_constructible<TypeT, const optional<Type2T>&>::value &&
                        !is_constructible<TypeT, const optional<Type2T>&&>::value &&
                        !is_convertible<optional<Type2T>&, TypeT>::value &&
                        !is_convertible<optional<Type2T>&&, TypeT>::value &&
                        !is_convertible<const optional<Type2T>&, TypeT>::value &&
                        !is_convertible<const optional<Type2T>&&, TypeT>::value>;

    template <typename TypeT, typename Type2T, typename OtherT>
    using enable_assign_from_other =
            enable_if_t<is_constructible<TypeT, OtherT>::value &&
                        is_assignable<TypeT&, OtherT>::value &&
                        !is_constructible<TypeT, optional<Type2T>&>::value &&
                        !is_constructible<TypeT, optional<Type2T>&&>::value &&
                        !is_constructible<TypeT, const optional<Type2T>&>::value &&
                        !is_constructible<TypeT, const optional<Type2T>&&>::value &&
                        !is_convertible<optional<Type2T>&, TypeT>::value &&
                        !is_convertible<optional<Type2T>&&, TypeT>::value &&
                        !is_convertible<const optional<Type2T>&, TypeT>::value &&
                        !is_convertible<const optional<Type2T>&&, TypeT>::value &&
                        !is_assignable<TypeT&, optional<Type2T>&>::value &&
                        !is_assignable<TypeT&, optional<Type2T>&&>::value &&
                        !is_assignable<TypeT&, const optional<Type2T>&>::value &&
                        !is_assignable<TypeT&, const optional<Type2T>&&>::value>;

    // Trait for checking if a type is a phi::optional
    template <typename TypeT>
    struct is_optional_impl : false_type
    {};

    template <typename TypeT>
    struct is_optional_impl<optional<TypeT>> : true_type
    {};

    template <typename TypeT>
    using is_optional = is_optional_impl<decay_t<TypeT>>;

    PHI_MSVC_SUPPRESS_WARNING_PUSH()
    PHI_MSVC_SUPPRESS_WARNING(4583) // 'x': destructor is not implicitly called
    PHI_MSVC_SUPPRESS_WARNING(4582) // 'x': constructor is not implicitly called

    // The storage base manages the actual storage, and correctly propagates
    // trivial destruction from T. This case is for when T is not trivially
    // destructible.
    template <typename TypeT, bool = is_trivially_destructible<TypeT>::value>
    struct optional_storage_base
    {
        constexpr optional_storage_base() noexcept
            : m_dummy()
            , m_has_value(false)
        {}

        template <typename... ArgsT>
        constexpr optional_storage_base(in_place_t, ArgsT&&... args)
            : m_Value(phi::forward<ArgsT>(args)...)
            , m_has_value(true)
        {}

        ~optional_storage_base()
        {
            if (m_has_value)
            {
                m_Value.~TypeT();
                m_has_value = false;
            }
        }

        struct dummy
        {};

        union
        {
            dummy m_dummy;
            TypeT m_Value;
        };

        bool m_has_value;
    };

    // This case is for when T is trivially destructible.
    template <typename TypeT>
    struct optional_storage_base<TypeT, true>
    {
        constexpr optional_storage_base() noexcept
            : m_dummy()
            , m_has_value(false)
        {}

        template <typename... OtherT>
        constexpr optional_storage_base(in_place_t, OtherT&&... u)
            : m_Value(phi::forward<OtherT>(u)...)
            , m_has_value(true)
        {}

        // No destructor, so this class is trivially destructible

        struct dummy
        {};

        union
        {
            dummy m_dummy;
            TypeT m_Value;
        };

        bool m_has_value = false;
    };

    PHI_MSVC_SUPPRESS_WARNING_POP()

    // This base class provides some handy member functions which can be used in
    // further derived classes
    template <typename TypeT>
    struct optional_operations_base : public optional_storage_base<TypeT>
    {
        using optional_storage_base<TypeT>::optional_storage_base;

        void hard_reset() noexcept
        {
            get().~TypeT();
            this->m_has_value = false;
        }

        template <typename... ArgsT>
        void construct(ArgsT&&... args) noexcept
        {
            new (phi::address_of(this->m_Value)) TypeT(phi::forward<ArgsT>(args)...);
            this->m_has_value = true;
        }

        template <typename OptT>
        void assign(OptT&& rhs)
        {
            if (this->has_value())
            {
                if (rhs.has_value())
                {
                    this->m_Value = phi::forward<OptT>(rhs).get();
                }
                else
                {
                    this->m_Value.~TypeT();
                    this->m_has_value = false;
                }
            }

            else if (rhs.has_value())
            {
                construct(phi::forward<OptT>(rhs).get());
            }
        }

        PHI_NODISCARD constexpr bool has_value() const
        {
            return this->m_has_value;
        }

        PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT& get() &
        {
            return this->m_Value;
        }

        PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const TypeT& get() const&
        {
            return this->m_Value;
        }

        PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT&& get() &&
        {
            return phi::move(this->m_Value);
        }

        PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const TypeT&& get() const&&
        {
            return phi::move(this->m_Value);
        }
    };

    // This class manages conditionally having a trivial copy constructor
    // This specialization is for when T is trivially copy constructible
    template <typename TypeT, bool = is_trivially_copy_constructible<TypeT>::value>
    struct optional_copy_base : public optional_operations_base<TypeT>
    {
        using optional_operations_base<TypeT>::optional_operations_base;
    };

    // This specialization is for when T is not trivially copy constructible
    template <typename TypeT>
    struct optional_copy_base<TypeT, false> : public optional_operations_base<TypeT>
    {
        using optional_operations_base<TypeT>::optional_operations_base;

        optional_copy_base() = default;

        optional_copy_base(const optional_copy_base& rhs)
        {
            if (rhs.has_value())
            {
                this->construct(rhs.get());
            }
            else
            {
                this->m_has_value = false;
            }
        }

        optional_copy_base(optional_copy_base&& rhs) = default;

        optional_copy_base& operator=(const optional_copy_base& rhs) = default;

        optional_copy_base& operator=(optional_copy_base&& rhs) = default;
    };

    // This class manages conditionally having a trivial move constructor.
    template <typename TypeT, bool = is_trivially_move_constructible<TypeT>::value>
    struct optional_move_base : public optional_copy_base<TypeT>
    {
        using optional_copy_base<TypeT>::optional_copy_base;
    };

    template <typename TypeT>
    struct optional_move_base<TypeT, false> : public optional_copy_base<TypeT>
    {
        using optional_copy_base<TypeT>::optional_copy_base;

        optional_move_base()                              = default;
        optional_move_base(const optional_move_base& rhs) = default;

        optional_move_base(optional_move_base&& rhs) noexcept(
                is_nothrow_move_constructible<TypeT>::value)
        {
            if (rhs.has_value())
            {
                this->construct(phi::move(rhs.get()));
            }
            else
            {
                this->m_has_value = false;
            }
        }
        optional_move_base& operator=(const optional_move_base& rhs) = default;
        optional_move_base& operator=(optional_move_base&& rhs)      = default;
    };

    // This class manages conditionally having a trivial copy assignment operator
    template <typename TypeT,
              bool = is_trivially_copy_assignable<TypeT>::value&& is_trivially_copy_constructible<
                      TypeT>::value&& is_trivially_destructible<TypeT>::value>
    struct optional_copy_assign_base : public optional_move_base<TypeT>
    {
        using optional_move_base<TypeT>::optional_move_base;
    };

    template <typename TypeT>
    struct optional_copy_assign_base<TypeT, false> : public optional_move_base<TypeT>
    {
        using optional_move_base<TypeT>::optional_move_base;

        optional_copy_assign_base()                                     = default;
        optional_copy_assign_base(const optional_copy_assign_base& rhs) = default;

        optional_copy_assign_base(optional_copy_assign_base&& rhs) = default;
        optional_copy_assign_base& operator=(const optional_copy_assign_base& rhs)
        {
            this->assign(rhs);
            return *this;
        }
        optional_copy_assign_base& operator=(optional_copy_assign_base&& rhs) = default;
    };

    // This class manages conditionally having a trivial move assignment operator
    template <typename TypeT,
              bool = is_trivially_destructible<TypeT>::value&& is_trivially_move_constructible<
                      TypeT>::value&& is_trivially_move_assignable<TypeT>::value>
    struct optional_move_assign_base : public optional_copy_assign_base<TypeT>
    {
        using optional_copy_assign_base<TypeT>::optional_copy_assign_base;
    };

    template <typename TypeT>
    struct optional_move_assign_base<TypeT, false> : public optional_copy_assign_base<TypeT>
    {
        using optional_copy_assign_base<TypeT>::optional_copy_assign_base;

        optional_move_assign_base()                                     = default;
        optional_move_assign_base(const optional_move_assign_base& rhs) = default;

        optional_move_assign_base(optional_move_assign_base&& rhs) = default;

        optional_move_assign_base& operator=(const optional_move_assign_base& rhs) = default;

        optional_move_assign_base& operator=(optional_move_assign_base&& rhs) noexcept(
                is_nothrow_move_constructible<TypeT>::value&&
                        is_nothrow_move_assignable<TypeT>::value)
        {
            this->assign(phi::move(rhs));
            return *this;
        }
    };

    // optional_delete_ctor_base will conditionally delete copy and move
    // constructors depending on whether T is copy/move constructible
    template <typename TypeT, bool EnableCopy = is_copy_constructible<TypeT>::value,
              bool EnableMove = is_move_constructible<TypeT>::value>
    struct optional_delete_ctor_base
    {
        optional_delete_ctor_base()                                                = default;
        optional_delete_ctor_base(const optional_delete_ctor_base&)                = default;
        optional_delete_ctor_base(optional_delete_ctor_base&&) noexcept            = default;
        optional_delete_ctor_base& operator=(const optional_delete_ctor_base&)     = default;
        optional_delete_ctor_base& operator=(optional_delete_ctor_base&&) noexcept = default;
    };

    template <typename TypeT>
    struct optional_delete_ctor_base<TypeT, true, false>
    {
        optional_delete_ctor_base()                                                = default;
        optional_delete_ctor_base(const optional_delete_ctor_base&)                = default;
        optional_delete_ctor_base(optional_delete_ctor_base&&) noexcept            = delete;
        optional_delete_ctor_base& operator=(const optional_delete_ctor_base&)     = default;
        optional_delete_ctor_base& operator=(optional_delete_ctor_base&&) noexcept = default;
    };

    template <typename TypeT>
    struct optional_delete_ctor_base<TypeT, false, true>
    {
        optional_delete_ctor_base()                                                = default;
        optional_delete_ctor_base(const optional_delete_ctor_base&)                = delete;
        optional_delete_ctor_base(optional_delete_ctor_base&&) noexcept            = default;
        optional_delete_ctor_base& operator=(const optional_delete_ctor_base&)     = default;
        optional_delete_ctor_base& operator=(optional_delete_ctor_base&&) noexcept = default;
    };

    template <typename TypeT>
    struct optional_delete_ctor_base<TypeT, false, false>
    {
        optional_delete_ctor_base()                                                = default;
        optional_delete_ctor_base(const optional_delete_ctor_base&)                = delete;
        optional_delete_ctor_base(optional_delete_ctor_base&&) noexcept            = delete;
        optional_delete_ctor_base& operator=(const optional_delete_ctor_base&)     = default;
        optional_delete_ctor_base& operator=(optional_delete_ctor_base&&) noexcept = default;
    };

    // optional_delete_assign_base will conditionally delete copy and move
    // constructors depending on whether TypeT is copy/move constructible + assignable
    template <typename TypeT,
              bool EnableCopy =
                      (is_copy_constructible<TypeT>::value && is_copy_assignable<TypeT>::value),
              bool EnableMove =
                      (is_move_constructible<TypeT>::value && is_move_assignable<TypeT>::value)>
    struct optional_delete_assign_base
    {
        optional_delete_assign_base()                                                  = default;
        optional_delete_assign_base(const optional_delete_assign_base&)                = default;
        optional_delete_assign_base(optional_delete_assign_base&&) noexcept            = default;
        optional_delete_assign_base& operator=(const optional_delete_assign_base&)     = default;
        optional_delete_assign_base& operator=(optional_delete_assign_base&&) noexcept = default;
    };

    template <typename TypeT>
    struct optional_delete_assign_base<TypeT, true, false>
    {
        optional_delete_assign_base()                                                  = default;
        optional_delete_assign_base(const optional_delete_assign_base&)                = default;
        optional_delete_assign_base(optional_delete_assign_base&&) noexcept            = default;
        optional_delete_assign_base& operator=(const optional_delete_assign_base&)     = default;
        optional_delete_assign_base& operator=(optional_delete_assign_base&&) noexcept = delete;
    };

    template <typename TypeT>
    struct optional_delete_assign_base<TypeT, false, true>
    {
        optional_delete_assign_base()                                                  = default;
        optional_delete_assign_base(const optional_delete_assign_base&)                = default;
        optional_delete_assign_base(optional_delete_assign_base&&) noexcept            = default;
        optional_delete_assign_base& operator=(const optional_delete_assign_base&)     = delete;
        optional_delete_assign_base& operator=(optional_delete_assign_base&&) noexcept = default;
    };

    template <typename TypeT>
    struct optional_delete_assign_base<TypeT, false, false>
    {
        optional_delete_assign_base()                                                  = default;
        optional_delete_assign_base(const optional_delete_assign_base&)                = default;
        optional_delete_assign_base(optional_delete_assign_base&&) noexcept            = default;
        optional_delete_assign_base& operator=(const optional_delete_assign_base&)     = delete;
        optional_delete_assign_base& operator=(optional_delete_assign_base&&) noexcept = delete;
    };
} // namespace detail

/// A tag type to represent an empty optional
struct nullopt_t
{
    struct do_not_use
    {};

    constexpr explicit nullopt_t(do_not_use, do_not_use) noexcept
    {}
};

/// Represents an empty optional
static constexpr nullopt_t nullopt{nullopt_t::do_not_use{}, nullopt_t::do_not_use{}};

/// An optional object is an object that contains the storage for another
/// object and manages the lifetime of this contained object, if any. The
/// contained object may be initialized after the optional object has been
/// initialized, and may be destroyed before the optional object has been
/// destroyed. The initialization state of the contained object is tracked by
/// the optional object.
template <typename TypeT>
class optional : private detail::optional_move_assign_base<TypeT>,
                 private detail::optional_delete_ctor_base<TypeT>,
                 private detail::optional_delete_assign_base<TypeT>
{
    using base = detail::optional_move_assign_base<TypeT>;

    static_assert(!is_same<TypeT, in_place_t>::value,
                  "instantiation of optional with in_place_t is ill-formed");
    static_assert(!is_same<decay_t<TypeT>, nullopt_t>::value,
                  "instantiation of optional with nullopt_t is ill-formed");

public:
    using this_type  = optional<TypeT>;
    using value_type = TypeT;

    /// Constructs an optional that does not contain a value.
    constexpr optional() noexcept = default;

    constexpr optional(nullopt_t) noexcept
    {}

    /// Copy constructor
    ///
    /// If `rhs` contains a value, the stored value is direct-initialized with
    /// it. Otherwise, the constructed optional is empty.
    constexpr optional(const optional& rhs) = default;

    /// Move constructor
    ///
    /// If `rhs` contains a value, the stored value is direct-initialized with
    /// it. Otherwise, the constructed optional is empty.
    constexpr optional(optional&& rhs) = default;

    /// Constructs the stored value in-place using the given arguments.
    template <typename... ArgsT>
    constexpr explicit optional(enable_if_t<is_constructible<TypeT, ArgsT...>::value, in_place_t>,
                                ArgsT&&... args)
        : base(in_place, phi::forward<ArgsT>(args)...)
    {}

    template <typename OtherT, typename... ArgsT>
    PHI_EXTENDED_CONSTEXPR explicit optional(
            enable_if_t<is_constructible<TypeT, std::initializer_list<OtherT>&, ArgsT&&...>::value,
                        in_place_t>,
            std::initializer_list<OtherT> il, ArgsT&&... args)
    {
        this->construct(il, phi::forward<ArgsT>(args)...);
    }

    /// Constructs the stored value with `u`.
    template <typename OtherT                                      = TypeT,
              enable_if_t<is_convertible<OtherT&&, TypeT>::value>* = nullptr,
              detail::enable_forward_value<TypeT, OtherT>*         = nullptr>
    constexpr optional(OtherT&& other)
        : base(in_place, phi::forward<OtherT>(other))
    {}

    template <typename OtherT                                       = TypeT,
              enable_if_t<!is_convertible<OtherT&&, TypeT>::value>* = nullptr,
              detail::enable_forward_value<TypeT, OtherT>*          = nullptr>
    constexpr explicit optional(OtherT&& other)
        : base(in_place, phi::forward<OtherT>(other))
    {}

    /// Converting copy constructor.
    template <typename OtherT, detail::enable_from_other<TypeT, OtherT, const OtherT&>* = nullptr,
              enable_if_t<is_convertible<const OtherT&, TypeT>::value>* = nullptr>
    optional(const optional<OtherT>& rhs)
    {
        if (rhs.has_value())
        {
            this->construct(*rhs);
        }
    }

    template <typename OtherT, detail::enable_from_other<TypeT, OtherT, const OtherT&>* = nullptr,
              enable_if_t<!is_convertible<const OtherT&, TypeT>::value>* = nullptr>
    explicit optional(const optional<OtherT>& rhs)
    {
        if (rhs.has_value())
        {
            this->construct(*rhs);
        }
    }

    /// Converting move constructor.
    template <typename OtherT, detail::enable_from_other<TypeT, OtherT, OtherT&&>* = nullptr,
              enable_if_t<is_convertible<OtherT&&, TypeT>::value>* = nullptr>
    optional(optional<OtherT>&& rhs)
    {
        if (rhs.has_value())
        {
            this->construct(phi::move(*rhs));
        }
    }

    template <typename OtherT, detail::enable_from_other<TypeT, OtherT, OtherT&&>* = nullptr,
              enable_if_t<!is_convertible<OtherT&&, TypeT>::value>* = nullptr>
    explicit optional(optional<OtherT>&& rhs)
    {
        if (rhs.has_value())
        {
            this->construct(phi::move(*rhs));
        }
    }

    /// Destroys the stored value if there is one.
    ~optional() = default;

    /// Assignment to empty.
    ///
    /// Destroys the current value if there is one.
    optional& operator=(nullopt_t) noexcept
    {
        if (has_value())
        {
            this->m_Value.~TypeT();
            this->m_has_value = false;
        }

        return *this;
    }

    /// Copy assignment.
    ///
    /// Copies the value from `rhs` if there is one. Otherwise resets the stored
    /// value in `*this`.
    optional& operator=(const optional& rhs) = default;

    /// Move assignment.
    ///
    /// Moves the value from `rhs` if there is one. Otherwise resets the stored
    /// value in `*this`.
    optional& operator=(optional&& rhs) = default;

    /// Assigns the stored value from `u`, destroying the old value if there was
    /// one.
    template <typename OtherT = TypeT, detail::enable_assign_forward<TypeT, OtherT>* = nullptr>
    optional& operator=(OtherT&& other)
    {
        if (has_value())
        {
            this->m_Value = phi::forward<OtherT>(other);
        }
        else
        {
            this->construct(phi::forward<OtherT>(other));
        }

        return *this;
    }

    /// Converting copy assignment operator.
    ///
    /// Copies the value from `rhs` if there is one. Otherwise resets the stored
    /// value in `*this`.
    template <typename OtherT,
              detail::enable_assign_from_other<TypeT, OtherT, const OtherT&>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional& operator=(const optional<OtherT>& rhs)
    {
        if (has_value())
        {
            if (rhs.has_value())
            {
                this->m_Value = *rhs;
            }
            else
            {
                this->hard_reset();
            }
        }

        if (rhs.has_value())
        {
            this->construct(*rhs);
        }

        return *this;
    }

    // TODO check exception guarantee
    /// Converting move assignment operator.
    ///
    /// Moves the value from `rhs` if there is one. Otherwise resets the stored
    /// value in `*this`.
    template <typename OtherT, detail::enable_assign_from_other<TypeT, OtherT, OtherT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional& operator=(optional<OtherT>&& rhs)
    {
        if (has_value())
        {
            if (rhs.has_value())
            {
                this->m_Value = phi::move(*rhs);
            }
            else
            {
                this->hard_reset();
            }
        }

        if (rhs.has_value())
        {
            this->construct(phi::move(*rhs));
        }

        return *this;
    }

    /// Constructs the value in-place, destroying the current one if there is
    /// one.
    template <typename... ArgsT>
    PHI_EXTENDED_CONSTEXPR TypeT& emplace(ArgsT&&... args)
    {
        static_assert(is_constructible<TypeT, ArgsT&&...>::value,
                      "TypeT must be constructible with ArgsT");

        *this = nullopt;
        this->construct(phi::forward<ArgsT>(args)...);
        return value();
    }

    template <typename OtherT, typename... ArgsT>
    enable_if_t<is_constructible<TypeT, std::initializer_list<OtherT>&, ArgsT&&...>::value, TypeT&>
            PHI_EXTENDED_CONSTEXPR emplace(std::initializer_list<OtherT> il, ArgsT&&... args)
    {
        *this = nullopt;
        this->construct(il, phi::forward<ArgsT>(args)...);
        return value();
    }

    /// Swaps this optional with the other.
    ///
    /// If neither optionals have a value, nothing happens.
    /// If both have a value, the values are swapped.
    /// If one has a value, it is moved to the other and the movee is left
    /// valueless.
    PHI_EXTENDED_CONSTEXPR void swap(optional& rhs) noexcept(
            is_nothrow_move_constructible<TypeT>::value&& is_nothrow_swappable<TypeT>::value)
    {
        using phi::swap;
        if (has_value())
        {
            if (rhs.has_value())
            {
                swap(**this, *rhs);
            }
            else
            {
                new (phi::address_of(rhs.m_Value)) TypeT(phi::move(this->m_Value));
                this->m_Value.TypeT::~TypeT();
            }
        }
        else if (rhs.has_value())
        {
            new (phi::address_of(this->m_Value)) TypeT(phi::move(rhs.m_Value));
            rhs.m_Value.TypeT::~TypeT();
        }

        swap(this->m_has_value, rhs.m_has_value);
    }

    /// Returns a pointer to the stored value
    PHI_EXTENDED_CONSTEXPR TypeT* operator->()
    {
        return phi::address_of(this->m_Value);
    }

    PHI_EXTENDED_CONSTEXPR const TypeT* operator->() const
    {
        return phi::address_of(this->m_Value);
    }

    /// Returns the stored value
    PHI_EXTENDED_CONSTEXPR TypeT& operator*() &
    {
        return this->m_Value;
    }

    PHI_EXTENDED_CONSTEXPR const TypeT& operator*() const&
    {
        return this->m_Value;
    }

    PHI_EXTENDED_CONSTEXPR TypeT&& operator*() &&
    {
        return phi::move(this->m_Value);
    }

    PHI_EXTENDED_CONSTEXPR const TypeT&& operator*() const&&
    {
        return phi::move(this->m_Value);
    }

    /// Returns whether or not the optional has a value
    PHI_NODISCARD constexpr bool has_value() const noexcept
    {
        return this->m_has_value;
    }

    constexpr explicit operator bool() const noexcept
    {
        return this->m_has_value;
    }

    PHI_GCC_SUPPRESS_WARNING_PUSH()
    PHI_GCC_SUPPRESS_WARNING("-Wreturn-type")
    PHI_MSVC_SUPPRESS_WARNING_PUSH()
    PHI_MSVC_SUPPRESS_WARNING(4702) // unreachable code

    /// Returns the contained value if there is one
    PHI_EXTENDED_CONSTEXPR TypeT& value() &
    {
        if (has_value())
        {
            return this->m_Value;
        }

        PHI_ASSERT_NOT_REACHED();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const TypeT& value() const&
    {
        if (has_value())
        {
            return this->m_Value;
        }

        PHI_ASSERT_NOT_REACHED();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT&& value() &&
    {
        if (has_value())
        {
            return phi::move(this->m_Value);
        }

        PHI_ASSERT_NOT_REACHED();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const TypeT&& value() const&&
    {
        if (has_value())
        {
            return phi::move(this->m_Value);
        }

        PHI_ASSERT_NOT_REACHED();
    }

    PHI_MSVC_SUPPRESS_WARNING_POP()
    PHI_GCC_SUPPRESS_WARNING_POP()

    /// Returns the stored value if there is one, otherwise returns `u`
    template <typename OtherT>
    constexpr TypeT value_or(OtherT&& other) const&
    {
        static_assert(is_copy_constructible<TypeT>::value && is_convertible<OtherT&&, TypeT>::value,
                      "TypeT must be copy constructible and convertible from OtherT");

        return has_value() ? **this : static_cast<TypeT>(phi::forward<OtherT>(other));
    }

    template <typename OtherT>
    constexpr TypeT value_or(OtherT&& other) &&
    {
        static_assert(is_move_constructible<TypeT>::value && is_convertible<OtherT&&, TypeT>::value,
                      "TypeT must be move constructible and convertible from OtherT");

        return has_value() ? **this : static_cast<TypeT>(phi::forward<OtherT>(other));
    }

    /// Destroys the stored value if one exists, making the optional empty
    PHI_EXTENDED_CONSTEXPR void reset() noexcept
    {
        if (has_value())
        {
            this->m_Value.~TypeT();
            this->m_has_value = false;
        }
    }

/// Carries out some operation which returns an optional on the stored
/// object if there is one.
#    if PHI_HAS_FEATURE_DECLTYPE_AUTO()
    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto and_then(FuncT&& f) &
    {
        using result = invoke_result_t<FuncT, TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an optional");

        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) : result(nullopt);
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto and_then(FuncT&& f) &&
    {
        using result = invoke_result_t<FuncT, TypeT&&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an optional");

        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             result(nullopt);
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto and_then(FuncT&& f) const&
    {
        using result = invoke_result_t<FuncT, const TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an optional");

        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) : result(nullopt);
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto and_then(FuncT&& f) const&&
    {
        using result = invoke_result_t<FuncT, const TypeT&&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an optional");

        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             result(nullopt);
    }

    /// Carries out some operation on the stored object if there is one.
    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto map(FuncT&& f) &
    {
        return optional_map_impl(*this, phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto map(FuncT&& f) &&
    {
        return optional_map_impl(phi::move(*this), phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto map(FuncT&& f) const&
    {
        return optional_map_impl(*this, phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto map(FuncT&& f) const&&
    {
        return optional_map_impl(phi::move(*this), phi::forward<FuncT>(f));
    }

    /// Carries out some operation on the stored object if there is one.
    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto transform(FuncT&& f) &
    {
        return optional_map_impl(*this, phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto transform(FuncT&& f) &&
    {
        return optional_map_impl(phi::move(*this), phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto transform(FuncT&& f) const&
    {
        return optional_map_impl(*this, phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    PHI_EXTENDED_CONSTEXPR auto transform(FuncT&& f) const&&
    {
        return optional_map_impl(phi::move(*this), phi::forward<FuncT>(f));
    }
#    endif

    /// Calls `f` if the optional is empty
    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& f) &
    {
        if (has_value())
        {
            return *this;
        }

        phi::forward<FuncT>(f)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& f) &
    {
        return has_value() ? *this : phi::forward<FuncT>(f)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& f) &&
    {
        if (has_value())
        {
            return phi::move(*this);
        }

        phi::forward<FuncT>(f)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& f) &&
    {
        return has_value() ? phi::move(*this) : phi::forward<FuncT>(f)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& f) const&
    {
        if (has_value())
        {
            return *this;
        }

        phi::forward<FuncT>(f)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& f) const&
    {
        return has_value() ? *this : phi::forward<FuncT>(f)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& f) const&&
    {
        if (has_value())
        {
            return phi::move(*this);
        }

        phi::forward<FuncT>(f)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& f) const&&
    {
        return has_value() ? phi::move(*this) : phi::forward<FuncT>(f)();
    }

    /// Maps the stored value with `f` if there is one, otherwise returns `other`.
    template <typename FuncT, typename OtherT>
    PHI_EXTENDED_CONSTEXPR OtherT map_or(FuncT&& f, OtherT&& other) &
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) :
                             phi::forward<OtherT>(other);
    }

    template <typename FuncT, typename OtherT>
    PHI_EXTENDED_CONSTEXPR OtherT map_or(FuncT&& f, OtherT&& other) &&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             phi::forward<OtherT>(other);
    }

    template <typename FuncT, typename OtherT>
    PHI_EXTENDED_CONSTEXPR OtherT map_or(FuncT&& f, OtherT&& other) const&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) :
                             phi::forward<OtherT>(other);
    }

    template <typename FuncT, typename OtherT>
    PHI_EXTENDED_CONSTEXPR OtherT map_or(FuncT&& f, OtherT&& other) const&&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             phi::forward<OtherT>(other);
    }

    /// Maps the stored value with `f` if there is one, otherwise calls
    /// `other` and returns the result.
    template <typename FuncT, typename OtherT>
    PHI_EXTENDED_CONSTEXPR invoke_result_t<OtherT> map_or_else(FuncT&& f, OtherT&& other) &
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) :
                             phi::forward<OtherT>(other)();
    }

    template <typename FuncT, typename OtherT>
    PHI_EXTENDED_CONSTEXPR invoke_result_t<OtherT> map_or_else(FuncT&& f, OtherT&& other) &&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             phi::forward<OtherT>(other)();
    }

    template <typename FuncT, typename OtherT>
    PHI_EXTENDED_CONSTEXPR invoke_result_t<OtherT> map_or_else(FuncT&& f, OtherT&& other) const&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) :
                             phi::forward<OtherT>(other)();
    }

    template <typename FuncT, typename OtherT>
    PHI_EXTENDED_CONSTEXPR invoke_result_t<OtherT> map_or_else(FuncT&& f, OtherT&& other) const&&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             phi::forward<OtherT>(other)();
    }

    /// Returns `other` if `*this` has a value, otherwise an empty optional.
    template <typename OtherT>
    PHI_EXTENDED_CONSTEXPR optional<typename decay<OtherT>::type> conjunction(OtherT&& other) const
    {
        using result = optional<decay_t<OtherT>>;
        return has_value() ? result{other} : result{nullopt};
    }

    /// Returns `rhs` if `*this` is empty, otherwise the current value.
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR optional disjunction(const optional& rhs) &
    {
        return has_value() ? *this : rhs;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR optional disjunction(const optional& rhs) const&
    {
        return has_value() ? *this : rhs;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR optional disjunction(const optional& rhs) &&
    {
        return has_value() ? phi::move(*this) : rhs;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR optional disjunction(const optional& rhs) const&&
    {
        return has_value() ? phi::move(*this) : rhs;
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR optional disjunction(optional&& rhs) &
    {
        return has_value() ? *this : phi::move(rhs);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR optional disjunction(optional&& rhs) const&
    {
        return has_value() ? *this : phi::move(rhs);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR optional disjunction(optional&& rhs) &&
    {
        return has_value() ? phi::move(*this) : phi::move(rhs);
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR optional disjunction(optional&& rhs) const&&
    {
        return has_value() ? phi::move(*this) : phi::move(rhs);
    }

    /// Takes the value out of the optional, leaving it empty
    optional take()
    {
        optional ret = phi::move(*this);
        reset();
        return ret;
    }
};

PHI_CLANG_SUPPRESS_WARNING_PUSH()
PHI_CLANG_SUPPRESS_WARNING("-Wzero-as-null-pointer-constant")

/// Compares two optional objects
template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator==(const optional<TypeT>&  lhs,
                                                const optional<OtherT>& rhs)
{
    return lhs.has_value() == rhs.has_value() && (!lhs.has_value() || *lhs == *rhs);
}

template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator!=(const optional<TypeT>&  lhs,
                                                const optional<OtherT>& rhs)
{
    return lhs.has_value() != rhs.has_value() || (lhs.has_value() && *lhs != *rhs);
}

template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator<(const optional<TypeT>&  lhs,
                                               const optional<OtherT>& rhs)
{
    return rhs.has_value() && (!lhs.has_value() || *lhs < *rhs);
}

template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator>(const optional<TypeT>&  lhs,
                                               const optional<OtherT>& rhs)
{
    return lhs.has_value() && (!rhs.has_value() || *lhs > *rhs);
}

template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator<=(const optional<TypeT>&  lhs,
                                                const optional<OtherT>& rhs)
{
    return !lhs.has_value() || (rhs.has_value() && *lhs <= *rhs);
}

template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator>=(const optional<TypeT>&  lhs,
                                                const optional<OtherT>& rhs)
{
    return !rhs.has_value() || (lhs.has_value() && *lhs >= *rhs);
}

/// Compares an optional to a `nullopt`
template <typename TypeT>
PHI_ATTRIBUTE_PURE constexpr boolean operator==(const optional<TypeT>& lhs, nullopt_t) noexcept
{
    return !lhs.has_value();
}

template <typename TypeT>
PHI_ATTRIBUTE_PURE constexpr boolean operator==(nullopt_t, const optional<TypeT>& rhs) noexcept
{
    return !rhs.has_value();
}

template <typename TypeT>
PHI_ATTRIBUTE_PURE constexpr boolean operator!=(const optional<TypeT>& lhs, nullopt_t) noexcept
{
    return lhs.has_value();
}

template <typename TypeT>
PHI_ATTRIBUTE_PURE constexpr boolean operator!=(nullopt_t, const optional<TypeT>& rhs) noexcept
{
    return rhs.has_value();
}

template <typename TypeT>
PHI_ATTRIBUTE_PURE constexpr boolean operator<(const optional<TypeT>&, nullopt_t) noexcept
{
    return false;
}

template <typename TypeT>
PHI_ATTRIBUTE_PURE constexpr boolean operator<(nullopt_t, const optional<TypeT>& rhs) noexcept
{
    return rhs.has_value();
}

template <typename TypeT>
PHI_ATTRIBUTE_PURE constexpr boolean operator<=(const optional<TypeT>& lhs, nullopt_t) noexcept
{
    return !lhs.has_value();
}

template <typename TypeT>
PHI_ATTRIBUTE_PURE constexpr boolean operator<=(nullopt_t, const optional<TypeT>&) noexcept
{
    return true;
}

template <typename TypeT>
PHI_ATTRIBUTE_PURE constexpr boolean operator>(const optional<TypeT>& lhs, nullopt_t) noexcept
{
    return lhs.has_value();
}

template <typename TypeT>
PHI_ATTRIBUTE_PURE constexpr boolean operator>(nullopt_t, const optional<TypeT>&) noexcept
{
    return false;
}

template <typename TypeT>
PHI_ATTRIBUTE_PURE constexpr boolean operator>=(const optional<TypeT>&, nullopt_t) noexcept
{
    return true;
}

template <typename TypeT>
PHI_ATTRIBUTE_PURE constexpr boolean operator>=(nullopt_t, const optional<TypeT>& rhs) noexcept
{
    return !rhs.has_value();
}

/// Compares the optional with a value.
template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator==(const optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs == rhs : false;
}

template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator==(const OtherT& lhs, const optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs == *rhs : false;
}

template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator!=(const optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs != rhs : true;
}

template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator!=(const OtherT& lhs, const optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs != *rhs : true;
}

template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator<(const optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs < rhs : true;
}

template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator<(const OtherT& lhs, const optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs < *rhs : false;
}

template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator<=(const optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs <= rhs : true;
}

template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator<=(const OtherT& lhs, const optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs <= *rhs : false;
}

template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator>(const optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs > rhs : false;
}

template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator>(const OtherT& lhs, const optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs > *rhs : true;
}

template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator>=(const optional<TypeT>& lhs, const OtherT& rhs)
{
    return lhs.has_value() ? *lhs >= rhs : false;
}

template <typename TypeT, typename OtherT>
PHI_ATTRIBUTE_PURE constexpr boolean operator>=(const OtherT& lhs, const optional<TypeT>& rhs)
{
    return rhs.has_value() ? lhs >= *rhs : true;
}

PHI_CLANG_SUPPRESS_WARNING_POP()

template <typename TypeT, enable_if_t<is_move_constructible<TypeT>::value>* = nullptr,
          enable_if_t<is_swappable<TypeT>::value>* = nullptr>
void swap(optional<TypeT>& lhs, optional<TypeT>& rhs) noexcept(noexcept(lhs.swap(rhs)))
{
    return lhs.swap(rhs);
}

namespace detail
{
    struct i_am_secret
    {};
} // namespace detail

template <typename TypeT = detail::i_am_secret, typename OtherT,
          typename RetT =
                  conditional_t<is_same<TypeT, detail::i_am_secret>::value, decay_t<OtherT>, TypeT>>
inline constexpr optional<RetT> make_optional(OtherT&& v)
{
    return optional<RetT>(phi::forward<OtherT>(v));
}

template <typename TypeT, typename... ArgsT>
inline constexpr optional<TypeT> make_optional(ArgsT&&... args)
{
    return optional<TypeT>(in_place, phi::forward<ArgsT>(args)...);
}

template <typename TypeT, typename OtherT, typename... ArgsT>
inline constexpr optional<TypeT> make_optional(std::initializer_list<OtherT> il, ArgsT&&... args)
{
    return optional<TypeT>(in_place, il, phi::forward<ArgsT>(args)...);
}

#    if PHI_HAS_FEATURE_DEDUCTION_GUIDES()
template <typename TypeT>
optional(TypeT) -> optional<TypeT>;
#    endif

/// \exclude
namespace detail
{
#    if PHI_HAS_FEATURE_DECLTYPE_AUTO()
    template <typename OptT, typename FuncT,
              typename RetT = decltype(phi::invoke(phi::declval<FuncT>(), *phi::declval<OptT>())),
              enable_if_t<!is_void<RetT>::value>* = nullptr>
    PHI_EXTENDED_CONSTEXPR auto optional_map_impl(OptT&& opt, FuncT&& func)
    {
        return opt.has_value() ? phi::invoke(phi::forward<FuncT>(func), *phi::forward<OptT>(opt)) :
                                 optional<RetT>(nullopt);
    }

    template <typename OptT, typename FuncT,
              typename RetT = decltype(phi::invoke(phi::declval<FuncT>(), *phi::declval<OptT>())),
              enable_if_t<is_void<RetT>::value>* = nullptr>
    PHI_EXTENDED_CONSTEXPR auto optional_map_impl(OptT&& opt, FuncT&& func)
    {
        if (opt.has_value())
        {
            phi::invoke(phi::forward<FuncT>(func), *phi::forward<OptT>(opt));
            return make_optional(monostate{});
        }

        return optional<monostate>(nullopt);
    }
#    endif
} // namespace detail

/// Specialization for when `T` is a reference. `optional<T&>` acts similarly
/// to a `T*`, but provides more operations and shows intent more clearly.
template <typename TypeT>
class optional<TypeT&>
{
public:
    using this_type  = optional<TypeT&>;
    using value_type = TypeT&;

    /// Constructs an optional that does not contain a value.
    constexpr optional() noexcept
        : m_Value(nullptr)
    {}

    constexpr optional(nullopt_t) noexcept
        : m_Value(nullptr)
    {}

    /// Copy constructor
    ///
    /// If `rhs` contains a value, the stored value is direct-initialized with
    /// it. Otherwise, the constructed optional is empty.
    constexpr optional(const optional& rhs) noexcept = default;

    /// Move constructor
    ///
    /// If `rhs` contains a value, the stored value is direct-initialized with
    /// it. Otherwise, the constructed optional is empty.
    constexpr optional(optional&& rhs) = default;

    /// Constructs the stored value with `u`.
    template <typename OtherT                                            = TypeT,
              enable_if_t<!detail::is_optional<decay_t<OtherT>>::value>* = nullptr>
    constexpr optional(OtherT&& u) noexcept
        : m_Value(phi::address_of(u))
    {
        static_assert(is_lvalue_reference<OtherT>::value, "OtherT must be an lvalue");
    }

    template <typename OtherT>
    constexpr explicit optional(const optional<OtherT>& rhs) noexcept
        : optional(*rhs)
    {}

    /// No-op
    ~optional() = default;

    /// Assignment to empty.
    ///
    /// Destroys the current value if there is one.
    PHI_EXTENDED_CONSTEXPR optional& operator=(nullopt_t) noexcept
    {
        m_Value = nullptr;
        return *this;
    }

    /// Copy assignment.
    ///
    /// Rebinds this optional to the referee of `rhs` if there is one. Otherwise
    /// resets the stored value in `*this`.
    optional& operator=(const optional& rhs) = default;

    /// Rebinds this optional to `u`.
    template <typename OtherT                                            = TypeT,
              enable_if_t<!detail::is_optional<decay_t<OtherT>>::value>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional& operator=(OtherT&& u)
    {
        static_assert(is_lvalue_reference<OtherT>::value, "OtherT must be an lvalue");
        m_Value = phi::address_of(u);
        return *this;
    }

    /// Converting copy assignment operator.
    ///
    /// Rebinds this optional to the referee of `rhs` if there is one. Otherwise
    /// resets the stored value in `*this`.
    template <typename OtherT>
    PHI_EXTENDED_CONSTEXPR optional& operator=(const optional<OtherT>& rhs) noexcept
    {
        m_Value = phi::address_of(rhs.value());
        return *this;
    }

    /// Rebinds this optional to `u`.
    template <typename OtherT                                            = TypeT,
              enable_if_t<!detail::is_optional<decay_t<OtherT>>::value>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional& emplace(OtherT&& u) noexcept
    {
        return *this = phi::forward<OtherT>(u);
    }

    PHI_EXTENDED_CONSTEXPR void swap(optional& rhs) noexcept
    {
        swap(m_Value, rhs.m_Value);
    }

    /// Returns a pointer to the stored value
    PHI_EXTENDED_CONSTEXPR TypeT* operator->() noexcept
    {
        return m_Value;
    }

    PHI_EXTENDED_CONSTEXPR const TypeT* operator->() const noexcept
    {
        return m_Value;
    }

    /// Returns the stored value
    PHI_EXTENDED_CONSTEXPR TypeT& operator*() noexcept
    {
        return *m_Value;
    }

    PHI_EXTENDED_CONSTEXPR const TypeT& operator*() const noexcept
    {
        return *m_Value;
    }

    PHI_NODISCARD constexpr bool has_value() const noexcept
    {
        return m_Value != nullptr;
    }

    constexpr explicit operator bool() const noexcept
    {
        return m_Value != nullptr;
    }

    /// Returns the contained value if there is one, otherwise throws bad_optional_access
    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR TypeT& value()
    {
        if (has_value())
        {
            return *m_Value;
        }

        PHI_ASSERT_NOT_REACHED();
    }

    PHI_NODISCARD PHI_EXTENDED_CONSTEXPR const TypeT& value() const
    {
        if (has_value())
        {
            return *m_Value;
        }

        PHI_ASSERT_NOT_REACHED();
    }

    /// Returns the stored value if there is one, otherwise returns `u`
    template <typename OtherT>
    PHI_NODISCARD constexpr TypeT value_or(OtherT&& u) const& noexcept
    {
        static_assert(is_copy_constructible<TypeT>::value && is_convertible<OtherT&&, TypeT>::value,
                      "TypeT must be copy constructible and convertible from OtherT");

        return has_value() ? **this : static_cast<TypeT>(phi::forward<OtherT>(u));
    }

    /// \group value_or
    template <typename OtherT>
    PHI_NODISCARD constexpr TypeT value_or(OtherT&& u) && noexcept
    {
        static_assert(is_move_constructible<TypeT>::value && is_convertible<OtherT&&, TypeT>::value,
                      "TypeT must be move constructible and convertible from OtherT");

        return has_value() ? **this : static_cast<TypeT>(phi::forward<OtherT>(u));
    }

    /// Destroys the stored value if one exists, making the optional empty
    PHI_EXTENDED_CONSTEXPR void reset() noexcept
    {
        m_Value = nullptr;
    }

/// Carries out some operation which returns an optional on the stored
/// object if there is one.
#    if PHI_HAS_FEATURE_DECLTYPE_AUTO()
    template <typename FuncT>
    constexpr auto and_then(FuncT&& func) &
    {
        using result = invoke_result_t<FuncT, TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an optional");

        return has_value() ? phi::invoke(phi::forward<FuncT>(func), **this) : result(nullopt);
    }

    template <typename FuncT>
    constexpr auto and_then(FuncT&& f) &&
    {
        using result = invoke_result_t<FuncT, TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an optional");

        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) : result(nullopt);
    }

    template <typename FuncT>
    constexpr auto and_then(FuncT&& f) const&
    {
        using result = invoke_result_t<FuncT, const TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an optional");

        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) : result(nullopt);
    }

    template <typename FuncT>
    constexpr auto and_then(FuncT&& f) const&&
    {
        using result = invoke_result_t<FuncT, const TypeT&>;
        static_assert(detail::is_optional<result>::value, "FuncT must return an optional");

        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) : result(nullopt);
    }

    /// Carries out some operation on the stored object if there is one.
    template <typename FuncT>
    constexpr auto map(FuncT&& f) &
    {
        return detail::optional_map_impl(*this, phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto map(FuncT&& f) &&
    {
        return detail::optional_map_impl(phi::move(*this), phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto map(FuncT&& f) const&
    {
        return detail::optional_map_impl(*this, phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto map(FuncT&& f) const&&
    {
        return detail::optional_map_impl(phi::move(*this), phi::forward<FuncT>(f));
    }

    /// Carries out some operation on the stored object if there is one.
    template <typename FuncT>
    constexpr auto transform(FuncT&& f) &
    {
        return detail::optional_map_impl(*this, phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto transform(FuncT&& f) &&
    {
        return detail::optional_map_impl(phi::move(*this), phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto transform(FuncT&& f) const&
    {
        return detail::optional_map_impl(*this, phi::forward<FuncT>(f));
    }

    template <typename FuncT>
    constexpr auto transform(FuncT&& f) const&&
    {
        return detail::optional_map_impl(phi::move(*this), phi::forward<FuncT>(f));
    }
#    endif

    /// Calls `f` if the optional is empty
    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& f) &
    {
        if (has_value())
        {
            return *this;
        }

        phi::forward<FuncT>(f)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    constexpr optional<TypeT> or_else(FuncT&& f) &
    {
        return has_value() ? *this : phi::forward<FuncT>(f)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& f) &&
    {
        if (has_value())
        {
            return phi::move(*this);
        }

        phi::forward<FuncT>(f)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    constexpr optional<TypeT> or_else(FuncT&& f) &&
    {
        return has_value() ? phi::move(*this) : phi::forward<FuncT>(f)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    PHI_EXTENDED_CONSTEXPR optional<TypeT> or_else(FuncT&& f) const&
    {
        if (has_value())
        {
            return *this;
        }

        phi::forward<FuncT>(f)();
        return nullopt;
    }

#    if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    constexpr optional<TypeT> or_else(FuncT&& f) const&
    {
        return has_value() ? *this : phi::forward<FuncT>(f)();
    }

    template <typename FuncT, detail::enable_if_ret_void<FuncT>* = nullptr>
    constexpr optional<TypeT> or_else(FuncT&& f) const&&
    {
        if (has_value())
        {
            return phi::move(*this);
        }

        phi::forward<FuncT>(f)();
        return nullopt;
    }

    template <typename FuncT, detail::disable_if_ret_void<FuncT>* = nullptr>
    constexpr optional<TypeT> or_else(FuncT&& f) const&&
    {
        return has_value() ? phi::move(*this) : phi::forward<FuncT>(f)();
    }
#    endif

    /// Maps the stored value with `f` if there is one, otherwise returns `u`
    template <typename FuncT, typename OtherT>
    constexpr OtherT map_or(FuncT&& f, OtherT&& u) &
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) : phi::forward<OtherT>(u);
    }

    template <typename FuncT, typename OtherT>
    constexpr OtherT map_or(FuncT&& f, OtherT&& u) &&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             phi::forward<OtherT>(u);
    }

#    if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    template <typename FuncT, typename OtherT>
    constexpr OtherT map_or(FuncT&& f, OtherT&& u) const&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) : phi::forward<OtherT>(u);
    }

    template <typename FuncT, typename OtherT>
    constexpr OtherT map_or(FuncT&& f, OtherT&& u) const&&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             phi::forward<OtherT>(u);
    }
#    endif

    /// Maps the stored value with `f` if there is one, otherwise calls
    /// `u` and returns the result.
    template <typename FuncT, typename OtherT>
    constexpr invoke_result_t<OtherT> map_or_else(FuncT&& f, OtherT&& u) &
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) :
                             phi::forward<OtherT>(u)();
    }

    template <typename FuncT, typename OtherT>
    constexpr invoke_result_t<OtherT> map_or_else(FuncT&& f, OtherT&& u) &&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             phi::forward<OtherT>(u)();
    }

#    if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    template <typename FuncT, typename OtherT>
    constexpr invoke_result_t<OtherT> map_or_else(FuncT&& f, OtherT&& u) const&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), **this) :
                             phi::forward<OtherT>(u)();
    }

    template <typename FuncT, typename OtherT>
    constexpr invoke_result_t<OtherT> map_or_else(FuncT&& f, OtherT&& u) const&&
    {
        return has_value() ? phi::invoke(phi::forward<FuncT>(f), phi::move(**this)) :
                             phi::forward<OtherT>(u)();
    }
#    endif

    /// Returns `u` if `*this` has a value, otherwise an empty optional.
    template <typename OtherT>
    constexpr optional<typename decay<OtherT>::type> conjunction(OtherT&& u) const
    {
        using result = optional<decay_t<OtherT>>;
        return has_value() ? result{u} : result{nullopt};
    }

    /// Returns `rhs` if `*this` is empty, otherwise the current value.
    PHI_NODISCARD constexpr optional disjunction(const optional& rhs) &
    {
        return has_value() ? *this : rhs;
    }

    PHI_NODISCARD constexpr optional disjunction(const optional& rhs) &&
    {
        return has_value() ? phi::move(*this) : rhs;
    }

#    if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    PHI_NODISCARD constexpr optional disjunction(const optional& rhs) const&
    {
        return has_value() ? *this : rhs;
    }

    PHI_NODISCARD constexpr optional disjunction(const optional& rhs) const&&
    {
        return has_value() ? phi::move(*this) : rhs;
    }
#    endif

    PHI_NODISCARD constexpr optional disjunction(optional&& rhs) &
    {
        return has_value() ? *this : phi::move(rhs);
    }

    PHI_NODISCARD constexpr optional disjunction(optional&& rhs) &&
    {
        return has_value() ? phi::move(*this) : phi::move(rhs);
    }

#    if PHI_HAS_FEATURE_EXTENDED_CONSTEXPR()
    PHI_NODISCARD constexpr optional disjunction(optional&& rhs) const&
    {
        return has_value() ? *this : phi::move(rhs);
    }

    PHI_NODISCARD constexpr optional disjunction(optional&& rhs) const&&
    {
        return has_value() ? phi::move(*this) : phi::move(rhs);
    }
#    endif

    /// Takes the value out of the optional, leaving it empty
    PHI_EXTENDED_CONSTEXPR optional take()
    {
        optional ret = phi::move(*this);
        reset();
        return ret;
    }

private:
    TypeT* m_Value;
};

#else

#    include "phi/type_traits/false_t.hpp"

#    define PHI_HAS_WORKING_OPTIONAL() 0

DETAIL_PHI_BEGIN_NAMESPACE()

template <typename TypeT>
class optional
{
    static_assert(false_t<TypeT>::value, "phi::optional: Requires compiler support");
};

#endif

DETAIL_PHI_END_NAMESPACE()

DETAIL_PHI_BEGIN_STD_NAMESPACE()

// TODO SFINAE
template <typename TypeT>
struct hash<phi::optional<TypeT>>
{
    size_t operator()(const phi::optional<TypeT>& optional) const
    {
        if (!optional.has_value())
        {
            return 0;
        }

        return std::hash<phi::remove_const_t<TypeT>>()(optional.value());
    }
};

DETAIL_PHI_END_STD_NAMESPACE()

#endif // INCG_PHI_CORE_OPTIONAL_HPP
