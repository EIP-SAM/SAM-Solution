#include "TestAFunctionality.hpp"

//
// Test entry function
//
TestAFunctionality::TestAFunctionality()
{
}


//
// Test if the QObject is threaded, return NULL if not
//
void TestAFunctionality::TestStart()
{
	BasicAFunctionality *threadedFunctionality = new BasicAFunctionality((AFunctionality::eClientId)100, true);
	QSignalSpy ThreadedStartSpy(threadedFunctionality, SIGNAL(start()));
	QSignalSpy ThreadedRunSpy(threadedFunctionality, SIGNAL(run()));
	threadedFunctionality->start();
	QTest::qWait(1000);
	QCOMPARE(ThreadedStartSpy.count(), 1);
	QCOMPARE(ThreadedRunSpy.count(), 1);
	QCOMPARE(threadedFunctionality->isRunning(), true);

	BasicAFunctionality *nonThreadedFunctionality = new BasicAFunctionality((AFunctionality::eClientId)200, false);
	QSignalSpy NonThreadedStartSpy(nonThreadedFunctionality, SIGNAL(start()));
	QSignalSpy NonThreadedRunSpy(nonThreadedFunctionality, SIGNAL(run()));
	nonThreadedFunctionality->start();
	QTest::qWait(1000);
	QCOMPARE(NonThreadedStartSpy.count(), 1);
	QCOMPARE(NonThreadedRunSpy.count(), 1);
	QCOMPARE(nonThreadedFunctionality->isRunning(), true);

}

void TestAFunctionality::TestStop()
{
	BasicAFunctionality *threadedFunctionality = new BasicAFunctionality((AFunctionality::eClientId)100, true);
	threadedFunctionality->start();
	QSignalSpy threadedStopSpy(threadedFunctionality, SIGNAL(stop()));
	QTest::qWait(1000);
	threadedFunctionality->stop();
	QTest::qWait(1000);
	QCOMPARE(threadedStopSpy.count(), 1);
	QCOMPARE(threadedFunctionality->isRunning(), false);

	BasicAFunctionality *nonThreadedFunctionality = new BasicAFunctionality((AFunctionality::eClientId)200, false);
	nonThreadedFunctionality->start();
	QSignalSpy nonThreadedStopSpy(nonThreadedFunctionality, SIGNAL(stop()));
	QTest::qWait(1000);
	nonThreadedFunctionality->stop();
	QTest::qWait(1000);
	QCOMPARE(nonThreadedStopSpy.count(), 1);
	QCOMPARE(nonThreadedFunctionality->isRunning(), false);

	BasicAFunctionality *NonStartFunctionality = new BasicAFunctionality((AFunctionality::eClientId)100, true);
	QSignalSpy nonStartedThreadedStopSpy(NonStartFunctionality, SIGNAL(stop()));
	QTest::qWait(1000);
	threadedFunctionality->stop();
	QTest::qWait(1000);
	QCOMPARE(nonStartedThreadedStopSpy.count(), 0);
	QCOMPARE(NonStartFunctionality->isRunning(), false);
}

QTEST_MAIN(TestAFunctionality)

#include "TestAFunctionality.moc"