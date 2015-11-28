#include "BasicAFunctionality.hpp"

//
// Constructor and destructor
//
BasicAFunctionality::BasicAFunctionality(AFunctionality::eClientId clientId, bool threaded) : AFunctionality(clientId, threaded)
{
}

BasicAFunctionality::~BasicAFunctionality()
{
}

//
// Emit signal to TestAFunctionalitiesManager
//
void BasicAFunctionality::_run()
{
    emit TestRunStarted();
}
