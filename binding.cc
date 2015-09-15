#include <sys/types.h>
#include <signal.h>
#include <nan.h>

using v8::FunctionTemplate;

NAN_METHOD(Kill) {
  auto pid = Nan::To<pid_t>(info[0]).FromJust();
  auto signal = Nan::To<int>(info[1]).FromJust();

  int ret = 0;
  if (kill(pid, signal) != 0) {
    ret = -errno;
  }

  info.GetReturnValue().Set(ret);
}

NAN_MODULE_INIT(Init) {
  Nan::Set(target, Nan::New("kill").ToLocalChecked(),
    Nan::GetFunction(Nan::New<FunctionTemplate>(Kill)).ToLocalChecked());


#define EXPORT_CONSTANT(c) Nan::Set(target, Nan::New(#c).ToLocalChecked(), Nan::New(c))
  auto errnos = Nan::New<v8::Object>();
#define target errnos
  EXPORT_CONSTANT(EINVAL);
  EXPORT_CONSTANT(EPERM);
  EXPORT_CONSTANT(ESRCH);
#undef target
  Nan::Set(target, Nan::New("errnos").ToLocalChecked(),
    errnos);

  auto signals = Nan::New<v8::Object>();
#define target signals 
  EXPORT_CONSTANT(SIGABRT);
  EXPORT_CONSTANT(SIGALRM);
  EXPORT_CONSTANT(SIGBUS);
  EXPORT_CONSTANT(SIGCHLD);
  EXPORT_CONSTANT(SIGCONT);
  EXPORT_CONSTANT(SIGFPE);
  EXPORT_CONSTANT(SIGHUP);
  EXPORT_CONSTANT(SIGILL);
  EXPORT_CONSTANT(SIGINT);
  EXPORT_CONSTANT(SIGKILL);
  EXPORT_CONSTANT(SIGPIPE);
  EXPORT_CONSTANT(SIGQUIT);
  EXPORT_CONSTANT(SIGSEGV);
  EXPORT_CONSTANT(SIGSTOP);
  EXPORT_CONSTANT(SIGTERM);
  EXPORT_CONSTANT(SIGTSTP);
  EXPORT_CONSTANT(SIGTTIN);
  EXPORT_CONSTANT(SIGTTOU);
  EXPORT_CONSTANT(SIGUSR1);
  EXPORT_CONSTANT(SIGUSR2);
#if !(__APPLE__ && __MACH__)
  EXPORT_CONSTANT(SIGPOLL);
#endif
  EXPORT_CONSTANT(SIGPROF);
  EXPORT_CONSTANT(SIGSYS);
  EXPORT_CONSTANT(SIGTRAP);
  EXPORT_CONSTANT(SIGURG);
  EXPORT_CONSTANT(SIGVTALRM);
  EXPORT_CONSTANT(SIGXCPU);
  EXPORT_CONSTANT(SIGXFSZ);
#undef target
  Nan::Set(target, Nan::New("signals").ToLocalChecked(),
    signals);

#undef EXPORT_CONSTANT
}

NODE_MODULE(NativeExtension, Init)
