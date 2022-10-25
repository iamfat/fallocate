#include <nan.h>
#include <errno.h>
#include <unistd.h>
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
    off_t offset = info[2]->NumberValue(ctx).FromJust();
    off_t len    = info[3]->NumberValue(ctx).FromJust();

    fstore_t store = {
        F_ALLOCATECONTIG, F_PEOFPOSMODE, 0, offset + len, 0,
    };
    int retval = fcntl(fd, F_PREALLOCATE, &store);

    if (-1 == retval) {
        store.fst_flags = F_ALLOCATEALL;
        retval          = fcntl(fd, F_PREALLOCATE, &store);
    }

    if (-1 != retval) {
        retval = ftruncate(fd, offset + len);
    }

    info.GetReturnValue().Set(retval == -1 ? -errno : (int)store.fst_bytesalloc);
}

NAN_MODULE_INIT(Init)
{
    Nan::Set(target, Nan::New("fallocate").ToLocalChecked(),
             Nan::GetFunction(Nan::New<FunctionTemplate>(fallocate)).ToLocalChecked());
}

NODE_MODULE(fallocate, Init)