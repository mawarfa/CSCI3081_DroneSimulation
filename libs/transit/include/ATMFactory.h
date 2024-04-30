#ifndef ATM_FACTORY_H_
#define ATM_FACTORY_H_

#include <vector>

#include "IEntityFactory.h"
#include "ATM.h"

/**
 *@brief ATM Factory to produce ATM class.
 **/
class ATMFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for IEntityFactory class.
   **/
  virtual ~ATMFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a
   *nullpointer if creation failed.
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif
