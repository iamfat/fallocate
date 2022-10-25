#include <nan.h>
#include <errno.h>
#include <fcntl.h>

using namespace v8;

NAN_METHOD(fallocate)
{
    if (info.Length() < 3) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    if (!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber()) {
        Nan::ThrowTypeError("Wrong arguments");
        return;
    }

    Local<Context> ctx = Nan::GetCurrentContext();

    int   fd     = info[0]->Uint32Value(ctx).FromJust();
    off_t offset = info[1]->NumberValue(ctx).FromJust();
    off_t len    = info[2]->NumberValue(ctx).FromJust();
    int   retval = posix_fallocate(fd, 0, offset + len);

    info.GetReturnValue().Set(retval == -1 ? -errno : retval);
}

NAN_MODULE_INIT(Init)
{
    Nan::Set(target, Nan::New("fallocate").ToLocalChecked(),
             Nan::GetFunction(Nan::New<FunctionTemplate>(fallocate)).ToLocalChecked());
}

NODE_MODULE(fallocate, Init)