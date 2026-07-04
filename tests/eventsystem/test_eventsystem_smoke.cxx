#include <gtest/gtest.h>
#include <libeventsystem/eventsystem.hpp>
#include <typeindex>


namespace {
    class TestEvent : public events::EventBase {
        public:
        mutable int invokes_ = 0;
        int data_;
    };

    void callback( const events::EventBase &data ) {
        ASSERT_EQ(static_cast<const TestEvent&>( data ).data_, 3);
        static_cast<const TestEvent&>( data ).invokes_++;
    }

    void callback2( const events::EventBase &data ) {
        static_cast<const TestEvent&>( data ).invokes_++;
    }
}

TEST(test_smoke, test_smoke_subscribe) {
    events::EventManager g_mgr;

    g_mgr.subscribe<TestEvent>(callback);
    TestEvent event;
    event.data_ = 3;
    g_mgr.invoke(event);

    ASSERT_GT(event.invokes_, 0);
}

TEST(test_smoke, test_smoke_classmember) {
    class Subscriber {
        public:
        unsigned int calls_ = 0;

        void callback (const events::EventBase &event) {
            calls_ ++;
        }
    };

    events::EventManager g_mgr;
    Subscriber inst, inst2;
    g_mgr.subscribe<TestEvent, Subscriber>( &Subscriber::callback, &inst );
    TestEvent event;
    g_mgr.invoke(event);
    ASSERT_EQ(inst.calls_, 1);
    ASSERT_EQ(inst2.calls_, 0);
}

TEST(test_smoke, test_unsubscribe) {
    events::EventManager g_mgr;

    g_mgr.subscribe<TestEvent>(callback);
    g_mgr.subscribe<TestEvent>(callback2);
    TestEvent event;
    event.data_ = 3;
    g_mgr.invoke(event);

    ASSERT_EQ(event.invokes_, 2);

    g_mgr.unsubscribe<TestEvent>(callback);
    g_mgr.invoke(event);
    ASSERT_EQ(event.invokes_, 3);
}


TEST(test_smoke, test_unsubscribe_classmember) {
    class Subscriber {
        public:
        unsigned int calls_ = 0;

        void callback (const events::EventBase &event) {
            calls_ ++;
        }
    };

    events::EventManager g_mgr;
    Subscriber inst, inst2;
    g_mgr.subscribe<TestEvent, Subscriber>( &Subscriber::callback, &inst );
    g_mgr.subscribe<TestEvent, Subscriber>( &Subscriber::callback, &inst2 );
    TestEvent event;
    g_mgr.invoke(event);
    ASSERT_EQ(inst.calls_, 1);
    ASSERT_EQ(inst2.calls_, 1);
    g_mgr.unsubscribe<TestEvent, Subscriber>( &Subscriber::callback, &inst2 );

    g_mgr.invoke(event);
    ASSERT_EQ(inst.calls_, 2);
    ASSERT_EQ(inst2.calls_, 1);
}
