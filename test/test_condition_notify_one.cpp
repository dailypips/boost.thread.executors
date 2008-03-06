// Copyright (C) 2007 Anthony Williams
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/thread/detail/config.hpp>

#include <boost/thread/thread.hpp>

#include <boost/test/unit_test.hpp>

#include <libs/thread/test/util.inl>
#include "condition_test_common.hpp"

void do_test_condition_notify_one_wakes_from_wait()
{
    wait_for_flag data;
    
    boost::thread thread(bind(&wait_for_flag::wait_without_predicate, data));

    {
        boost::mutex::scoped_lock lock(data.mutex);
        data.flag=true;
        data.cond_var.notify_one();
    }

    thread.join();
    BOOST_CHECK(data.woken);
}

void do_test_condition_notify_one_wakes_from_wait_with_predicate()
{
    wait_for_flag data;
    
    boost::thread thread(bind(&wait_for_flag::wait_with_predicate, data));

    {
        boost::mutex::scoped_lock lock(data.mutex);
        data.flag=true;
        data.cond_var.notify_one();
    }

    thread.join();
    BOOST_CHECK(data.woken);
}

void do_test_condition_notify_one_wakes_from_timed_wait()
{
    wait_for_flag data;
    
    boost::thread thread(bind(&wait_for_flag::timed_wait_without_predicate, data));

    {
        boost::mutex::scoped_lock lock(data.mutex);
        data.flag=true;
        data.cond_var.notify_one();
    }

    thread.join();
    BOOST_CHECK(data.woken);
}

void do_test_condition_notify_one_wakes_from_timed_wait_with_predicate()
{
    wait_for_flag data;
    
    boost::thread thread(bind(&wait_for_flag::timed_wait_with_predicate, data));

    {
        boost::mutex::scoped_lock lock(data.mutex);
        data.flag=true;
        data.cond_var.notify_one();
    }

    thread.join();
    BOOST_CHECK(data.woken);
}

void do_test_condition_notify_one_wakes_from_relative_timed_wait_with_predicate()
{
    wait_for_flag data;
    
    boost::thread thread(bind(&wait_for_flag::relative_timed_wait_with_predicate, data));

    {
        boost::mutex::scoped_lock lock(data.mutex);
        data.flag=true;
        data.cond_var.notify_one();
    }

    thread.join();
    BOOST_CHECK(data.woken);
}

void test_condition_notify_one()
{
    timed_test(&do_test_condition_notify_one_wakes_from_wait, timeout_seconds, execution_monitor::use_mutex);
    timed_test(&do_test_condition_notify_one_wakes_from_wait_with_predicate, timeout_seconds, execution_monitor::use_mutex);
    timed_test(&do_test_condition_notify_one_wakes_from_timed_wait, timeout_seconds, execution_monitor::use_mutex);
    timed_test(&do_test_condition_notify_one_wakes_from_timed_wait_with_predicate, timeout_seconds, execution_monitor::use_mutex);
    timed_test(&do_test_condition_notify_one_wakes_from_relative_timed_wait_with_predicate, timeout_seconds, execution_monitor::use_mutex);
}


boost::unit_test_framework::test_suite* init_unit_test_suite(int, char*[])
{
    boost::unit_test_framework::test_suite* test =
        BOOST_TEST_SUITE("Boost.Threads: condition test suite");

    test->add(BOOST_TEST_CASE(&test_condition_notify_one));

    return test;
}