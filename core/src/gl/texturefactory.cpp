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

#include "texturefactory.h"
#include "core/manager/resourcemanager.h"
#include "core/fonts/fontfactory.h"
#include "core/ogl/ogl.h"

#include "gli/gli.h"

namespace core {

using namespace std;

CTextureFactory *CTextureFactory::instance = nullptr;

class __CTextureFactoryImplDel {
public:
    explicit __CTextureFactoryImplDel(CTextureFactory *tlManager) : tlManager(tlManager) {}
    ~__CTextureFactoryImplDel() {delete tlManager;}
private:
    CTextureFactory *tlManager;
};

CTextureFactory* CTextureFactory::getInstance()
{
    if (!instance) {
        instance = new CTextureFactory();
        static __CTextureFactoryImplDel delHelper(instance);
    }
    return instance;
}


CTextureFactory::CTextureFactory() : textures(std::map<std::string, uint>())
{
}

CTextureFactory::~CTextureFactory()
{
    for (std::map<std::string, uint>::const_iterator it = textures.begin(), end = textures.end();
            it != end; ++it)
        glDeleteTextures(1, &(it->second));
}

unsigned int CTextureFactory::createTexture2D(const std::string &filename)
{
    gli::texture2D Texture(gli::load_dds(filename.c_str()));
    if(Texture.empty())
        return 0;

    gli::detail::format_desc Desc = gli::detail::getFormatInfo(Texture.format());

    GLint Alignment = 0;
    GLint CurrentTextureName = 0;
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &Alignment);
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &CurrentTextureName);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    GLuint Name = 0;
    glGenTextures(1, &Name);
    glBindTexture(GL_TEXTURE_2D, Name);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Texture.levels() > 1 ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if(gli::is_compressed((Texture.format()))) {
        for(gli::texture2D::size_type Level = 0; Level < Texture.levels(); ++Level) {
            glCompressedTexImage2D(
                        GL_TEXTURE_2D,
                        GLint(Level),
                        Desc.Internal,
                        GLsizei(Texture[Level].dimensions().x),
                        GLsizei(Texture[Level].dimensions().y),
                        0,
                        GLsizei(Texture[Level].size()),
                        Texture[Level].data());
        }
    } else {
        for(gli::texture2D::size_type Level = 0; Level < Texture.levels(); ++Level) {
            glTexImage2D(
                        GL_TEXTURE_2D,
                        GLint(Level),
                        Desc.Internal,
                        GLsizei(Texture[Level].dimensions().x),
                        GLsizei(Texture[Level].dimensions().y),
                        0,
                        Desc.External,
                        Desc.Type,
                        Texture[Level].data());
        }
    }

    // Restaure previous states
    glBindTexture(GL_TEXTURE_2D, GLuint(CurrentTextureName));
    glPixelStorei(GL_UNPACK_ALIGNMENT, Alignment);

    return Name;
}

uint CTextureFactory::loadTexture(const string &name, const string &fileName)
{
    if (textures.find(name) != textures.end())
        return false; // уже загружена

    uint t = createTexture2D(fileName);

    // добавим в наш словарь
    textures[name] = t;

    // возвращаем начальное состояние
    glBindTexture(GL_TEXTURE_2D, 0);

    return t;
}

uint CTextureFactory::getTexture(const string &name)
{
    std::map<std::string, uint>::const_iterator texture = textures.find(name);
    if (texture == textures.end()) {
        CResourceManager *res = CResourceManager::getInstance();
        return loadTexture(name, res->getTextureFolder()+ res->getFileSeparator() + name + ".dds");
    }
    return texture->second;
}

CSymbolTexture CTextureFactory::getSymbol(char symbol, const CFont &font)
{
    std::map<char, CSymbolTexture>::const_iterator s = symbols.find(symbol);
    CSymbolTexture retSymbol;
    if (s == symbols.end()) {
        CTextBuffer buffer = CFontFactory::getInstance()->getTextBuffer(symbol, font);
        uint retTexture = getTexture(buffer);
        retSymbol.texture = retTexture;
        retSymbol.width = static_cast<float>(buffer.width);
        retSymbol.height = static_cast<float>(buffer.height);
        symbols[symbol] = retSymbol;
    } else {
        retSymbol = s->second;
    }
    return retSymbol;
}

uint CTextureFactory::getTexture(const CTextBuffer &buffer) const
{
    // генерим текстуру

    glEnable(GL_TEXTURE_2D);
    uint t;
    glGenTextures(1, &t);
    glBindTexture(GL_TEXTURE_2D, t);

    // фильтрации текстуры - линейная фильтрация
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 buffer.width, buffer.height,
                 0,
                 GL_BGRA,
                 GL_UNSIGNED_BYTE,
                 buffer.buffer.data());
    return t;
}

} // namespace Core
