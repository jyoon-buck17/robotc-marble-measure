#ifndef _measure
#define _measure

// SETUP

// define how many different materials should be distinguished
#define MEASURE_MATERIAL_NUMBER 3

// update this if necessary to match your line follower
#define lfv SensorValue[lineFollower]

/////////

// WHY A STRUCT?
// Originally, our code took two different measurements,
// one with a flashlight on and one with it off.
// This makes it easy to add additional measurement dimensions.
// Add any additional 
struct MaterialMeasurement {
  unsigned int measurement;
};

struct MaterialMeasurement materialTypes[MEASURE_MATERIAL_NUMBER];
int materialsLearned = 0;

struct MaterialMeasurement measurementBuffer;

// update to account for any other dimensions
int getDistance(int x1, int x2) {
  return abs(x1 - x2);
}

// update to include any additional dimensions
void msrCopy(struct MaterialMeasurement *origin, struct MaterialMeasurement *target) {
  target->measurement = origin->measurement;
}

// update to measure any additional dimensions
void doMeasurement() {
  measurementBuffer.measurement = lfv;
}

int measurementHelper(bool learn) {
  // distance: variance in lit and unlit values from 
  int dist[MEASURE_MATERIAL_NUMBER];      // for each material type

  doMeasurement();

  if (learn) {
    // copy this to a new material
    msrCopy(&measurementBuffer, &materialTypes[materialsLearned]);
    // increment the count of materials learned
    materialsLearned++;
    // return the material
    return materialsLearned - 1;
  }

  // otherwise, we're looking for the closest material

  // update to include additional dimensions
  for (int i = 0; i < materialsLearned; ++i) {
    dist[i] = getDistance(measurementBuffer.measurement, materialTypes[i].measurement);
  }

  // find the index of dist with the smallest value.
  int smallestMaterial = 0;
  int smallestValue = dist[0];
  for (int i = 1; i < materialsLearned; ++i) {
    if (dist[i] < smallestValue) {
      smallestValue = dist[i];
      smallestMaterial = i;
    }
  }
  // this is our best possible guess, given what we know.
  return smallestMaterial;
}

// USE THESE FUNCTIONS

// learnMaterial() : int
// learns a new material based on the current sensor status
// returns the new material's id
int learnMaterial() {
  return measurementHelper(true);
}

// learnMaterialValue(int lineFollowerValue) : int
// learns a new material based on an explicit value
// returns the new material's id
int learnMaterialValue(int lineFollowerValue) {
  measurementBuffer.measurement = lfv;
  // copy this to a new material
  msrCopy(&measurementBuffer, &materialTypes[materialsLearned]);
  // increment the count of materials learned
  materialsLearned++;
  // return the material
  return materialsLearned - 1;
}

// getMaterial() : int
// find the material that is closest to the current measured value
// returns the material's id
int getMaterial() {
  return measurementHelper();
}

// unlearnAllMaterials() : void
// forgets all materials.
void unlearnAllMaterials() {
  materialsLearned = 0;
}




#endif
