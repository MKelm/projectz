#include "models.hpp"

Model::Model() {
  changed = true;
}

// MAP MODEL
MapModel::MapModel(Uint16 argColumns, Uint16 argRows) {
  columns = argColumns;
  rows = argRows;
  fields = new Uint16*[argRows];
  for (int i = 0; i < argRows; ++i) {
    fields[i] = new Uint16[argColumns];
  }
  cout << "model constructor" << endl;
}

MapModel::~MapModel() {
  cout << "model destructor" << endl;
  for (int i = 0; i < rows; ++i) {
    delete[] fields[i];
  }
  delete[] fields;
}
