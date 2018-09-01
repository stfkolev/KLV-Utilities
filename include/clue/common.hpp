#ifndef KLV_COMMON__
#define KLV_COMMON__

#include <klv/config.hpp>
#include <cassert>
#include <cstddef>
#include <stdexcept>
#include <type_traits>

#ifndef CHAR_BIT
#define CHAR_BIT 8
#endif

// to turn KLV_ASSERT into no-op, one can pre-define KLV_NDEBUG
//
#ifndef KLV_NDEBUG
#define KLV_ASSERT(cond) assert(cond)
#else
#define KLV_ASSERT(cond)
#endif


#if defined(__GNUC__)
#define KLV_LIKELY(x)   (__builtin_expect((x), 1))
#define KLV_UNLIKELY(x) (__builtin_expect((x), 0))
#else
#define KLV_LIKELY(x)   (x)
#define KLV_UNLIKELY(x) (x)
#endif

#define KLV_REQUIRE(...) typename std::enable_if<(__VA_ARGS__), int>::type = 0

namespace klv {

using ::std::size_t;
using ::std::ptrdiff_t;

}

#endif
