#ifndef KLV_PREDICATES__
#define KLV_PREDICATES__

#include <klv/preproc.hpp>
#include <cmath>
#include <cctype>
#include <cwctype>

namespace klv {

#define KLV_DEFINE_COMPARISON_PREDICATE(fname, op) \
    template<typename T> \
    struct fname##_t { \
        T value; \
        template<typename X> \
        bool operator()(const X& x) const noexcept { \
            return x op value; \
        } \
    }; \
    template<typename T> \
    inline fname##_t<T> fname(const T& x) { \
        return fname##_t<T>{x}; \
    }

KLV_DEFINE_COMPARISON_PREDICATE(eq, ==)
KLV_DEFINE_COMPARISON_PREDICATE(ne, !=)
KLV_DEFINE_COMPARISON_PREDICATE(ge, >=)
KLV_DEFINE_COMPARISON_PREDICATE(gt, >)
KLV_DEFINE_COMPARISON_PREDICATE(le, <=)
KLV_DEFINE_COMPARISON_PREDICATE(lt, <)

template<class Container>
struct in_t {
    const Container& values_;

    template<typename X>
    bool operator()(const X& x) const {
        auto it = values_.begin();
        auto it_end = values_.end();
        for (; it != it_end; ++it) {
            if (x == *it) return true;
        }
        return false;
    }
};

template<>
struct in_t<const char*> {
    const char* chs;

    bool operator()(char c) const noexcept {
        const char *p = chs;
        while (*p) {
            if (c == *p) return true;
            p++;
        }
        return false;
    }

    bool operator()(wchar_t c) const noexcept {
        const char *p = chs;
        while (*p) {
            if (c == static_cast<wchar_t>(*p)) return true;
            p++;
        }
        return false;
    }
};

template<class Container>
inline in_t<Container> in(const Container& values) {
    return in_t<Container>{values};
}

inline in_t<const char*> in(const char* chs) {
    return in_t<const char*>{chs};
}

template<typename T>
struct in_range_t {
    const T left;
    const T right;

    in_range_t(const T& l, const T& r)
        : left(l), right(r) {}

    bool operator()(const T& x) const {
        return x >= left && x <= right;
    }
};

template<typename T>
inline in_range_t<T> in_range(const T& l, const T& r) {
    return in_range_t<T>(l, r);
}


// Compound predicates

template<class... Preds> struct and_pred_t;
template<class... Preds> struct or_pred_t;

#define KLV_PREDICATE_TPARAM_(n) class P##n
#define KLV_PREDICATE_TARG_(n) P##n
#define KLV_PREDICATE_FIELDDEF_(n) P##n p##n
#define KLV_PREDICATE_PREDTERM_(n) p##n(x)

#define KLV_DEFINE_AND_PREDS(N) \
    template<KLV_TERMLIST_##N(KLV_PREDICATE_TPARAM_)> \
    struct and_pred_t<KLV_TERMLIST_##N(KLV_PREDICATE_TARG_)> { \
        KLV_STMTLIST_##N(KLV_PREDICATE_FIELDDEF_) \
        template<typename X> \
        bool operator()(const X& x) const noexcept { \
            return KLV_GENEXPR_##N(KLV_PREDICATE_PREDTERM_, &&); \
        } \
    };

#define KLV_DEFINE_OR_PREDS(N) \
    template<KLV_TERMLIST_##N(KLV_PREDICATE_TPARAM_)> \
    struct or_pred_t<KLV_TERMLIST_##N(KLV_PREDICATE_TARG_)> { \
        KLV_STMTLIST_##N(KLV_PREDICATE_FIELDDEF_) \
        template<typename X> \
        bool operator()(const X& x) const noexcept { \
            return KLV_GENEXPR_##N(KLV_PREDICATE_PREDTERM_, ||); \
        } \
    };

KLV_DEFINE_AND_PREDS(1)
KLV_DEFINE_AND_PREDS(2)
KLV_DEFINE_AND_PREDS(3)
KLV_DEFINE_AND_PREDS(4)
KLV_DEFINE_AND_PREDS(5)
KLV_DEFINE_AND_PREDS(6)
KLV_DEFINE_AND_PREDS(7)
KLV_DEFINE_AND_PREDS(8)
KLV_DEFINE_AND_PREDS(9)

KLV_DEFINE_OR_PREDS(1)
KLV_DEFINE_OR_PREDS(2)
KLV_DEFINE_OR_PREDS(3)
KLV_DEFINE_OR_PREDS(4)
KLV_DEFINE_OR_PREDS(5)
KLV_DEFINE_OR_PREDS(6)
KLV_DEFINE_OR_PREDS(7)
KLV_DEFINE_OR_PREDS(8)
KLV_DEFINE_OR_PREDS(9)

template<class... Preds>
inline and_pred_t<Preds...> and_(const Preds&... preds) {
    return and_pred_t<Preds...>{preds...};
}

template<class... Preds>
inline or_pred_t<Preds...> or_(const Preds&... preds) {
    return or_pred_t<Preds...>{preds...};
}

// Predicates for chars

namespace chars {

template<class P1, class P2>
struct either_t {
    P1 p1;
    P2 p2;

    bool operator()(char c) const noexcept {
        return p1(c) || p2(c);
    }

    bool operator()(wchar_t c) const noexcept {
        return p1(c) || p2(c);
    }
};

template<class P1, class P2>
inline either_t<P1, P2> either(P1 p1, P2 p2) {
    return either_t<P1, P2>{p1, p2};
}

#define KLV_DEFINE_CHAR_PREDICATE(cname, sfun, wfun) \
    struct cname##_t { \
        bool operator()(char c) const noexcept { \
            return std::sfun(c); \
        } \
        bool operator()(wchar_t c) const noexcept { \
            return std::wfun(c); \
        } \
    }; \
    constexpr cname##_t cname{};

KLV_DEFINE_CHAR_PREDICATE(is_space, isspace, iswspace)
KLV_DEFINE_CHAR_PREDICATE(is_blank, isblank, iswblank)
KLV_DEFINE_CHAR_PREDICATE(is_digit, isdigit, iswdigit)
KLV_DEFINE_CHAR_PREDICATE(is_alpha, isalpha, iswalpha)
KLV_DEFINE_CHAR_PREDICATE(is_alnum, isalnum, iswalnum)
KLV_DEFINE_CHAR_PREDICATE(is_punct, ispunct, iswpunct)
KLV_DEFINE_CHAR_PREDICATE(is_upper, isupper, iswupper)
KLV_DEFINE_CHAR_PREDICATE(is_lower, islower, iswlower)
KLV_DEFINE_CHAR_PREDICATE(is_xdigit, isxdigit, iswxdigit)

} // end namespace chars


// Predicates for floating point numbers

namespace floats {

#define KLV_DEFINE_FLOAT_PREDICATE(cname, fun) \
    struct cname##_t { \
        bool operator()(double x) const noexcept { \
            return std::fun(x); \
        } \
        bool operator()(float x) const noexcept { \
            return std::fun(x); \
        } \
        bool operator()(long double x) const noexcept { \
            return std::fun(x); \
        } \
    }; \
    constexpr cname##_t cname{};

KLV_DEFINE_FLOAT_PREDICATE(is_inf, isinf)
KLV_DEFINE_FLOAT_PREDICATE(is_nan, isnan)
KLV_DEFINE_FLOAT_PREDICATE(is_finite, isfinite)

} // end namespace floats

} // end namespace klv

#endif
