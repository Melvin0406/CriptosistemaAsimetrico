#include <iostream>
#include "libraries/actor/actor.h"

int main()
{
    // Create sender and receiver
    Actor SenderActor("Sender");
    Actor ReceiverActor("Receiver");

    // Send message
    SenderActor.generateMessage("Shrek", ReceiverActor.getName(), ReceiverActor.getPublicKey());

    // Read message
    ReceiverActor.readMessage();

    return 0;
}