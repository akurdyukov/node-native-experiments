#include <nan.h>
#include "myobject.h"

void RunCallback(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  // get callback
  v8::Local<v8::Function> cb = info[1].As<v8::Function>();

  // prepare output
  const unsigned argc = 1;
  v8::Local<v8::Value> argv[argc] = { MyObject::NewInstance(info[0]) };
  Nan::MakeCallback(Nan::GetCurrentContext()->Global(), cb, argc, argv);
}

void Init(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
  Nan::HandleScope scope;

  MyObject::Init();

  Nan::SetMethod(module, "exports", RunCallback);
}

NODE_MODULE(addon, Init)
