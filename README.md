# robotc-marble-measure

## include

```c
#include "measure.c"
```

## functions
### `int learnMaterial()`
learns a new material based on the current sensor status

returns the new material's id

### `int learnMaterialValue(int lineFollowerValue)`
learns a new material based on an explicitly passed value.

returns the new material's id

### `int getMaterial()`
find the material that's closest to the current measured value

returns the material's id

### `void unlearnAllMaterials()`
forgets all materials.