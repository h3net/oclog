#ifndef THREADTEST_H_
#define THREADTEST_H_

#include <iostream>
#include <cppunit/TestFixture.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Log.h"
#include "Sink.h"
#include "FileSink.h"
#include "CerrSink.h"
#include "macros.h"
#include "ScribeSink.h"
#include <boost/thread.hpp>

using namespace std;
using namespace oc::log;

class ThreadTest: public CppUnit::TestFixture
{
public:

	void setUp()
	{

	}

	void tearDown()
	{

	}

	void threadCerr(std::string cat, int timeout)
	{
		sleep(timeout);
		Log<CerrSink>::getLevel() = DEBUG;
		OC_LOG(CerrSink,cat,DEBUG)
		<< "Hello world 2";
		OC_LOG(CerrSink,cat,ALERT)
		<< "Hello world 3";
	}

	void testThreadCerr()
	{

		boost::thread_group threads;

		for (int i = 0 ; i < 100 ; i++) {
			threads.add_thread(new boost::thread(&ThreadTest::threadCerr, this, "Test", i % 20));
		}

		threads.join_all();

	}

	void threadFile(std::string cat, int timeout)
	{
		sleep(timeout);
		OC_LOG(FileSink,"test2",DEBUG)
		<< "Hello world 4";
		Log<FileSink>("test2", "other.log").get() << "Hello World 5";
		Log<FileSink>("test2").get() << "Hello World 6";
		OC_LOG(FileSink,"test2",DEBUG)
		<< "Hello world 7";
		OC_LOG(FileSink,"test2",DEBUG)
		<< "Hello world 8";
		OC_LOG(FileSink,"test2",DEBUG)
		<< "Hello world 9";
		Log<FileSink>::getLevel() = ERROR;
		OC_LOG(FileSink,"test2",DEBUG)
		<< "Hello world 10";
		OC_LOG(FileSink,"test2",DEBUG)
		<< "Hello world 11";
		OC_LOG(FileSink,"test2",DEBUG)
		<< "Hello world 12";
	}

	void testThreadFile()
	{
		boost::thread_group threads;

		for (int i = 0 ; i < 2000 ; i++) {
			threads.add_thread(new boost::thread(&ThreadTest::threadFile, this, "Test", 0));
		}

		threads.join_all();

	}

	void threadScribe(std::string cat, int timeout)
	{
		cout << "new thread" << endl;
		sleep(timeout);
		Log<ScribeSink>("test3").get() << "Hello World";
		OC_LOG(ScribeSink, "test4", DEBUG)
		<< "Test test";
	}

	void testThreadScribe()
	{
		boost::thread_group threads;

		for (int i = 0 ; i < 1000 ; i++) {
			threads.add_thread(new boost::thread(&ThreadTest::threadScribe, this, "Test", i % 3));
		}

		threads.join_all();

	}

	void testScribeLog()
	{
	}

CPPUNIT_TEST_SUITE(ThreadTest);
//	CPPUNIT_TEST(testThreadCerr);
//		CPPUNIT_TEST(testThreadFile);
		CPPUNIT_TEST(testThreadScribe);

	CPPUNIT_TEST_SUITE_END();

};

#endif /* THREADTEST_H_ */
