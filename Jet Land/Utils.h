#pragma once

#define CheckAllocation(x) if (!x) { return; }
#define ReleaseCOM(x) if (x) { x->Release(); x = NULL; }
#define Delete(x) if (x) { delete[] x; x = NULL; }