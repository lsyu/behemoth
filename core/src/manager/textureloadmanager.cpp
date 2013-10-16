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
#include "gli/gli.h"
#include <GL/gl.h>

namespace Core {

using namespace std;

TextureLoadManager *TextureLoadManager::instance = nullptr;

class __TextureLoaderManagerImplDel {
public:
    explicit __TextureLoaderManagerImplDel(TextureLoadManager *tlManager) : tlManager(tlManager) {}
    ~__TextureLoaderManagerImplDel() {delete tlManager;}
private:
    TextureLoadManager *tlManager;
};

TextureLoadManager* TextureLoadManager::getInstance()
{
    if (!instance) {
        instance = new TextureLoadManager();
        static __TextureLoaderManagerImplDel delHelper(instance);
    }
    return instance;
}


TextureLoadManager::TextureLoadManager() : textures(std::map<std::string, uint>())
{
}

TextureLoadManager::~TextureLoadManager()
{
    for (std::map<std::string, uint>::const_iterator it = textures.begin(), end = textures.end();
            it != end; ++it)
        glDeleteTextures(1, &(it->second));
}

bool TextureLoadManager::loadTexture(const string &name, const string &fileName)
{
    if (textures.find(name) != textures.end())
        return false; // уже загружена

    gli::texture2D im(gli::loadStorageDDS(
            ResourceManager::getInstance()->getTextureFolder()
            + ResourceManager::getInstance()->getFileSeparator()
            + fileName));

    if (im.empty())
        return false; // файл не найден или невозможно открыть

    // генерим текстуру
    uint t;
    glGenTextures(1, &t);

    // делаем ее активной
    glBindTexture(GL_TEXTURE_2D, t);

    // фильтрации текстуры - линейная фильтрация
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // параметры "оборачивания" текстуры - отсутствие оборачивания
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // загрузм данные о цвете
    //! TODO: Подумать над форматами
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 gli::internal_format(im.format())/*GL_RGB8*/,
                 im.dimensions().x, im.dimensions().y,
                 0,
                 gli::type_format(im.format())/*GL_BGR*/,
                 GL_UNSIGNED_BYTE,
                 im.data());

    //! TODO: сделать проверку корректности bool checkOGL();

    // добавим в наш словарь
    textures[name] = t;

    // возвращаем начальное состояние
    glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

uint TextureLoadManager::getTexture(const string &name) const
{
    std::map<std::string, uint>::const_iterator texture = textures.find(name);
    return (texture == textures.end()) ? 0 : texture->second;
}

} // namespace Core
