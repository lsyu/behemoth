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

#ifndef LAUWRAPPERIMPL_H
#define LAUWRAPPERIMPL_H

#include <map>
#include <typeinfo>
#include <typeindex>

#include "lua/lua.h"

// Вспомогательное пространство имен. Не используйте его!
namespace __CLuaWrapper {
extern std::map<std::type_index, std::string> types;

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
   Arg **fromLua = static_cast<Arg **>(lua_newuserdata(l, sizeof(Arg*)));
   *fromLua = new Arg();
   (**fromLua) = arg;
   luaL_getmetatable(l, __CLuaWrapper::types[std::type_index(typeid(Arg))].c_str());
   lua_setmetatable(l, -2);

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
// ^^^ Вспомогательное пространство имен. Не используйте его! ^^^

#endif // LAUWRAPPERIMPL_H
