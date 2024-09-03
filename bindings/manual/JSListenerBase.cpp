#include "include/JSListenerBase.h"

namespace wrapper
{
    namespace jsbhelper
    {
        // string toolkit
        static inline void split(const std::string &src, const std::string &token, std::vector<std::string> &vect)
        {
            size_t nend = 0;
            size_t nbegin = 0;
            size_t tokenSize = token.size();
            while (nend != std::string::npos)
            {
                nend = src.find(token, nbegin);
                if (nend == std::string::npos)
                    vect.push_back(src.substr(nbegin, src.length() - nbegin));
                else
                    vect.push_back(src.substr(nbegin, nend - nbegin));
                nbegin = nend + tokenSize;
            }
        }

        void JSListenerBase::setJSDelegate(const se::Value &jsDelegate)
        {
            _JSDelegate.setObject(jsDelegate.toObject(), true);
        }

        const se::Value &JSListenerBase::getJSDelegate()
        {
            return _JSDelegate;
        }

        void JSListenerBase::invokeJSFun(const std::string &funName, const se::ValueArray &params)
        {
            for (int i = 0; i < params.size(); i++)
            {
                const se::Value &param = params.at(i);
                if (param.isObject())
                {
                    param.toObject()->root();
                }
            }
        #if CC_VERSION_3_X
            CC_CURRENT_ENGINE()->getScheduler()->
        #else
            cocos2d::Application::getInstance()->getScheduler()->
        #endif
            performFunctionInCocosThread([funName, params, this]() {
                this->invokeJSFunNow(funName, params);
            });
        }

        void JSListenerBase::invokeJSFunNow(const std::string &funName, const se::ValueArray &params)
        {
            se::ScriptEngine::getInstance()->clearException();
            se::AutoHandleScope hs;
            if (!_JSDelegate.isObject())
                return;

            se::Value func;
            _JSDelegate.toObject()->getProperty(funName.c_str(), &func);

            if (func.isObject() && func.toObject()->isFunction())
            {
                bool ok = func.toObject()->call(params, _JSDelegate.toObject());
                if (!ok)
                {
                    se::ScriptEngine::getInstance()->clearException();
                }
            }
            for (int i = 0; i < params.size(); i++)
            {
                const se::Value &param = params.at(i);
                if (param.isObject())
                {
                    param.toObject()->unroot();
                }
            }
        }

        se::Value getPluginValue(se::Object *obj, const std::string &name)
        {
            std::vector<std::string> vect;
            split(name, ".", vect);

            se::Value parent(obj, true);
            se::Value ret;
            for (auto n : vect)
            {
                se::Object *pObj = parent.toObject();
                if (nullptr == pObj)
                {
                    // shoudn't be here
                    break;
                }
                if (!pObj->getProperty(n.c_str(), &ret))
                {
                    // shouldn't be here
                    break;
                }
                parent.setObject(ret.toObject(), true);
            }
            return ret;
        }
    }
}
