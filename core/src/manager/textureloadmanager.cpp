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

#include "textureloadmanager.h"
#include "resourcemanager.h"

#include <iostream>

#include "core/ogl/ogl.h"
#include "gli/gli.h"
#include "gli/glitexture2d.h"

namespace core {

using namespace std;

CTextureLoadManager *CTextureLoadManager::instance = nullptr;

class __CTextureLoaderManagerImplDel {
public:
    explicit __CTextureLoaderManagerImplDel(CTextureLoadManager *tlManager) : tlManager(tlManager) {}
    ~__CTextureLoaderManagerImplDel() {delete tlManager;}
private:
    CTextureLoadManager *tlManager;
};

CTextureLoadManager* CTextureLoadManager::getInstance()
{
    if (!instance) {
        instance = new CTextureLoadManager();
        static __CTextureLoaderManagerImplDel delHelper(instance);
    }
    return instance;
}


CTextureLoadManager::CTextureLoadManager() : textures(std::map<std::string, uint>())
{
}

CTextureLoadManager::~CTextureLoadManager()
{
    for (std::map<std::string, uint>::const_iterator it = textures.begin(), end = textures.end();
            it != end; ++it)
        glDeleteTextures(1, &(it->second));
}

uint CTextureLoadManager::loadTexture(const string &name, const string &fileName)
{
    if (textures.find(name) != textures.end())
        return false; // уже загружена

//    gli::texture2D im(gli::loadStorageDDS(fileName));

//    if (im.empty())
//        return 0; // файл не найден или невозможно открыть

//    // генерим текстуру
//    uint t;
//    glActiveTexture(GL_TEXTURE0);
//    glGenTextures(1, &t);
//    //glEnable(GL_TEXTURE_2D);
//    //glActiveTexture(GL_TEXTURE0);

//    // делаем ее активной
//    glBindTexture(GL_TEXTURE_2D, t);
//    GLenum error = glGetError();

//    // фильтрации текстуры - линейная фильтрация
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//    // параметры "оборачивания" текстуры - отсутствие оборачивания
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

//    error = glGetError();
//    // загрузм данные о цвете
//    //! TODO: Подумать над форматами

//    glTexImage2D(GL_TEXTURE_2D,
//                 im.levels(),
//                 gli::internal_format(im.format())/*GL_RGB8*/,
//                 im.dimensions().x, im.dimensions().y,
//                 0,
//                 gli::type_format(im.format())/*GL_BGR*/,
//                 GL_UNSIGNED_BYTE,
//                 im.data());

//    error = glGetError();


    //! TODO: сделать проверку корректности bool checkOGL();

    uint t = gli::createTexture2D(fileName);

    // добавим в наш словарь
    textures[name] = t;

    // возвращаем начальное состояние
    glBindTexture(GL_TEXTURE_2D, 0);

    return t;
}

uint CTextureLoadManager::getTexture(const string &name)
{
    std::map<std::string, uint>::const_iterator texture = textures.find(name);
    CResourceManager *res = CResourceManager::getInstance();
    if (texture == textures.end())
        return loadTexture(name, res->getTextureFolder()+ res->getFileSeparator() + name + ".dds");
    return texture->second;
}

} // namespace Core
