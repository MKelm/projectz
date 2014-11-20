#ifndef _INCLUDE_MODELS_HPP
#define _INCLUDE_MODELS_HPP

#include "global.hpp"

class Model {
  public:
    bool changed;
    Model();
    virtual ~Model() {};
};

class MapModel: public Model {
    Uint16 rows;
    Uint16 columns;
    Uint16 **fields;
  public:
    MapModel(Uint16, Uint16);
    ~MapModel();
};

#endif
