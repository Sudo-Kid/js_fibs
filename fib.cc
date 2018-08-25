// hello.cc
#include <node.h>
#include <map>
#include <stdint.h>

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;


void Method(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    if (args.Length() < 1) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "You are required to pass in a number")
        ));
        return;
    }

    if (!args[0]->IsNumber()) {
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "You didn't pass in a number")
        ));
        return;
    }

    __int128 n = args[0]->NumberValue() + 1;

    __int128 a, b, c;

    a = c = 0;
    b = 1;
    for(__int128 i=1; i<= n-2; i++){
        c = a + b;
        a = b;
        b = c;
    }

	args.GetReturnValue().Set(Number::New(isolate, c));
}

void Initialize(Local<Object> exports) {
    NODE_SET_METHOD(exports, "calc", Method);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)
