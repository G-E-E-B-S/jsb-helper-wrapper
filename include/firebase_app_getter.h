#pragma once
namespace firebase
{
    class App;
}
namespace wrapper
{
    namespace jsbhelper
    {
        class IFirebaseAppGetter
        {
        public:
            IFirebaseAppGetter() = default;
            virtual firebase::App *getApp() = 0;
            virtual ~IFirebaseAppGetter() = default;
        };
    }
}