#include "eventmanager.hpp"
#include "event.hpp"

#include <stdexcept>


void events::EventManager::_subscribe_impl(const _key_t &event_desc, const _desc_t &callb_desc, const _func_t &callback)
{
    subscribers_[event_desc][callb_desc] = callback;
}

void events::EventManager::_unsubscribe_impl(const _key_t &event_desc, const _desc_t &callback_desc)
{
    try {
        subscribers_.at(event_desc).erase(callback_desc);
    }
    catch (std::out_of_range exc) {
        return;
    }
}

void events::EventManager::invoke( const EventBase &event ) const {
    const auto key = _get_key(&event);
    if ( subscribers_.find(key) == subscribers_.end() )
        return;

    const auto bucket = subscribers_.at(key);
    for ( const auto &callback : bucket ) {
        callback.second(event);
    }
}

events::EventManager::_desc_t events::EventManager::_get_fdesc(const _func_t &callback)
{
    const auto fptr = callback.target<void (const EventBase &)>();
    return std::hash<void *>() ( * reinterpret_cast< void ** > (fptr) );
}

events::EventManager::_key_t events::EventManager::_get_key( const EventBase * vptr ) {
    return std::type_index(typeid(*vptr));
}

// eventmanager.cpp
