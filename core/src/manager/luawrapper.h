/*
 * Labs4Physics - visualisation of physics process
 * Copyright (C) 2013  Leyko Sergey powt81lsyu@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef LUAWRAPPER_H
#define LUAWRAPPER_H

#include <string>
#include <vector>
#include <map>
#include <typeinfo>
#include <typeindex>

#include "lua/lua.h"

namespace __CLuaWrapper {
static std::map<std::type_index, std::string> types;

template<typename Arg>
Arg *checkUserData(lua_State *l, int numArg)  {
    return *static_cast<Arg **>(luaL_checkudata(l, numArg, __CLuaWrapper::types[std::type_index(typeid(Arg))].c_str()));
}

template<typename Arg>
Arg checkType(lua_State *l, int numArg)  {
    return **static_cast<Arg **>(luaL_checkudata(l, numArg, __CLuaWrapper::types[std::type_index(typeid(Arg))].c_str()));
}

template<>
inline int checkType <int> (lua_State *l, int numArg) {
    return static_cast<int>(luaL_checkinteger(l, numArg));
}

template<>
inline float checkType <float> (lua_State *l, int numArg) {
    return static_cast<float>(luaL_checknumber(l, numArg));
}

template<>
inline double checkType <double> (lua_State *l, int numArg) {
    return luaL_checknumber(l, numArg);
}

template<>
inline std::string checkType <std::string> (lua_State *l, int numArg) {
    return luaL_checkstring(l, numArg);
}

template<>
inline const char *checkType <const char*> (lua_State *l, int numArg) {
    return luaL_checkstring(l, numArg);
}

template<typename Arg>
void pushType(lua_State *l, Arg arg) {
    lua_pushlightuserdata(l, reinterpret_cast<void*>(&arg));
}

template<>
inline void pushType(lua_State *l, const std::string &arg) {
    lua_pushstring(l, arg.c_str());
}

template<>
inline void pushType(lua_State *l, const char *arg) {
    lua_pushstring(l, arg);
}

template<>
inline void pushType(lua_State *l, int arg) {
    lua_pushinteger(l, arg);
}

template<>
inline void pushType(lua_State *l, float arg) {
    lua_pushnumber(l, arg);
}

template<>
inline void pushType(lua_State *l, double arg) {
    lua_pushnumber(l, arg);
}

// Arg(T::*func)() const
template<typename T, typename Arg, typename Fun, int id>
class GetterAdapter {
public:
    explicit GetterAdapter(Fun fun) : fun(fun) {}

    int operator() (lua_State *l) {
        T *t = __CLuaWrapper::checkUserData<T>(l, 1);
        Arg param = (t->*fun)();
        __CLuaWrapper::pushType<Arg>(l, param);
        return 1;
    }
private:
    Fun fun;
}; // class GetterAdapter

// void(T::*func)(Arg)
template<typename T, typename Arg, typename Fun, int id>
class SetterAdapter {
public:
    explicit SetterAdapter(Fun fun) : fun(fun) {}

    int operator() (lua_State *l) {
        T *t = __CLuaWrapper::checkUserData<T>(l, 1);
        Arg arg = __CLuaWrapper::checkType<Arg>(l, 2);
        (t->*fun)(arg);
        return 1;
    }
private:
    Fun fun;
}; // class SetterAdapter

// Arg T::*m
template<typename T, typename Arg, typename Member, int id>
class GetMemberAdapter {
public:
    explicit GetMemberAdapter(Member m) : m(m) {}

    int operator() (lua_State *l) {
        T *t = __CLuaWrapper::checkUserData<T>(l, 1);
        Arg param = t->*m;
        __CLuaWrapper::pushType<Arg>(l, param);
        return 1;
    }
private:
    Member m;
}; // class GetMemberAdapter

// Arg T::*m
template<typename T, typename Arg, typename Member, int id>
class SetMemberAdapter {
public:
    explicit SetMemberAdapter(Member m) : m(m) {}

    int operator() (lua_State *l) {
        T *t = __CLuaWrapper::checkUserData<T>(l, 1);
        Arg arg = __CLuaWrapper::checkType<Arg>(l, 2);
        t->*m = arg;
        return 1;
    }
private:
    Member m;
}; // class SetMemberAdapter

template<typename T, typename Arg, typename Fun, int id>
lua_CFunction getterAdapterInC(Fun fun)
{
    static GetterAdapter<T, Arg, Fun, id> my_functor(fun);
    return [](lua_State *l) {
        return my_functor(l);
    };
} // getterAdapterInC

template<typename T, typename Arg, typename Fun, int id>
lua_CFunction setterAdapterInC(Fun fun)
{
    static SetterAdapter<T, Arg, Fun, id > my_functor(fun);
    return [](lua_State *l) {
        return my_functor(l);
    };
} // setterAdapterInC

template<typename T, typename Arg, typename Member, int id>
lua_CFunction getMemberAdapterInC(Member m)
{
    static GetMemberAdapter<T, Arg, Member, id> my_functor(m);
    return [](lua_State *l) {
        return my_functor(l);
    };
} // getterAdapterInC

template<typename T, typename Arg, typename Member, int id>
lua_CFunction setMemberAdapterInC(Member m)
{
    static SetMemberAdapter<T, Arg, Member, id> my_functor(m);
    return [](lua_State *l) {
        return my_functor(l);
    };
} // setterAdapterInC

} // namespace __CLuaWrapper



template <typename T>
class CLuaWrapper
{
public:
    CLuaWrapper(lua_State *lua, const std::string &name) : lua(lua), nameOfGlobal(name),
        nameOfMetaTable(std::string("luaL_") + name), lReg(), lRegMemHelper()  {
    }

    /**
     * @brief Сгенерировать конструктор класса
     */
    void addConstructor() {
        __CLuaWrapper::types[std::type_index(typeid(T))] = nameOfMetaTable;
        luaL_Reg constructor = {
            "new", [](lua_State *l) {
                T **userData = newUserData<T>(l);
                *userData = new T;
                luaL_getmetatable(l, __CLuaWrapper::types[std::type_index(typeid(T))].c_str());
                lua_setmetatable(l, -2);
                return 1;
            }
        };
        lReg.push_back(constructor);
    }

    /**
     * @brief Сгенерировать конструктор класса
     */
    template <typename Arg>
    void addConstructor() {
        __CLuaWrapper::types[std::type_index(typeid(T))] = nameOfMetaTable;
        luaL_Reg constructor = {
            "new", [](lua_State *l) {
                Arg arg = __CLuaWrapper::checkType<Arg>(l, 1);
                T **userData = newUserData<T>(l);
                *userData = new T(arg);
                luaL_getmetatable(l, __CLuaWrapper::types[std::type_index(typeid(T))].c_str());
                lua_setmetatable(l, -2);
                return 1;
            }
        };
        lReg.push_back(constructor);
    }

    /**
     * @brief Сгенерировать конструктор класса
     */
    template <typename Arg1, typename Arg2>
    void addConstructor() {
        __CLuaWrapper::types[std::type_index(typeid(T))] = nameOfMetaTable;
        luaL_Reg constructor = {
            "new", [](lua_State *l) {
                Arg1 arg1 = __CLuaWrapper::checkType<Arg1>(l, 1);
                Arg2 arg2 = __CLuaWrapper::checkType<Arg2>(l, 2);
                T **userData = newUserData<T>(l);
                *userData = new T(arg1, arg2);
                luaL_getmetatable(l, __CLuaWrapper::types[std::type_index(typeid(T))].c_str());
                lua_setmetatable(l, -2);
                return 1;
            }
        };
        lReg.push_back(constructor);
    }

    /**
     * @brief Сгенерировать конструктор класса
     */
    template <typename Arg1, typename Arg2, typename Arg3>
    void addConstructor() {
        __CLuaWrapper::types[std::type_index(typeid(T))] = nameOfMetaTable;
        luaL_Reg constructor = {
            "new", [](lua_State *l) {
                Arg1 arg1 = __CLuaWrapper::checkType<Arg1>(l, 1);
                Arg2 arg2 = __CLuaWrapper::checkType<Arg2>(l, 2);
                Arg2 arg3 = __CLuaWrapper::checkType<Arg2>(l, 3);
                T **userData = newUserData<T>(l);
                *userData = new T(arg1, arg2, arg3);
                luaL_getmetatable(l, __CLuaWrapper::types[std::type_index(typeid(T))].c_str());
                lua_setmetatable(l, -2);
                return 1;
            }
        };
        lReg.push_back(constructor);
    }

    /**
     * @brief Добавить свойство типа Arg с именем name
     */
    template <typename Arg, int id>
    void addProperty(const std::string &name, Arg(T::*getter)() const, void(T::*setter)(const Arg&)) {
        lRegMemHelper.push_back(std::string("get") + name);
        luaL_Reg get = {
            lRegMemHelper.back().c_str(),
             __CLuaWrapper::getterAdapterInC<T, Arg, Arg(T::*)() const, id >(getter)
        };
        lRegMemHelper.push_back(std::string("set") + name);
        luaL_Reg set = {
           lRegMemHelper.back().c_str(),
            __CLuaWrapper::setterAdapterInC<T, Arg, void(T::*)(const Arg&), id > (setter)
        };
        lReg.push_back(get);
        lReg.push_back(set);
    }

    /**
     * @brief Добавить свойство типа Arg с именем name
     */
    template <typename Arg, int id>
    void addProperty(const std::string &name, Arg(T::*getter)() const, void(T::*setter)(Arg)) {
        lRegMemHelper.push_back(std::string("get") + name);
        luaL_Reg get = {
            lRegMemHelper.back().c_str(),
             __CLuaWrapper::getterAdapterInC<T, Arg, Arg(T::*)() const, id>(getter)
        };
        lRegMemHelper.push_back(std::string("set") + name);
        luaL_Reg set = {
           lRegMemHelper.back().c_str(),
            __CLuaWrapper::setterAdapterInC<T, Arg, void(T::*)(Arg), id > (setter)
        };
        lReg.push_back(get);
        lReg.push_back(set);
    }

    /**
     * @brief Добавить свойство типа Arg с именем name
     */
    template <typename Arg, int id>
    void addProperty(const std::string &name, Arg(T::*getter)(), void(T::*setter)(Arg)) {
        lRegMemHelper.push_back(std::string("get") + name);
        luaL_Reg get = {
            lRegMemHelper.back().c_str(),
             __CLuaWrapper::getterAdapterInC<T, Arg, Arg(T::*)(), id >(getter)
        };
        lRegMemHelper.push_back(std::string("set") + name);
        luaL_Reg set = {
           lRegMemHelper.back().c_str(),
            __CLuaWrapper::setterAdapterInC<T, Arg, void(T::*)(Arg), id > (setter)
        };
        lReg.push_back(get);
        lReg.push_back(set);
    }

    /**
     * @brief Добавить свойство типа Arg с именем name
     */
    template <typename Arg, int id>
    void addProperty(const std::string &name, Arg T::*member) {
        lRegMemHelper.push_back(std::string("get") + name);
        luaL_Reg get = {
            lRegMemHelper.back().c_str(),
             __CLuaWrapper::getMemberAdapterInC<T, Arg, Arg T::*, id >(member)
        };
        lRegMemHelper.push_back(std::string("set") + name);
        luaL_Reg set = {
           lRegMemHelper.back().c_str(),
            __CLuaWrapper::setMemberAdapterInC<T, Arg, Arg T::*, id > (member)
        };
        lReg.push_back(get);
        lReg.push_back(set);
    }

    /**
     * @brief Добавить свойство типа Arg с именем name
     */
    void addProperty(const luaL_Reg &member) {
        lReg.push_back(member);
    }

    /**
     * @brief Добавить деструктор
     */
    void addDestructor() {
        luaL_Reg constructor = {
            "__gc", [](lua_State *l) {
                T *userData = __CLuaWrapper::checkUserData<T>(l, 1);
                delete userData;
                return 0;
            }
        };
        lReg.push_back(constructor);
    }

    /**
     * @brief Завершить конструирование обертки, сгенерировав все необходимое для
     * общения С++ - Lua
     */
    void complete() {
        lReg.push_back({NULL, NULL});
        luaL_newmetatable(lua, nameOfMetaTable.c_str());
        luaL_setfuncs(lua, &lReg[0], 0);
        lua_pushvalue(lua, -1);
        lua_setfield(lua, -1, "__index");
        lua_setglobal(lua, nameOfGlobal.c_str());
    }

protected:
    template <typename Arg>
    static Arg** newUserData(lua_State *l) {
        return static_cast<Arg **>(lua_newuserdata(l, sizeof(Arg*)));
    }

private:
    CLuaWrapper(const CLuaWrapper &);
    const CLuaWrapper &operator= (const CLuaWrapper &);

    lua_State *lua;
    std::string nameOfGlobal;
    std::string nameOfMetaTable;
    std::vector<luaL_Reg> lReg;
    std::vector<std::string> lRegMemHelper; // для корректного хранения строк в luaL_Reg
};

#endif // LUAWRAPPER_H
