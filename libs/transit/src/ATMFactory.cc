#include "ATMFactory.h"

IEntity* ATMFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("atm") == 0) {
    std::cout << "ATM Created" << std::endl;
    return new ATM(entity);
  }
  return nullptr;
}
