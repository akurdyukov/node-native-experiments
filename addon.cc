#include <nan.h>
#include "myobject.h"
#include "async.h"

void RunCallback(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  // get callback
  v8::Local<v8::Value> arg = info[0];
  v8::Local<v8::Function> cb = info[1].As<v8::Function>();

  // run async
  RunAsync(arg, cb);
}

void Init(v8::Local<v8::Object> exports, v8::Local<v8::Object> module) {
  Nan::HandleScope scope;

  MyObject::Init();

  Nan::SetMethod(module, "exports", RunCallback);
}

NODE_MODULE(addon, Init)
