#pragma once
#include <unordered_map>
#include <typeindex>
#include <functional>
#include <cstdint>


namespace events {
    class EventBase;

    class EventManager {
    protected:
        using _key_t    = std::type_index;
        using _func_t   = std::function<void ( const EventBase & )>;
        template <class C> 
        using _cfunc_t  = void (C:: *) (const EventBase &);

        using _desc_t   = std::uint64_t;
        using _calls_t  = std::unordered_map<_desc_t, _func_t>;
    public:
        template <typename T>
        void subscribe(const _func_t &/* callback */);
        template <typename T>
        void unsubscribe(const _func_t &/* callback */);
        
        template <typename T, class C>
        void subscribe(const _cfunc_t<C> &/* callback */, C */* p_inst */);
        template <typename T, class C>
        void unsubscribe(const _cfunc_t<C> &/* callback */, const C */* p_inst */);
        
        void invoke( const EventBase & ) const;
    private:
        void _subscribe_impl( const _key_t &/* event_desc */, const _desc_t &/* callb_desc */, const _func_t &/* callback */ );
        void _unsubscribe_impl( const _key_t &/* event_desc */, const _desc_t &/* callback_desc */ );

        static _desc_t _get_fdesc( const _func_t &/* callback */ );

        template <class C>
        static _desc_t _get_fdesc( const _cfunc_t<C> /* callback */, const C */* inst */ );

        template <typename T>
        static _key_t _get_key();

        static _key_t _get_key( const EventBase * /* event */);
    protected:
        std::unordered_map< _key_t, _calls_t > subscribers_;
    };
}

#include "eventmanager.ipp"

// eventmanager.hpp
