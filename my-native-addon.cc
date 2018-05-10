#include <node.h>

const int maxValue = 10;
int numberOfCalls = 0;

void WhoAmI(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();
  auto message = v8::String::NewFromUtf8(isolate, "I'm a Node Hero!");
  args.GetReturnValue().Set(message);
}

void Increment(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = args.GetIsolate();

  if (!args[0]->IsNumber()) {
    isolate->ThrowException(v8::Exception::TypeError(
          v8::String::NewFromUtf8(isolate, "Argument must be a number")));
    return;
  }

  double argsValue = args[0]->NumberValue();
  if (numberOfCalls + argsValue > maxValue) {
    isolate->ThrowException(v8::Exception::Error(
          v8::String::NewFromUtf8(isolate, "Counter went through the roof!")));
    return;
  }

  numberOfCalls += argsValue;

  auto currentNumberOfCalls =
    v8::Number::New(isolate, static_cast<double>(numberOfCalls));

  args.GetReturnValue().Set(currentNumberOfCalls);
}

void Add(const v8::FunctionCallbackInfo<v8::Value>& args){
    if(args.Length() == 1){
        int* p1 = NULL;
        *p1 = 3;//cause segfault
    }

    v8::Isolate* isolate = args.GetIsolate();
    if(args.Length() < 2){
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "Wrong number of arguments")));
    }

    if(!args[0]->IsNumber() || !args[1]->IsNumber()){
        isolate->ThrowException(v8::Exception::TypeError(v8::String::NewFromUtf8(isolate, "arguments must of type number")));
    }

    double value = args[0]->NumberValue() + args[1]->NumberValue();
    v8::Local<v8::Number> num = v8::Number::New(isolate, value);
    
    args.GetReturnValue().Set(num);
}

void RunCallback(const v8::FunctionCallbackInfo<v8::Value>& args){
    v8::Isolate* isolate = args.GetIsolate();

    v8::Local<v8::Function> cb = v8::Local<v8::Function>::Cast(args[0]);
    const unsigned argc = 1;
    v8::Local<v8::Value> argv[argc] = { v8::String::NewFromUtf8(isolate, "hello world") };
    cb->Call(Null(isolate), argc, argv);
}

void Initialize(v8::Local<v8::Object> exports) {
  NODE_SET_METHOD(exports, "whoami", WhoAmI);
  NODE_SET_METHOD(exports, "increment", Increment);
  NODE_SET_METHOD(exports, "add", Add);
  NODE_SET_METHOD(exports, "runCallback", RunCallback);
}

NODE_MODULE(module_name, Initialize)
