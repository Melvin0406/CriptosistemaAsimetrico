#include <iostream>
#include <fstream>
#include <filesystem>
#include "libraries/json.hpp"
#include "libraries/actor/actor.h"

int main()
{
    // Crear actores
    Actor SenderActor("Sender");
    Actor ReceiverActor("Receiver");

    // Caso valido
    std::cout << "\n\nCaso valido\n";
    SenderActor.generateMessage("Vanessa", ReceiverActor.getName(), ReceiverActor.getPublicKey());
    std::filesystem::rename("jsons/message.json", "jsons/message_valid.json");
    ReceiverActor.readMessage(0, "jsons/message_valid.json");
    std::cout << "\n\n-------------------------------------------------------------------------------------\n";


    // Caso firma alterada
    std::cout << "\n\nCaso firma alterada\n";
    SenderActor.generateMessage("Miranda", ReceiverActor.getName(), ReceiverActor.getPublicKey());

    std::ifstream fileIn4("jsons/message.json");
    nlohmann::json package4;
    fileIn4 >> package4;
    fileIn4.close();

    // Modificar manualmente la firma
    package4["signature"] = package4["signature"].get<uint64_t>() + 1;

    std::ofstream fileOut4("jsons/message.json");
    fileOut4 << package4.dump(4);
    fileOut4.close();

    std::filesystem::rename("jsons/message.json", "jsons/message_signature_corr.json");
    ReceiverActor.readMessage(0, "jsons/message_signature_corr.json");
    std::cout << "\n\n-------------------------------------------------------------------------------------\n";


    // Caso campo firma eliminado
    std::cout << "\n\nCaso campo firma eliminado\n";
    SenderActor.generateMessage("Lopez", ReceiverActor.getName(), ReceiverActor.getPublicKey());

    std::ifstream fileIn7("jsons/message.json");
    nlohmann::json package7;
    fileIn7 >> package7;
    fileIn7.close();

    // Eliminar campo de firma
    package7.erase("signature");

    std::ofstream fileOut7("jsons/message.json");
    fileOut7 << package7.dump(4);
    fileOut7.close();

    std::cout << "\n";
    std::filesystem::rename("jsons/message.json", "jsons/message_signature_elim.json");
    ReceiverActor.readMessage(0, "jsons/message_signature_elim.json");
    std::cout << "\n\n-------------------------------------------------------------------------------------\n";

    return 0;
}