#include "native.h"

NativeObject::NativeObject(int start): current(start) {}
NativeObject::~NativeObject() {}

int NativeObject::plusOne() {
	current += 1;
	return current;
}
