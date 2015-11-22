#ifndef BASICAFUNCTIONALITY_HPP
# define BASICAFUNCTIONALITY_HPP

# include "AFunctionality.hpp"

//
// Test class of an basic functionality
//

class BasicAFunctionality : public AFunctionality {
	Q_OBJECT

public:
	BasicAFunctionality(AFunctionality::eClientId clientId, bool threaded = true);
	virtual ~BasicAFunctionality();

protected slots:
	virtual void _run();

signals:
	void TestRunStarted();
};

#endif // !BASICAFUNCTIONALITY_HPP