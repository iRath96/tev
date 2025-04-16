#include "rpc_common.hpp"

namespace rpc {

class RemoteObject {
protected:
    struct carg {};

    void* m_remotePtr;
    RemoteObject(carg) {}

public:
    explicit RemoteObject(void* ptr) : m_remotePtr(ptr) {}
    void* remotePointer() const { return m_remotePtr; }
};

class Client {
    wstream w;

public:
    std::function<packet (packet)> send;

    packet receive(packet packet) {
        rpc_printf("[client] received a packet with %d bytes\n", int(packet.size));
        
        rstream r { packet };
        uint8_t msgtype = r.read_raw<uint8_t>();
        if (msgtype != RPC_MSGTYPE_CALL) {
            rpc_printf("[client] invalid msgtype %d\n", msgtype);
            return { .data = &RPC_MSGTYPE_ERROR, .size = 1 };
        }

        const auto id = reader<uint32_t>()(r);
        rpc_printf("  [client] should call %u\n", id);

        auto reg = w.functions[id];

        w.clear();
        reg->apply(r, w);
        return w.packet();
    }

    template<typename R, typename C, typename... Args>
    remote_t<R> call(std::string fnName, bool isConst, const C &c, remote_t<Args>... args) {
        fnName = isConst ?
            typeinfo<R (C::*)(Args...) const>::decl(fnName) :
            typeinfo<R (C::*)(Args...)>::decl(fnName);
        rpc_printf("[client] call function '%s'\n", fnName.c_str());
        w.clear();
        w.write_raw(RPC_MSGTYPE_CALL);
        writeArgument(fnName);
        writeArgument(c);
        (writeArgument(args), ...);
        auto response = send(packet { w.data.data(), w.data.size() });
        rstream r { response };
        uint8_t msgtype = r.read_raw<uint8_t>();
        if (msgtype != RPC_MSGTYPE_RETURN) {
            rpc_printf("[client] invalid msgtype %d\n", msgtype);
        }
        if constexpr (std::is_void_v<R>)
            return;
        else
            return reader<remote_t<R>>()(r);
    }

    template<typename R, typename... Args>
    remote_t<R> construct(std::string fnName, remote_t<Args>... args) {
        fnName += "(" + typeinfo_variadic<Args...>::name() + ")";
        rpc_printf("[client] call constructor '%s'\n", fnName.c_str());
        w.clear();
        w.write_raw(RPC_MSGTYPE_CALL);
        writeArgument(fnName);
        (writeArgument(args), ...);
        auto response = send(packet { w.data.data(), w.data.size() });
        rstream r { response };
        uint8_t msgtype = r.read_raw<uint8_t>();
        if (msgtype != RPC_MSGTYPE_RETURN) {
            rpc_printf("[client] invalid msgtype %d\n", msgtype);
        }
        return reader<remote_t<R>>()(r);
    }

private:
    template<typename T>
    void writeArgument(T t) {
        rpc_printf("  [client] write called with '%s'\n", typeinfo<T>::name().c_str());
        writer<T>()(w, t);
    }
};

inline Client client;

}

#define BEGIN_SUBCLASS(C, P) class C; \
TYPE(C); \
template<> struct rpc::remote<C*> { using type = C; }; \
template<> struct rpc::remote<const C*> { using type = C; }; \
class C : public P { \
    using Class = C; \
    using Parent = P; \
    static std::string className() { return #C; } \
protected: \
    C(carg c) : P(c) {} \
public: \
    C(void *ptr) : P(ptr) {} \
    C* operator->() { return this; } \
    operator void*() const { return m_remotePtr; }
#define BEGIN_CLASS(C) BEGIN_SUBCLASS(C, rpc::RemoteObject)
#define END_CLASS() };

#define CONSTRUCTOR0(M) static M make() { \
    return rpc::client.construct<M*>(className() + "::" #M); }
#define CONSTRUCTOR1(M, A) static M make(rpc::remote_t<A> a) { \
    return rpc::client.construct<M*, A>(className() + "::" #M, a); }
#define CONSTRUCTOR2(M, A, B) static M make(rpc::remote_t<A> a, rpc::remote_t<B> b) { \
    return rpc::client.construct<M*, A, B>(className() + "::" #M, a, b); }
#define CONSTRUCTOR3(M, A, B, C) static M make(rpc::remote_t<A> a, rpc::remote_t<B> b, rpc::remote_t<C> c) { \
    return rpc::client.construct<M*, A, B, C>(className() + "::" #M, a, b, c); }
#define CONSTRUCTOR4(M, A, B, C, D) static M make(rpc::remote_t<A> a, rpc::remote_t<B> b, rpc::remote_t<C> c, rpc::remote_t<D> d) { \
    return rpc::client.construct<M*, A, B, C, D>(className() + "::" #M, a, b, c, d); }
#define CONSTRUCTOR5(M, A, B, C, D, E) static M make(rpc::remote_t<A> a, rpc::remote_t<B> b, rpc::remote_t<C> c, rpc::remote_t<D> d, rpc::remote_t<E> e) { \
    return rpc::client.construct<M*, A, B, C, D, E>(className() + "::" #M, a, b, c, d, e); }

#define METHOD0(R, M) rpc::remote_t<R> M() { \
    return rpc::client.call<R, Class>(className() + "::" #M, false, *this); }
#define METHOD1(R, M, A) rpc::remote_t<R> M(rpc::remote_t<A> a) { \
    return rpc::client.call<R, Class, A>(className() + "::" #M, false, *this, a); }
#define METHOD2(R, M, A, B) rpc::remote_t<R> M(rpc::remote_t<A> a, rpc::remote_t<B> b) { \
    return rpc::client.call<R, Class, A, B>(className() + "::" #M, false, *this, a, b); }

#define CONST_METHOD0(R, M) rpc::remote_t<R> M() const { \
    return rpc::client.call<R, Class>(className() + "::" #M, true, *this); }
#define CONST_METHOD1(R, M, A) rpc::remote_t<R> M(rpc::remote_t<A> a) const { \
    return rpc::client.call<R, Class, A>(className() + "::" #M, true, *this, a); }
#define CONST_METHOD2(R, M, A, B) rpc::remote_t<R> M(rpc::remote_t<A> a, rpc::remote_t<B> b) const { \
    return rpc::client.call<R, Class, A, B>(className() + "::" #M, true, *this, a, b); }
