#ifndef KLV_DEMANGLE__
#define KLV_DEMANGLE__

#include <klv/common.hpp>
#include <memory>
#include <string>

#ifdef __GNUC__
#include <cstdlib>
#include <cxxabi.h>
#define KLV_HAS_DEMANGLE
#endif

namespace klv {

constexpr bool has_demangle() noexcept {
#ifdef KLV_HAS_DEMANGLE
    return true;
#else
    return false;
#endif
}

// Note: this is also defined by clang and icc
#ifdef __GNUC__

/**
 * This implementation is adapted from the solution here:
 *
 *  http://stackoverflow.com/questions/281818/unmangling-the-result-of-stdtype-infoname
 */
inline std::string demangle(const char *name) {
    int status = -1;
    std::unique_ptr<char, void(*)(void*)> uptr {
        abi::__cxa_demangle(name, NULL, NULL, &status),
        std::free
    };
    return status == 0 ? uptr.get() : name;
}

#else
// TODO: support demangle for non-GCC compilers
inline std::string demangle(const char *name) {
    return name;
}
#endif

template<class T>
inline std::string type_name() {
    return demangle(typeid(T).name());
}

template<class T>
inline std::string type_name(const T&) {
    return type_name<T>();
}

} // end namespace klv

#endif
