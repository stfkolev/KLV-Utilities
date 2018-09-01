// to ensure <klv/klv.hpp> is correct

#include <klv/klv.hpp>
#include <klv/klv.hpp>   // ensure duplicated inclusion is ok

// ensure that all headers are actually included

// misc
using klv::_;
using klv::pass;
using klv::index_sequence;
using klv::apply;

// predicates
using klv::eq;
using klv::chars::is_digit;
using klv::chars::is_space;
using klv::floats::is_inf;
using klv::floats::is_nan;

// memory
using klv::aligned_alloc;
using klv::aligned_free;

// array_view
using klv::array_view;

// formatting
using klv::cfmt;
using klv::sstr;

// meta
using klv::meta::type_;

// meta_seq
using klv::meta::seq_;

// optional
using klv::optional;

// reindexed_view
using klv::reindexed_view;

// string_view
using klv::string_view;

// mparser
using klv::mparser;

// fast_vector
using klv::fast_vector;

// ordered_dict
using klv::ordered_dict;

// keyed_vector
using klv::keyed_vector;

// stringex
using klv::trim;
using klv::foreach_token_of;

// timing
using klv::stop_watch;
using klv::calibrated_time;

// type_traits
using klv::enable_if_t;

// value_range
using klv::value_range;

// string_view
using klv::string_view;

// textio
using klv::read_file_content;
using klv::line_stream;

// type_name
using klv::demangle;
using klv::type_name;

// shared_mutex
using klv::shared_mutex;
using klv::shared_timed_mutex;
using klv::shared_lock;

// concurrent_queue
using klv::concurrent_queue;

// concurrent_counter
using klv::concurrent_counter;

// thread_pool
using klv::thread_pool;

int main() {
    return 0;
}
