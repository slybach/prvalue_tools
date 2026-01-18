#ifndef prvalue_tools_hpp
#define prvalue_tools_hpp

#define PRT_LIFT(...)                   \
::prt::details::lifted{                 \
    [&] noexcept(noexcept(__VA_ARGS__)) \
        -> decltype((__VA_ARGS__))      \
    {                                   \
        return (__VA_ARGS__);           \
    }                                   \
}

namespace prt
{
    namespace details
    {
        template <typename F>
        struct lifted
        {
            F lambda;
            using expression_type = decltype(lambda());
            // should this conversion be restricted to rvalues?
            // intended usage is "only" as a stand-in for an expression
            // which might only be valid "once"
            // though once lifted, this lifted object will typically be
            // an lvalue unless forwarded/moved...
            constexpr operator expression_type () const
            {
                return lambda();
            }
        };
    }
}

#endif
