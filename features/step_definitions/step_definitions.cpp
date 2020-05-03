#include "mocks/MockParameter.h"
#include "mocks/MockConfigurator.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cucumber-cpp/autodetect.hpp>

using cucumber::ScenarioScope;

struct ParameterCtx
{
	int x;
};

GIVEN("^the trigger to initialize the framework$")
{
    ScenarioScope<ParameterCtx> context;
    context->x = 1;
}

WHEN("^the IsStarted signal has ben envoked$")
{
    ScenarioScope<ParameterCtx> context;

}

THEN("^the framework is running$") 
{
	ScenarioScope<ParameterCtx> context;
	EXPECT_EQ( context->x, 1 );
}

GIVEN("^the trigger to terminate the framework$")
{
    ScenarioScope<ParameterCtx> context;
    context->x = 1;
}

WHEN("^the IsStopped signal has ben envoked$")
{
    ScenarioScope<ParameterCtx> context;

}

THEN("^the framework is stopped$") 
{
	ScenarioScope<ParameterCtx> context;
	EXPECT_EQ( context->x, 1 );
}
