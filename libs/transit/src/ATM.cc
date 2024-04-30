#include "ATM.h"

ATM::ATM(JsonObject &obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
}

JsonObject ATM::GetDetails() const { return details; }
