#pragma once

#include <map>
#include <vector>
#include <string>

#if CC_VERSION_3_X
#include "cocos/bindings/jswrapper/SeApi.h"
#include "cocos/bindings/manual/jsb_conversions.h"
#include "cocos/bindings/manual/jsb_global.h"
#else
#include "cocos/scripting/js-bindings/jswrapper/SeApi.h"
#include "cocos/scripting/js-bindings/manual/jsb_conversions.hpp"
#include "cocos/scripting/js-bindings/manual/jsb_global.h"
#endif

#define MAKE_V8_HAPPY \
se::ScriptEngine::getInstance()->clearException(); \
se::AutoHandleScope hs;
#if CC_VERSION_3_X
#include "cocos/cocos.h"
#else
#include "cocos2d.h"
#include "base/CCScheduler.h"
#include "platform/CCApplication.h"
#endif

#if CC_VERSION_3_X
#define RUN_ON_MAIN_THREAD_BEGIN \
auto funcName = __FUNCTION__;    \
auto scheduler = CC_CURRENT_ENGINE()->getScheduler(); \
scheduler->performFunctionInCocosThread([=](){

#define RUN_ON_MAIN_THREAD_END });
#else
#define RUN_ON_MAIN_THREAD_BEGIN \
auto funcName = __FUNCTION__; \
auto scheduler = cocos2d::Application::getInstance()->getScheduler(); \
scheduler->performFunctionInCocosThread([=](){

#define RUN_ON_MAIN_THREAD_END });
#endif
namespace wrapper
{
    namespace jsbhelper
    {
        class JSListenerBase
        {
        public:
            void setJSDelegate(const se::Value &jsDelegate);
            const se::Value &getJSDelegate();

            void invokeJSFun(const std::string &funName, const se::ValueArray &params = se::EmptyValueArray);
            void invokeJSFunNow(const std::string &funName, const se::ValueArray &params = se::EmptyValueArray);

        protected:
            se::Value _JSDelegate;
        };

        se::Value getPluginValue(se::Object * obj, const std::string &name);
    }
}