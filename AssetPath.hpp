/* Class containing static functions for constructing temporary paths for asset loading.
 * Author: Adam "beckadamtheinventor" Beckingham
 * License: MIT
 */
#pragma once

#include <cstring>
static const char *assetPathTextures = "assets/textures/";
static const char *assetPathObjects = "assets/objects/";
static const char *assetPathLevels = "assets/levels/";
static const char *assetPathMaps = "assets/maps/";
static const char *assetPathRoot = "assets/";
static char assetPathBuffer[512] = {0};

class AssetPath {
    public:
	/* Return a path to "<path><name>.<type>". Writes the data to p. */
    static char* concat(char *p, const char *path, const char *name, const char *type) {
        memcpy(p, path, strlen(path));
        memcpy(&p[strlen(path)], name, strlen(name));
        if (type == nullptr || type[0] == 0) {
            p[strlen(path) + strlen(name)] = 0;
        } else {
            p[strlen(path) + strlen(name)] = '.';
            memcpy(&p[strlen(path) + strlen(name) + 1], type, strlen(type));
            p[strlen(path) + strlen(name) + 1 + strlen(type)] = 0;
        }
        // printf("AssetPath: %s\n", p);
        return p;
    }
    /* Return a path to "assets/textures/<name>.<type>".
       Note that the memory where the path is stored is overwritten next time an AssetPath function is called */
    static inline char* texture(const char* name, const char* type="png") {
        return concat(assetPathBuffer, assetPathTextures, name, type);
    }
    /* Return a path to "assets/objects/<name>.<type>".
       Note that the memory where the path is stored is overwritten next time an AssetPath function is called */
    static inline char* object(const char* name, const char* type="obj") {
        return concat(assetPathBuffer, assetPathObjects, name, type);
    }
    /* Return a path to "assets/levels/<name>.<type>".
       Note that the memory where the path is stored is overwritten next time an AssetPath function is called */
    static inline char* level(const char* name, const char* type="dat") {
        return concat(assetPathBuffer, assetPathLevels, name, type);
    }
    /* Return a path to "assets/levels/<name>.<type>".
       Note that the memory where the path is stored is overwritten next time an AssetPath function is called */
    static inline char* map(const char* name, const char* type="dat") {
        return concat(assetPathBuffer, assetPathMaps, name, type);
    }
    /* Return a path to "assets/<name>.<type>".
       Note that the memory where the path is stored is overwritten next time an AssetPath function is called */
    static inline char* root(const char* name, const char* type="dat") {
        return concat(assetPathBuffer, assetPathRoot, name, type);
    }
};