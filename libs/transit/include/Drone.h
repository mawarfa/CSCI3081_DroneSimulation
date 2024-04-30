#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"
#include "WalletDecorator.h"

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity {
 public:
  /**
   * @brief Drones are created with a name
   * @param obj JSON object containing the drone's information
   */
  Drone(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Drone();

  /**
   * @brief Gets the speed of the drone
   * @return The speed of the drone
   */
  float GetSpeed() const { return speed; }

  /**
   * @brief Gets the position of the drone
   * @return The position of the drone
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the direction of the drone
   * @return The direction of the drone
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the destination of the drone
   * @return The destination of the drone
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the color of the drone
   * @return The color of the drone
   */
  std::string GetColor() const { return color; }

  /**
   * @brief Gets the details information of the drone
   * @return The details information of the drone
   */
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Gets the availability of the drone
   * @return The availability of the drone
   */
  bool GetAvailability() const { return available; }

  /**
   * @brief Gets the nearest entity in the scheduler
   * @param scheduler Vector containing all the entities in the system
   */
  void GetNearestEntity(std::vector<IEntity*> scheduler);

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Sets the position of the drone
   * @param pos_ The new position of the drone
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the direction of the drone
   * @param dir_ The new direction of the drone
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the destination of the drone
   * @param des_ The new destination of the drone
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Sets the color of the drone
   * @param col_ The new color of the drone
   */
  void SetColor(std::string col_) { color = col_; }

  /**
   * @brief Rotates the drone
   * @param angle The angle by which the drone should be rotated
   */
  void Rotate(double angle);

  /**
   * @brief Makes the drone jump
   * @param height The height at which the drone should jump
   */
  void Jump(double height);

  /**
   * @brief Removing the copy constructor and assignment operator
   * so that drones cannot be copied.
   */
  Drone(const Drone& drone) = delete;
  Drone& operator=(const Drone& drone) = delete;

  /**
   * @brief setting a vector of atms to the atm vector
   * @param atms vector of atm entities
   */
  void SetATMEntities(std::vector<IEntity*> atms) {
    this->atms = atms;
  }


 private:
 /**
  *@brief Details of a drone
**/
  JsonObject details;

  /**
  *@brief current postion of a drone
**/
  Vector3 position;

   /**
  *@brief current direction of a drone
**/
  Vector3 direction;

  /**
  *@brief The color of a drone.
**/
  std::string color = "None";  // None means default color
/**
  *@brief The height that the drone will jump
**/
float jumpHeight = 0;

/**
  *@brief A jump helper that checks if drone is going up
**/
  bool goUp = true;  // jump helper
/**
  *@brief current destination of a drone
**/
  Vector3 destination;
/**
  *@brief The speed of a drone
**/
  float speed;
/**
  *@brief boolean that checks if drone is available
**/
  bool available;
/**
  *@brief Boolean that checks if drone has been picked up. 
**/
  bool pickedUp;
/**
  *@brief Pointer Ientity object that represent the nearest Entity of a drone. 
**/
  IEntity* nearestEntity = nullptr;
/**
  *@brief Pointer Ientity object that represent the nearest ATM. 
**/
  IEntity* nearestATM = nullptr;

/**
  *@brief Pointer Ientity object that represent the nearest Entity to a robot.
**/
  IStrategy* toRobot = nullptr;

/**
  *@brief Pointer Ientity object that represent the final Destination of drone.
**/
  IStrategy* toFinalDestination = nullptr;

/**
  *@brief pointer to strategy object that represent the how to get to atm.
**/
  IStrategy* toATM = nullptr;

  /**
  *@brief List of atm entities
**/
  std::vector<IEntity*> atms;

/**
  *@brief the price of the ride. 
**/
  double price;

/**
  *@brief pointer to a WalletDecorator object that represent the  wallet of an entity.
**/

  WalletDecorator* entityWallet = nullptr;

/**
  *@brief pointer to a WalletDecorator object that represent the  wallet of an drone.
**/
  WalletDecorator* droneWallet = nullptr;
};
#endif
