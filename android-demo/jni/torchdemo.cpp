/*
 * Copyright (C) 2013 Soumith Chintala
 *
 */
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include "torchandroid.h"
#include <assert.h>

extern "C" {
  
  JNIEXPORT jstring JNICALL
  Java_com_torch_torchdemo_TorchDemo_callTorch( JNIEnv* env,
                                                jobject thiz,
                                                jobject assetManager) {
    D("Hello from C");
    // get native asset manager
    AAssetManager* manager = AAssetManager_fromJava(env, assetManager);
    assert( NULL != manager);
    
    char buffer[4096]; // buffer for textview output
    
    lua_State *L = inittorch(manager); // create a lua_State
    // load and run file
    char file[] = "main.lua";
    int ret;
    long size = android_asset_get_size(file);
    if (size != -1) {
      char *filebytes = android_asset_get_bytes(file);
      ret = luaL_dobuffer(L, filebytes, size, "main");
    }
    // check if script ran succesfully. If not, print error to logcat
    if (ret == 1) {
      D("Error doing resource: %s\n", file);
      D(lua_tostring(L,-1));
      strlcat(buffer, lua_tostring(L,-1), sizeof(buffer));
    }
    else {
	  lua_getfield(L, LUA_GLOBALSINDEX, "imsz_x");
	  
	  lua_Number imsz_x = lua_tonumber(L,-1);
	  
	  size_t len;
	  lua_getfield(L, LUA_GLOBALSINDEX, "output_str");
	  
	  const char     * str = lua_tolstring(L, -1, &len);

	  sprintf(buffer,"imsz_x = %0f; output_str=%s; len=%d",imsz_x,str,len);
	  
      //strlcat(buffer,
      //        "Torch script ran succesfully. Check Logcat for more details.",
      //        sizeof(buffer));
    }
    // destroy the Lua State
    lua_close(L);
    return env->NewStringUTF(buffer);
  }
  
}
