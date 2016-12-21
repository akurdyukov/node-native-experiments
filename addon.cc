#include <nan.h>
#include "myobject.h"

void RunCallback(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  // get callback
  v8::Local<v8::Function> cb = info[1].As<v8::Function>();

  // create object
  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  obj->Set(Nan::New("msg").ToLocalChecked(), MyObject::NewInstance(info[0]));

  // prepare output
  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = { obj };
  Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);
}

void Init(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
  Nan::HandleScope scope;

  MyObject::Init();

  Nan::SetMethod(module, "exports", RunCallback);
}

NODE_MODULE(addon, Init)
