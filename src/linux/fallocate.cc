#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include <napi.h>

using namespace Napi;

Value fallocate(const CallbackInfo &info)
{
    auto env = info.Env();

    if (info.Length() < 3) {
        Error::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    if (!info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber()) {
        Error::New(env, "Wrong arguments").ThrowAsJavaScriptException();
        return env.Undefined();
    }

    int   fd     = info[0].As<Number>();
    off_t offset = info[1].As<Number>();
    off_t len    = info[2].As<Number>();

    int retval = posix_fallocate(fd, 0, offset + len);

    return Number::New(env, retval == -1 ? -errno : retval);
}

Object Init(Env env, Object exports)
{
    exports.Set(String::New(env, "fallocate"), Function::New(env, fallocate));
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init);
