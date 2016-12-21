#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <nan.h>
#include "native.h"

class MyObject : public Nan::ObjectWrap {
 public:
  static void Init();
  static v8::Local<v8::Object> NewInstance(NativeObject* native);

 private:
  MyObject();
  ~MyObject();

  static Nan::Persistent<v8::Function> constructor;
  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void PlusOne(const Nan::FunctionCallbackInfo<v8::Value>& info);
  NativeObject* _native;
};

#endif
