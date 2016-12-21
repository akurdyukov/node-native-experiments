#ifndef ASYNC_H_
#define ASYNC_H_

#include <nan.h>

void RunAsync(const v8::Local<v8::Value> arg, v8::Local<v8::Function> cb);

#endif  // ASYNC_H_