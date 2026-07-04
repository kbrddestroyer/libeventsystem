#include "eventmanager.hpp"


template <typename T>
inline void events::EventManager::subscribe(const _func_t &callback) {
    const auto event_desc = _get_key<T>();
    const auto callb_desc = _get_fdesc(callback);

    _subscribe_impl(event_desc, callb_desc, callback);
}

template <typename T>
inline void events::EventManager::unsubscribe(const _func_t &callback) {
    const auto event_desc = _get_key<T>();
    const auto callb_desc = _get_fdesc(callback);

    _unsubscribe_impl(event_desc, callb_desc);
}

template <typename T, class C>
inline void events::EventManager::subscribe(const _cfunc_t<C> &callback, C *p_inst)
{
    const auto event_desc = _get_key<T>();
    const auto callb_desc = _get_fdesc<C>(callback, p_inst);
    _subscribe_impl(event_desc, callb_desc, [p_inst, callback]( const EventBase & event ) { (p_inst->*callback)(event); } );
}

template <typename T, class C>
inline void events::EventManager::unsubscribe(const _cfunc_t<C> &callback, const C *p_inst)
{
    const auto event_desc = _get_key<T>();
    const auto callb_desc = _get_fdesc<C>(callback, p_inst);
    _unsubscribe_impl(event_desc, callb_desc);
}

template <typename T>
inline events::EventManager::_key_t events::EventManager::_get_key()
{
    return std::type_index(typeid(T));
}

template <class C>
events::EventManager::_desc_t events::EventManager::_get_fdesc( const _cfunc_t<C> callback, const C *inst ) {
    // TODO: This will result in hash collision if we try to subscribe more than one member function to the same manager instance
    return std::hash<void *>() (const_cast<C *>(inst));
}


// eventmanager.ipp
