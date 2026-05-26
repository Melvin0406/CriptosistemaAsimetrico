#include <iostream>
#include <fstream>
#include "libraries/json.hpp"
#include "libraries/actor/actor.h"

int main()
{
    // Crear actores
    Actor SenderActor("Sender");
    Actor ReceiverActor("Receiver");

    SenderActor.generateMessage("Vanessa", ReceiverActor.getName(), ReceiverActor.getPublicKey());

    return 0;
}