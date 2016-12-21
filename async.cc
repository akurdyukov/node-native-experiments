#include <nan.h>
#include "async.h"
#include "myobject.h"

using v8::Function;
using v8::Local;
using v8::Number;
using v8::Value;
using Nan::AsyncQueueWorker;
using Nan::AsyncWorker;
using Nan::Callback;
using Nan::HandleScope;
using Nan::New;
using Nan::Null;
using Nan::To;

class ObjectCreateWorker : public AsyncWorker {
 public:
  ObjectCreateWorker(Callback *callback, int start)
    : AsyncWorker(callback), start(start) {}
  ~ObjectCreateWorker() {}

  // Executed inside the worker-thread.
  // It is not safe to access V8, or V8 data structures
  // here, so everything we need for input and output
  // should go on `this`.
  void Execute () {
    start += 1;
  }

  // Executed when the async work is complete
  // this function will be run inside the main event loop
  // so it is safe to use V8 again
  void HandleOKCallback () {
    HandleScope scope;

    const unsigned argc = 1;
    v8::Local<v8::Value> argv[argc] = { 
        MyObject::NewInstance(start)
    };

    callback->Call(argc, argv);
  }

 private:
  int start;
};

// Asynchronous access to the `Estimate()` function
void RunAsync(const v8::Local<v8::Value> arg, v8::Local<v8::Function> cb) {
  int start = To<int>(arg).FromJust();
  Callback *callback = new Callback(cb);

  AsyncQueueWorker(new ObjectCreateWorker(callback, start));
}