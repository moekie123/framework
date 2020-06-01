#pragma once

// Design Patters
#include "StateMachine.h"
#include "Visitor.h"

// Third-Party
#include "tinyfsm.hpp"

/** Modules */
enum MODULES
{
        MOSQUITTO,
        ACTUATOR
};

/** StateMachine Types */
using MqttStateMachine = StateMachine<MODULES::MOSQUITTO>;
using ActuatorStateMachine = StateMachine<MODULES::ACTUATOR>;

using StateMachines = tinyfsm::FsmList<
    MqttStateMachine,
    ActuatorStateMachine>;

/** Visitor Types */
using MqttVisitor = Visitor<MODULES::MOSQUITTO>;
using ActuatorVisitor = Visitor<MODULES::ACTUATOR>;

