#define _USE_MATH_DEFINES
#include "Drone.h"

#include <cmath>
#include <limits>

#include "AstarStrategy.h"
#include "BeelineStrategy.h"
#include "DfsStrategy.h"
#include "DijkstraStrategy.h"
#include "JumpDecorator.h"
#include "SpinDecorator.h"
#include "WalletDecorator.h"

Drone::Drone(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

  available = true;
}

Drone::~Drone() {
  // Delete dynamically allocated variables
  delete graph;
  delete nearestEntity;
  delete toRobot;
  delete toFinalDestination;
}

void Drone::GetNearestEntity(std::vector<IEntity*> scheduler) {
  float minDis = std::numeric_limits<float>::max();
  for (auto entity : scheduler) {
    if (entity->GetAvailability()) {
      float disToEntity = this->position.Distance(entity->GetPosition());
      if (disToEntity <= minDis) {
        minDis = disToEntity;
        nearestEntity = entity;
      }
    }
  }

  if (nearestEntity) {
      // set availability to the nearest entity
    nearestEntity->SetAvailability(false);
    available = false;
    pickedUp = false;

    destination = nearestEntity->GetPosition();
    Vector3 finalDestination = nearestEntity->GetDestination();

    toRobot = new BeelineStrategy(position, destination);

    droneWallet = new WalletDecorator(this);
    entityWallet = new WalletDecorator(nearestEntity);
    std::cout << "Robot's original balance: "<<
    entityWallet->GetTotal() << std::endl;
    std::cout << "Drone's original balance: "<<
    droneWallet->GetTotal() << std::endl;
    int x1 = destination[0];
    int y1 = destination[1];
    int z1 = destination[2];
    int x2 = finalDestination[0];
    int y2 = finalDestination[1];
    int z2 = finalDestination[2];

    double distance = sqrt(pow((x2-x1), 2)+ pow((y2-y1), 2) + pow((z2-z1), 2));
    price = distance * (.1);

    std::string strat = nearestEntity->GetStrategyName();
    if (strat == "astar")
      toFinalDestination =
        new JumpDecorator(new
        AstarStrategy(destination, finalDestination, graph));
    else if (strat == "dfs")
      toFinalDestination =
        new SpinDecorator(new JumpDecorator(new
        DfsStrategy(destination, finalDestination, graph)));
    else if (strat == "dijkstra")
      toFinalDestination =
        new JumpDecorator(new SpinDecorator(new
        DijkstraStrategy(destination, finalDestination, graph)));
    else
      toFinalDestination = new BeelineStrategy(destination, finalDestination);
  }
}

void Drone::Update(double dt, std::vector<IEntity*> scheduler) {
  if (available)
    GetNearestEntity(scheduler);
    // std::cout << "Trip price: " << price << std::endl;

  if (toRobot) {
    toRobot->Move(this, dt);
    if (toRobot->IsCompleted()) {
      if (entityWallet->GetTotal() >= price) {
        delete toRobot;
        toRobot = nullptr;
        pickedUp = true;
      } else {
        float minDistance = std::numeric_limits<float>::max();
        for (auto entity : atms) {
            JsonObject tempDetails = entity->GetDetails();
            std::string entType = tempDetails["type"];
            if (entType.compare("atm") == 0) {
                float distanceToEntity =
                nearestEntity->GetPosition().Distance(entity->GetPosition());
                if (distanceToEntity <= minDistance) {
                  minDistance = distanceToEntity;
                  nearestATM = entity;
                }
            }
        }
        nearestEntity->SetDestination(nearestATM->GetPosition());
        toATM = new BeelineStrategy(
        nearestEntity->GetPosition(), nearestATM->GetPosition());
        toATM->Move(nearestEntity, dt);

        if (toATM->IsCompleted()) {
          std::cout << "Trip price: " << price << std::endl;
          entityWallet->AddWallet(100.00);
          toRobot = new BeelineStrategy(
            this->position, nearestEntity->GetPosition());
          std::cout << "Robot's new balance: " <<
          entityWallet->GetTotal() << std::endl;
          delete toATM;
          toATM = nullptr;
          nearestATM = nullptr;
          if (entityWallet->GetTotal() < price) {
            std::cout << "Can't schedule trip. Still too broke. Walk!"
            << std::endl;
            delete toRobot;
            delete toFinalDestination;
            toRobot = nullptr;
            toFinalDestination = nullptr;
            nearestEntity = nullptr;
            available = true;
            pickedUp = false;
          }
        }
      }
    }
  } else if (toFinalDestination) {
    toFinalDestination->Move(this, dt);

    if (nearestEntity && pickedUp) {
      nearestEntity->SetPosition(position);
      nearestEntity->SetDirection(direction);
    }

    if (toFinalDestination->IsCompleted()) {
      entityWallet->SubWallet(price);
      droneWallet->AddWallet(price);
      std::cout << "Trip price: " << price << std::endl;
      std::cout << "Robot's balance: " << entityWallet->GetTotal() << std::endl;
      std::cout << "Drone's balance: " << droneWallet->GetTotal() << std::endl;
      delete toFinalDestination;
      toFinalDestination = nullptr;
      nearestEntity = nullptr;
      available = true;
      pickedUp = false;
    }
  }
}


void Drone::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

void Drone::Jump(double height) {
  if (goUp) {
    position.y += height;
    jumpHeight += height;
    if (jumpHeight > 5) {
      goUp = false;
    }
  } else {
    position.y -= height;
    jumpHeight -= height;
    if (jumpHeight < 0) {
      goUp = true;
    }
  }
}

// double Drone::GetBalance() {
//     return balance;
// }
