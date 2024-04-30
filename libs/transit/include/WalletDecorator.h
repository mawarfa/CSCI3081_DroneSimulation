#ifndef WALLET_DECORATOR_H_
#define WALLET_DECORATOR_H_

#include "IEntity.h"
/**
 * @brief Class inherits from IEntity class and is represented as the amount of money in an Entitys wallet.
 * 
 */
class WalletDecorator : public IEntity {
 public:
  /**
   * @brief Construct a new Wallet Decorator object
   *
   * @param entity the entity to decorate on
   */
  WalletDecorator(IEntity* entity) {this->total = 100.00;}

  /**
   * @brief WalletDecorator Destructor
   */
  ~WalletDecorator();


  /**
   * @brief Gets the Entity's destination
   * @return The Entity's destination
   */

  Vector3 GetDestination() const { entity->GetDestination(); }

/**
   * @brief Gets the ID of the entity.
   * @return The ID of the entity.
   */
  int GetId() const { entity->GetId(); }

 /**
   * @brief Gets the position of the entity.
   * @return The position of the entity.
   */
  Vector3 GetPosition() const { entity->GetPosition(); }

 /**
   * @brief Gets the direction of the entity.
   * @return The direction of the entity.
   */
  Vector3 GetDirection() const { entity->GetDirection(); }

  /**
   * @brief Gets the details of the entity.
   * @return The details of the entity.
   */
  JsonObject GetDetails() const { entity->GetDetails(); }

  /**
   * @brief Gets the color of the drone
   * @return The color of the drone
   */
  std::string GetColor() const { entity->GetColor(); }

/**
   * @brief Gets the speed of the entity.
   * @return The speed of the entity.
   */
  float GetSpeed()const { entity->GetSpeed(); }

  /**
   * @brief Gets the availability of the entity.
   * @return The availability of the entity.
   */
  bool GetAvailability() const { entity->GetAvailability(); }

    /**
   * @brief Get the Strategy Name
   * @return Streategy name
   */
  std::string GetStrategyName()const { entity->GetStrategyName(); }

  /**
   * @brief Set the Strategy Name
   * @param strategyName_ Strategy name
   */
  void SetStrategyName(std::string strategyName_)
  { entity->SetStrategyName(strategyName_); }
  /**
   * @brief Sets the availability of the entity.
   * @param choice The desired availability of the entity.
   */
  void SetAvailability(bool choice)  { entity->SetAvailability(choice); }
  /**
   * @brief Updates the entity's position in the physical system.
   * @param dt The time step of the update.
   * @param scheduler The list of all entities in the system.
   */
  void Update(double dt, std::vector<IEntity*> scheduler)
  {entity->Update(dt,  scheduler); }
  /**
   * @brief Sets the position of the entity.
   * @param pos_ The desired position of the entity.
   */
  void SetPosition(Vector3 pos_)  { entity->SetPosition(pos_); }
   /**
   *@brief Set the destination of the entity.
   *@param des_ The new destination of the entity.
   */
  void SetDestination(Vector3 pos_)  { entity->SetDestination(pos_); }
  /**
   *@brief Set the direction of the entity.
   *@param dir_ The new direction of the entity.
   */
  void SetDirection(Vector3 pos_)  { entity->SetDirection(pos_); }
   /**
   * @brief Sets the color of the drone
   * @param col_ The new color of the drone
   */
  void SetColor(std::string col_)  {entity->SetColor(col_); }
  /**
   * @brief Rotate the entity.
   * @param angle The angle to rotate the entity by.
   */
  void Rotate(double angle)  {entity->Rotate(angle); }
  /**
   * @brief Make the entity jump.
   * @param height The height to make the entity jump.
   */
  void Jump(double height)  {entity->Jump(height); }
  /**
   * @brief random position .
   * @param min, max The random posiiton an entity will go.
   */
  float Random(float Min, float Max)  {entity->Random(Min,  Max); }
  /**
   * @brief Add price of ride to the drones wallet
   * @param amount the amount of money being added to entity's wallet
   */
    void AddWallet(double amount);

  /**
   * @brief Subtract the price of the ride from the robots wallet
   * @param amount the amount of money being subtracted from entity's wallet
   */
    void SubWallet(double amount);

     /**
   * @brief Set the amount of money to the entity wallet
   * @param total the amount of money being set to the entity's wallet
   */

    void SetTotal(double total) {this->total = total;}

     /**
   * @brief Get total amount of money in entity wallet
   @return Total amount of money in the entity wallet.
   */
    double GetTotal() {return this->total;}


 private:
    /**
  *@brief The total amount of wallet
**/
  double total;

     /**
  *@brief The entity that is being decorated on
**/
  IEntity* entity;
};

#endif  // WALLET_DECORATOR_H_
