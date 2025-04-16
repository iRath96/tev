#include "rpc_common.hpp"

#include <unordered_map>

namespace rpc {

template<typename T>
struct reader<T *> {
    T *operator()(rstream &s) {
        auto ptr = s.read_raw<T *>();
        rpc_printf("    [server] ptr: %p\n", ptr);
        return ptr;
    }
};

template<typename T>
struct writer<T *> {
    void operator()(wstream &s, T *t) {
        s.write_raw(t);
    }
};

struct RegistrarBase {
    using Registry = std::unordered_map<std::string, RegistrarBase *>;
    static Registry& registry() {
        static Registry registry {};
        return registry;
    }

    virtual void apply(rstream &r, wstream &w) = 0;

private:
    template<typename T>
    std::decay_t<T> readArgument(rstream &r) {
        rpc_printf("  [server] read called %s => %s\n", typeinfo<T>::name().c_str(), typeinfo<std::decay_t<T>>::name().c_str());
        return reader<std::decay_t<T>>()(r);
    }

    template <typename R, typename C, typename... Args>
    void call(R (C::*function)(Args...), rstream &r, wstream &w) {
        w.write_raw(RPC_MSGTYPE_RETURN);
        if constexpr (std::is_void_v<R>)
            (*readArgument<C*>(r).*function)(readArgument<Args>(r)...);
        else
            writer<std::decay_t<R>>()(w, (*readArgument<C*>(r).*function)(readArgument<Args>(r)...));
    }

    template <typename R, typename C, typename... Args>
    void call(R (C::*function)(Args...) const, rstream &r, wstream &w) {
        w.write_raw(RPC_MSGTYPE_RETURN);
        if constexpr (std::is_void_v<R>)
            (*readArgument<const C*>(r).*function)(readArgument<Args>(r)...);
        else
            writer<std::decay_t<R>>()(w, (*readArgument<const C*>(r).*function)(readArgument<Args>(r)...));
    }

    template <typename C, typename... Args>
    void construct(rstream &r, wstream &w) {
        w.write_raw(RPC_MSGTYPE_RETURN);
        writer<C*>()(w, new C(readArgument<Args>(r)...));
    }
};

class Server {
    wstream w;

public:
#ifdef _WIN32
    using socket_t = SOCKET;
#else
    using socket_t = int;
#endif

    socket_t client;

    std::function<packet (socket_t, packet)> send;

    packet receive(packet packet) {
        rpc_printf("[server] received a packet with %d bytes\n", int(packet.size));

        rstream r { packet };
        uint8_t msgtype = r.read_raw<uint8_t>();
        if (msgtype != RPC_MSGTYPE_CALL) {
            rpc_printf("[server] invalid msgtype %d\n", msgtype);
            return { .data = &RPC_MSGTYPE_ERROR, .size = 1 };
        }

        const auto signature = reader<std::string>()(r);
        rpc_printf("  [server] should call %s\n", signature.c_str());

        auto reg = RegistrarBase::registry().find(signature);
        if (reg == RegistrarBase::registry().end()) {
            rpc_printf("  [server] could not find method!\n");
            return { .data = &RPC_MSGTYPE_ERROR, .size = 1 };
        }

        w.clear();
        reg->second->apply(r, w);
        return w.packet();
    }
};

inline Server server;

template<typename R, typename ...Args>
struct reader<std::function<R (Args...)>> {
    typedef std::function<R (Args...)> F;
    F operator()(rstream &s) {
        const auto id = s.read_raw<uint32_t>();
        rpc_printf("[reader] creating '%s' with id %u\n", typeinfo<F>::name().c_str(), id);
        auto owner = server.client;
        return [=](Args... args) {
            rpc_printf("[reader] calling '%s' with id %u\n", typeinfo<F>::name().c_str(), id);

            wstream w;
            w.write_raw(RPC_MSGTYPE_CALL);
            writer<uint32_t>()(w, id);
            (writer<Args>()(w, args), ...);

            auto response = server.send(owner, packet { w.data.data(), w.data.size() });
            rstream r { response };
            uint8_t msgtype = r.read_raw<uint8_t>();
            if (msgtype != RPC_MSGTYPE_RETURN) {
                rpc_printf("[server] invalid msgtype %d\n", msgtype);
            }
            return reader<R>()(r);
        };
    }
};

template<typename FnPointer>
struct Registrar : public RegistrarBase {
    FnPointer ptr;

    Registrar(std::string name, FnPointer ptr) : ptr(ptr) {
        const auto signature = typeinfo<FnPointer>::decl(name);
        rpc_printf("[server] registered function '%s'\n", signature.c_str());
        registry()[signature] = this;
    }

    void apply(rstream &r, wstream &w) override { call(ptr, r, w); }
};

template<typename Class, typename ...Args>
struct ConstructorRegistrar : public RegistrarBase{
    ConstructorRegistrar(std::string name) {
        const auto signature = name + "(" + typeinfo_variadic<Args...>::name() + ")";
        rpc_printf("[server] registered constructor '%s'\n", signature.c_str());
        registry()[signature] = this;
    }

    void apply(rstream &r, wstream &w) override { construct<Class, Args...>(r, w); }
};

}

#define CONCAT(a, b) CONCAT_INNER(a, b)
#define CONCAT_INNER(a, b) a ## b
#define UNIQUE_NAME(base) CONCAT(base, __LINE__)

#define BEGIN_CLASS(C) TYPE(C) \
namespace Register ## C { \
    using Class = C; \
    static std::string className = #C;
#define BEGIN_SUBCLASS(C, P) BEGIN_CLASS(C)
#define END_CLASS() }

#define CONSTRUCTOR0(M) rpc::ConstructorRegistrar<M> UNIQUE_NAME(con) { className + "::"#M };
#define CONSTRUCTOR1(M, A) rpc::ConstructorRegistrar<M, A> UNIQUE_NAME(con) { className + "::"#M };
#define CONSTRUCTOR2(M, A, B) rpc::ConstructorRegistrar<M, A, B> UNIQUE_NAME(con) { className + "::"#M };
#define CONSTRUCTOR3(M, A, B, C) rpc::ConstructorRegistrar<M, A, B, C> UNIQUE_NAME(con) { className + "::"#M };
#define CONSTRUCTOR4(M, A, B, C, D) rpc::ConstructorRegistrar<M, A, B, C, D> UNIQUE_NAME(con) { className + "::"#M };
#define CONSTRUCTOR5(M, A, B, C, D, E) rpc::ConstructorRegistrar<M, A, B, C, D, E> UNIQUE_NAME(con) { className + "::"#M };

#define METHOD0(R, M) rpc::Registrar<R (Class::*)()> UNIQUE_NAME(reg) { className + "::"#M, &Class::M };
#define METHOD1(R, M, A) rpc::Registrar<R (Class::*)(A)> UNIQUE_NAME(reg) { className + "::"#M, &Class::M };
#define METHOD2(R, M, A, B) rpc::Registrar<R (Class::*)(A, B)> UNIQUE_NAME(reg) { className + "::"#M, &Class::M };

#define CONST_METHOD0(R, M) rpc::Registrar<R (Class::*)() const> UNIQUE_NAME(reg) { className + "::"#M, &Class::M };
#define CONST_METHOD1(R, M, A) rpc::Registrar<R (Class::*)(A) const> UNIQUE_NAME(reg) { className + "::"#M, &Class::M };
#define CONST_METHOD2(R, M, A, B) rpc::Registrar<R (Class::*)(A, B) const> UNIQUE_NAME(reg) { className + "::"#M, &Class::M };
