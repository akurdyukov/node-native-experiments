#include <nan.h>
#include "myobject.h"
#include "native.h"

using namespace v8;

MyObject::MyObject() {};
MyObject::~MyObject() {};

Nan::Persistent<v8::Function> MyObject::constructor;

void MyObject::Init() {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("MyObject").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  // Prototype
  tpl->PrototypeTemplate()->Set(Nan::New("plusOne").ToLocalChecked(),
      Nan::New<v8::FunctionTemplate>(PlusOne)->GetFunction());

  constructor.Reset(tpl->GetFunction());
}

void MyObject::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  // create JS object and wrap
  MyObject* obj = new MyObject();
  obj->Wrap(info.This());

  info.GetReturnValue().Set(info.This());
}


v8::Local<v8::Object> MyObject::NewInstance(NativeObject* native) {
  Nan::EscapableHandleScope scope;

  // create new JS object
  const unsigned argc = 0;
  v8::Local<v8::Value> argv[argc] = { };
  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
  v8::Local<v8::Object> instance = cons->NewInstance(argc, argv);

  // push aggregated into MyObject
  MyObject* wrapped = Nan::ObjectWrap::Unwrap<MyObject>(instance);
  wrapped->_native = native;

  return scope.Escape(instance);
}

void MyObject::PlusOne(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.This());
  int newValue = obj->_native->plusOne();

  info.GetReturnValue().Set(Nan::New(newValue));
}
