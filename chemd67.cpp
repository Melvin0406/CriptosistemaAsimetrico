#include <iostream>
#include <fstream>
#include "libraries/json.hpp"
#include "libraries/actor/actor.h"

int main()
{
    // Create sender and receiver
    Actor SenderActor("Chemo");
    Actor ReceiverActor("Melvin");


    // CASO 1 - Mensaje valido enviado del emisor al receptor
    std::cout << "\n\nCASO 1 - Mensaje valido enviado del emisor al receptor\n";
    SenderActor.generateMessage("Adomination", ReceiverActor.getName(), ReceiverActor.getPublicKey());
    ReceiverActor.readMessage(0);
    std::cout << "\n\n-------------------------------------------------------------------------------------\n";


    // CASO 2 - Mensaje vacio
    std::cout << "\n\nCASO 2 - Mensaje vacio\n";
    SenderActor.generateMessage("", ReceiverActor.getName(), ReceiverActor.getPublicKey());
    ReceiverActor.readMessage(0);
    std::cout << "\n\n-------------------------------------------------------------------------------------\n";


    // CASO 3 - Mensaje alterado despues de haber sido firmado
    std::cout << "\n\nCASO 3 - Mensaje alterado despues de haber sido firmado\n";
    SenderActor.generateMessage("Fermin", ReceiverActor.getName(), ReceiverActor.getPublicKey());

    std::ifstream fileIn3("jsons/message.json");
    nlohmann::json package3;
    fileIn3 >> package3;
    fileIn3.close();

    // Modificar manualmente el mensaje (cambiar primer caracter del hex)
    std::string em3 = package3["encrypted_message"].get<std::string>();
    if (!em3.empty()) em3[0] = (em3[0] == 'f') ? '0' : em3[0] + 1;
    package3["encrypted_message"] = em3;

    std::ofstream fileOut3("jsons/message.json");
    fileOut3 << package3.dump(4);
    fileOut3.close();

    ReceiverActor.readMessage(0);
    std::cout << "\n\n-------------------------------------------------------------------------------------\n";


    // CASO 4 - Firma alterada manualmente dentro del JSON
    std::cout << "\n\nCASO 4 - Firma alterada manualmente dentro del JSON\n";
    SenderActor.generateMessage("Convivio", ReceiverActor.getName(), ReceiverActor.getPublicKey());

    std::ifstream fileIn4("jsons/message.json");
    nlohmann::json package4;
    fileIn4 >> package4;
    fileIn4.close();

    // Modificar manualmente la firma
    package4["signature"] = package4["signature"].get<uint64_t>() + 1;

    std::ofstream fileOut4("jsons/message.json");
    fileOut4 << package4.dump(4);
    fileOut4.close();

    ReceiverActor.readMessage(0);
    std::cout << "\n\n-------------------------------------------------------------------------------------\n";


    // CASO 5 - Intento de verificacion con una llave publica incorrecta
    std::cout << "\n\nCASO 5 - Intento de verificacion con una llave publica incorrecta\n";
    SenderActor.generateMessage("Que paho", ReceiverActor.getName(), ReceiverActor.getPublicKey());
    
    std::ifstream fileIn5("jsons/message.json");
    nlohmann::json package5;
    fileIn5 >> package5;
    fileIn5.close();

    // Modificar manualmente la firma publica
    package5["sender_public_key"]["e"] = 17;
    package5["sender_public_key"]["n"] = 9999999937;

    std::ofstream fileOut5("jsons/message.json");
    fileOut5 << package5.dump(4);
    fileOut5.close();

    ReceiverActor.readMessage(0);
    std::cout << "\n\n-------------------------------------------------------------------------------------\n";


    // CASO 6 - Intento de descifrado con la llave privada de otro usuario
    std::cout << "\n\nCASO 6 - Intento de descifrado con la llave privada de otro usuario\n";
    SenderActor.generateMessage("Iiiii", ReceiverActor.getName(), ReceiverActor.getPublicKey());
    ReceiverActor.readMessage(8);
    std::cout << "\n\n-------------------------------------------------------------------------------------\n";


    // CASO 7 - Paquete JSON incompleto
    std::cout << "\n\nCASO 7 - Paquete JSON incompleto\n";
    SenderActor.generateMessage("Hola123", ReceiverActor.getName(), ReceiverActor.getPublicKey());

    std::ifstream fileIn7("jsons/message.json");
    nlohmann::json package7;
    fileIn7 >> package7;
    fileIn7.close();

    // Eliminar campo de firma
    package7.erase("signature");

    std::ofstream fileOut7("jsons/message.json");
    fileOut7 << package7.dump(4);
    fileOut7.close();

    ReceiverActor.readMessage(0);
    std::cout << "\n\n-------------------------------------------------------------------------------------\n";


    // CASO 8 - Paquete JSON con datos mal formados
    std::cout << "\n\nCASO 8 - Paquete JSON con datos mal formados\n";
    SenderActor.generateMessage("Tocheux", ReceiverActor.getName(), ReceiverActor.getPublicKey());

    std::ifstream fileIn8("jsons/message.json");
    nlohmann::json package8;
    fileIn8 >> package8;
    fileIn8.close();

    // Cambiar a formato incorrecto campos en JSON 
    package8["encrypted_message"] = "corrupto";
    package8["signature"] = "invalido";
    package8["encrypted_session_key"] = "malformado";

    std::ofstream fileOut8("jsons/message.json");
    fileOut8 << package8.dump(4);
    fileOut8.close();

    ReceiverActor.readMessage(0);
    std::cout << "\n\n-------------------------------------------------------------------------------------\n";


    // CASO 9 - Firma que no corresponde al mensaje recibido
    std::cout << "\n\nCASO 9 - Firma que no corresponde al mensaje recibido\n";
    SenderActor.generateMessage("Proyecto", ReceiverActor.getName(), ReceiverActor.getPublicKey());

    std::ifstream fileIn9("jsons/message.json");
    nlohmann::json package9;
    fileIn9 >> package9;
    fileIn9.close();

    // Guardar primera firma generada
    uint64_t wrongSignature = package9["signature"].get<uint64_t>();

    // Generar segundo JSON
    SenderActor.generateMessage("Donkey", ReceiverActor.getName(), ReceiverActor.getPublicKey());

    std::ifstream fileIn10("jsons/message.json");
    nlohmann::json package10;
    fileIn10 >> package10;
    fileIn10.close();

    // Cambiar firma nueva a firma orignal no correspondiente
    package10["signature"] = wrongSignature;

    std::ofstream fileOut10("jsons/message.json");
    fileOut10 << package10.dump(4);
    fileOut10.close();

    ReceiverActor.readMessage(0);
    std::cout << "\n\n-------------------------------------------------------------------------------------\n";

    return 0;
}