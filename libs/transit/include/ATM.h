#ifndef ATM_H
#define ATM_H

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

/**
 * @class ATM
 * @brief Represents an ATM in a physical system
 */
class ATM : public IEntity {
 public:
  /**
   * @brief Constructor
   * @param obj JSON object containing the ATM's information
   */
  ATM(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~ATM() override = default;

  /**
   * @brief Gets the ATM's position
   * @return The ATM's position
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the ATM's details
   * @return The ATM's details
   */
  JsonObject GetDetails() const override;

  /**
   * @brief Gets the direction of the ATM
   * @return The direction of the ATM
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the destination of the ATM
   * @return The destination of the ATM
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the speed of the ATM
   * @return The speed of the ATM
   */
  float GetSpeed() const { return speed; }

  /**
   * @brief Sets the ATM's position
   * @param pos_ The new position of the ATM
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

 private:
  /**
  *@brief Details of a atm
**/
  JsonObject details;

  /**
  *@brief current postion of a atm
**/
  Vector3 position;

   /**
  *@brief current direction of a atm
**/
  Vector3 direction;

    /**
  *@brief current destination of a atm
**/
  Vector3 destination;

     /**
  *@brief The speed of a atm
**/
  float speed;
};

#endif  // ATM_H
