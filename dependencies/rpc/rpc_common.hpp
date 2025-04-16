#include <string>
#include <functional>
#include <cassert>
#include <cstring>

// #define rpc_printf(...)
#define rpc_printf(...) printf(__VA_ARGS__)

namespace rpc {

inline uint8_t RPC_MSGTYPE_CALL   = 71;
inline uint8_t RPC_MSGTYPE_RETURN = 72;
inline uint8_t RPC_MSGTYPE_ERROR  = 73;

template<typename T>
struct remote {
    static_assert(false, "type not supported");
};

#define RAW(T) template<> struct remote<T> { using type = T; };
RAW(void)
RAW(bool)
RAW(std::string)
RAW(int16_t)
RAW(int32_t)
RAW(int64_t)
RAW(uint16_t)
RAW(uint32_t)
RAW(uint64_t)
#undef RAW

template<typename T> struct remote<const T&> { using type = T; };

template<typename T>
using remote_t = remote<T>::type;

struct packet {
    const uint8_t *data;
    size_t size;
};

// MARK: typeinfo
template<typename T>
struct typeinfo {
    static std::string name() { return std::string("/") + typeid(T).name(); }
    static std::string decl(std::string var) { return name() + " " + var; }
};

// Variadic template specialization
template<typename... Types>
struct typeinfo_variadic;

template<typename T>
struct typeinfo<const T> {
    static std::string name() { return "const " + typeinfo<T>::name(); }
    static std::string decl(std::string var) { return "const " + typeinfo<T>::name() + " " + var; }
};

// MARK: References
template<typename T>
struct typeinfo<T&> {
    static std::string name() { return typeinfo<T>::name() + "&"; }
    static std::string decl(std::string var) { return typeinfo<T>::name() + "& " + var; }
};

// MARK: Pointers
template<typename T>
struct typeinfo<T*> {
    static std::string name() { return typeinfo<T>::name() + "*"; }
    static std::string decl(std::string var) { return typeinfo<T>::name() + "* " + var; }
};

// MARK: Member functions
template<typename C, typename R, typename... Args>
struct typeinfo<R (C::*)(Args...)> {
    static std::string name() { return typeinfo<R>::name() + " (" + typeinfo<C>::name() + "::*)(" + typeinfo_variadic<Args...>::name() + ")"; }
    static std::string decl(std::string var) { return typeinfo<R>::name() + " " + var + "(" + typeinfo_variadic<Args...>::name() + ")"; }
};
template<typename C, typename R, typename... Args>
struct typeinfo<R (C::*)(Args...) const> {
    static std::string name() { return typeinfo<R>::name() + " (" + typeinfo<C>::name() + "::*)(" + typeinfo_variadic<Args...>::name() + ") const"; }
    static std::string decl(std::string var) { return typeinfo<R>::name() + " " + var + "(" + typeinfo_variadic<Args...>::name() + ") const"; }
};

// MARK: std::function
template<typename R, typename... Args>
struct typeinfo<std::function<R (Args...)>> {
    static std::string name() { return "std::function<" + typeinfo<R>::name() + "(" + typeinfo_variadic<Args...>::name() + ")>"; }
    static std::string decl(std::string var) { return name() + " " + var; }
};

// MARK: typeinfo_variadic

// Specialization for at least one type
template<typename First, typename... Rest>
struct typeinfo_variadic<First, Rest...> {
    static std::string name() {
        return typeinfo<First>::name() + (sizeof...(Rest) > 0 ? ", " + typeinfo_variadic<Rest...>::name() : "");
    }
};

// Specialization for zero types (empty case)
template<>
struct typeinfo_variadic<> {
    static std::string name() { return ""; }
};

// MARK: rstream
struct rstream {
    const uint8_t* data;
    size_t index;
    size_t size;

    rstream(packet packet) {
        data = packet.data;
        size = packet.size;
        index = 0;
    }

    void read_binary(void* dst, size_t readSize) {
        memcpy(dst, data + index, readSize);
        index += readSize;
    }

    template<typename T>
    T read_raw() {
        T result;
        read_binary(static_cast<void*>(&result), sizeof(T));
        return result;
    }
};

template<typename T>
struct reader {
    T operator()(rstream &s) {
        return { s.read_raw<void*>() };
    }
};

#define RAW(T) template<> struct reader<T> { auto operator()(rstream &s) { return s.read_raw<T>(); } };
template<> struct reader<void> { void operator()(rstream &) {} };
RAW(bool)
RAW(int16_t)
RAW(int32_t)
RAW(int64_t)
RAW(uint16_t)
RAW(uint32_t)
RAW(uint64_t)
#undef RAW

template<> struct reader<std::string> {
    std::string operator()(rstream &s) {
        const uint32_t length = s.read_raw<uint32_t>();
        char* buffer = (char*)malloc(length);
        s.read_binary(buffer, length);
        std::string result(buffer, length);
        free(buffer);
        return result;
    }
};

// MARK: wstream
struct wstream {
    struct erased_function {
        virtual void apply(rstream &r, wstream &w) = 0;
        virtual ~erased_function() = default;
    };
    std::vector<std::shared_ptr<erased_function>> functions;

    std::vector<uint8_t> data;
    packet packet() const {
        return {
            .data = data.data(),
            .size = data.size(),
        };
    }

    void clear() {
        data.clear();
    }

    void write_binary(const void* src, size_t size) {
        const size_t i = data.size();
        data.resize(i + size);
        memcpy(data.data() + i, src, size);
    }

    template<typename T>
    void write_raw(T t) {
        write_binary(static_cast<const void*>(&t), sizeof(T));
    }
};

template<typename T>
struct writer {
    void operator()(wstream &s, T v) {
        s.write_raw(v.remotePointer());
    }
};

#define RAW(T) template<> struct writer<T> { void operator()(wstream &s, T v) { return s.write_raw(v); } };
template<> struct writer<void> { void operator()(wstream &) {} };
RAW(bool)
RAW(int16_t)
RAW(int32_t)
RAW(int64_t)
RAW(uint16_t)
RAW(uint32_t)
RAW(uint64_t)
#undef RAW

template<> struct writer<std::string> {
    void operator()(wstream &s, std::string v) {
        s.write_raw((uint32_t)v.length());
        s.write_binary(v.c_str(), v.length());
    }
};

template<typename R, typename ...Args>
struct writer<std::function<R (Args...)>> {
    typedef std::function<R (Args...)> F;

    struct fn : public wstream::erased_function {
        F f;
        fn(F f) : f(f) {}

        void apply(rstream &r, wstream &w) override {
            rpc_printf("[writer] calling '%s'\n", typeinfo<F>::name().c_str());
            if constexpr (std::is_void_v<R>)
                f(reader<Args>()(r)...);
            else
                writer<R>()(w, f(reader<Args>()(r)...));
        }
    };

    void operator()(wstream &s, std::function<R (Args...)> f) {
        const auto id = uint32_t(s.functions.size());
        rpc_printf("[writer] creating '%s' with id %u\n", typeinfo<F>::name().c_str(), id);
        s.functions.push_back(std::make_shared<fn>(f));
        s.write_raw(id);
    }
};

}

#define TYPE(T) template<> struct rpc::typeinfo<T> { \
    static std::string name() { return #T; } \
    static std::string decl(std::string var) { return #T " " + var; } \
};
TYPE(void)
TYPE(bool)
TYPE(int16_t)
TYPE(int32_t)
TYPE(int64_t)
TYPE(uint16_t)
TYPE(uint32_t)
TYPE(uint64_t)
TYPE(std::string)

#define RPC_ENUM(T, Int) \
template<> struct rpc::typeinfo<T> { \
    static std::string name() { return #T; } \
    static std::string decl(std::string var) { return #T " " + var; } \
}; \
template<> struct rpc::reader<T> { \
    auto operator()(rpc::rstream &s) { return T(s.read_raw<Int>()); } \
}; \
template<> struct rpc::writer<T> { \
    void operator()(wstream &s, T v) { return s.write_raw(Int(v)); } \
}; \
template<> struct rpc::remote<T> { using type = T; };
