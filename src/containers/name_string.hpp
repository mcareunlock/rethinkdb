#ifndef CONTAINERS_NAME_STRING_HPP_
#define CONTAINERS_NAME_STRING_HPP_

#include <string>

#include "http/json/json_adapter.hpp"
#include "rpc/serialize_macros.hpp"

// The kind of string that can only contain either the empty string or acceptable names for
// things.  You may only assign non-empty strings.

class name_string_t {
public:
    // Initializes to the empty string.
    name_string_t();

    // Succeeds on valid non-empty strings.
    MUST_USE bool assign_value(const std::string& s);

    const std::string& str() const { return str_; }

    bool empty() const { return str_.empty(); }  // TODO(1253): get rid of this.
    const char *c_str() const { return str_.c_str(); }  // TODO(1253): get rid of this.

    RDB_MAKE_ME_SERIALIZABLE_1(str_);

    static const char *const valid_char_msg;

private:
    std::string str_;
};

inline bool operator==(const name_string_t& x, const name_string_t& y) {
    return x.str() == y.str();
}

inline bool operator!=(const name_string_t& x, const name_string_t& y) {
    return !(x == y);
}

inline bool operator<(const name_string_t& x, const name_string_t& y) {
    return x.str() < y.str();
}

// ctx-less json adapter concept for name_string_t
json_adapter_if_t::json_adapter_map_t get_json_subfields(name_string_t *target);
cJSON *render_as_json(name_string_t *target);
void apply_json_to(cJSON *change, name_string_t *target);
void on_subfield_change(name_string_t *);

void debug_print(append_only_printf_buffer_t *buf, const name_string_t& s);



#endif  // CONTAINERS_NAME_STRING_HPP_
