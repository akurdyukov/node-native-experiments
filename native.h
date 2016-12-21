#ifndef NATIVE_H_
#define NATIVE_H_

class NativeObject {
public:
	NativeObject(int start);
	~NativeObject();

	int plusOne();
private:
	int current;
};

#endif // NATIVE_H_