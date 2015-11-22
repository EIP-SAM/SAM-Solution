//
// Constructor
//
TestAFunctionality::TestAFunctionality()
{
}

//
// Test the start signal for the functionality weither it is
// threaded or not
//
void TestAFunctionality::TestStart()
{
	BasicAFunctionality *threadedFunctionality(
		(AFunctionality::eClientId)1,
		true);

	QSignalSpy threadedStartSpy(threadedFunctionality, start());
	threadedFunctionality->start();
	QTest::qWait(300);
	QCOMPARE(threadedStartSpy.count(), 1);

	BasicAFunctionality *nonThreadedFunctionality(
		(AFunctionality::eClientId)2,
		false);

	QSignalSpy nonThreadedStartSpy(nonThreadedFunctionality, start());
	threadedFunctionality->start();
	QTest::qWait(300);
	QCOMPARE(nonThreadedStartSpy.count(), 1);
}


//
// Test the stop signal for the case if the functionality is :
// - Threaded and started
// - Not threaded and started
// - Not started
//
void TestAFunctionality::TestStop()
{
	BasicAFunctionality *startedThreadedFunctionality(
		(AFunctionality::eClientId)1,
		true);

	QSignalSpy startedThreadedStopSpy(
		startedThreadedFunctionality,
		isRunning());
	startedThreadedFunctionality->start();
	QTest::qWait(300);
	startedThreadedFunctionality->stop();
	QTest::qWait(300);
	QCOMPARE(startedThreadedStopSpy.count(), 1);

	BasicAFunctionality *startedNonThreadedFunctionality(
		(AFunctionality::eClientId)1,
		false);

	QSignalSpy startedNonThreadedStopSpy(
		startedNonThreadedFunctionality,
		isRunning());
	startedNonThreadedFunctionality->start();
	QTest::qWait(300);
	startedNonThreadedFunctionality->stop();
	QTest::qWait(300);
	QCOMPARE(startedNonThreadedStopSpy.count(), 1);

	BasicAFunctionality *nonStartedFunctionality(
		(AFunctionality::eClientId)1,
		true);

	QSignalSpy nonStartedStopSpy(nonStartedFunctionality, isRunning());
	nonStartedFunctionality->stop();
	QTest::qWait(300);
	QCOMPARE(nonStartedStopSpy.count(), 0);
}

QTEST_MAIN(TestAFunctionality)

#include "TestAFunctionality.moc"