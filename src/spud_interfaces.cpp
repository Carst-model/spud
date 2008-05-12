/*  Copyright (C) 2006 Imperial College London and others.
    
    Please see the AUTHORS file in the main source directory for a full list
    of copyright holders.

    Prof. C Pain
    Applied Modelling and Computation Group
    Department of Earth Science and Engineering
    Imperial College London

    C.Pain@Imperial.ac.uk
    
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation,
    version 2.1 of the License.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
    USA
*/

#include "cspud.h"
#include "spud.h"

using namespace std;

using namespace Spud;

extern "C" {
  void spud_load_options(const char* key, const int* key_len)
  {
    OptionManager::load_options(string(key, *key_len));

    return;
  }
  
  void spud_write_options(const char* key, const int* key_len)
  {
    OptionManager::write_options(string(key, *key_len));

    return;
  }
  
  int spud_get_child_name(const char* key, const int* key_len, const int* index, char* child_name, const int* child_name_len){
    string child_name_handle;
    OptionError get_name_err = OptionManager::get_child_name(string(key, *key_len), *index, child_name_handle);
    if(get_name_err != SPUD_NO_ERROR){
      return get_name_err;
    }
    
    int copy_len = (int)child_name_handle.size() > *child_name_len ? *child_name_len : child_name_handle.size();
    memcpy(child_name, child_name_handle.c_str(), copy_len);
    
    return SPUD_NO_ERROR;
  }

  int spud_number_of_children(const char* key, const int* key_len){
    return OptionManager::number_of_children(string(key, *key_len));
  }
  
  int spud_option_count(const char* key, const int* key_len){
    return OptionManager::option_count(string(key, *key_len));
  }
  
  int spud_have_option(const char* key, const int* key_len){
    return OptionManager::have_option(string(key, *key_len)) ? 1 : 0;
  }
  
  int spud_get_option_type(const char* key, const int* key_len, int* type){
    OptionType type_handle;
    OptionError get_type_err = OptionManager::get_option_type(string(key, *key_len), type_handle);
    if(get_type_err != SPUD_NO_ERROR){
      return get_type_err;
    }
    
    *type = type_handle;
    
    return SPUD_NO_ERROR;
  }

  int spud_get_option_rank(const char* key, const int* key_len, int* rank){
    return OptionManager::get_option_rank(string(key, *key_len), *rank);
  }
  
  int spud_get_option_shape(const char* key, const int* key_len, int* shape){
    vector<int> shape_handle;
    OptionError get_shape_err = OptionManager::get_option_shape(string(key, *key_len), shape_handle);
    if(get_shape_err != SPUD_NO_ERROR){
      return get_shape_err;
    }
    
    shape[0] = shape_handle[0];  shape[1] = shape_handle[1];
    
    return SPUD_NO_ERROR;
  }
  
  int spud_get_option(const char* key, const int* key_len, void* val){
    string key_handle(key, *key_len);
  
    OptionType type;
    OptionError get_type_err = OptionManager::get_option_type(key_handle, type);
    if(get_type_err != SPUD_NO_ERROR){
      return get_type_err;
    }
    
    int rank;
    OptionError get_rank_err = OptionManager::get_option_rank(key_handle, rank);
    if(get_rank_err != SPUD_NO_ERROR){
      return get_rank_err;
    }

    if(type == SPUD_DOUBLE){
      if(rank == 0){
        double val_handle;
        OptionError get_err = OptionManager::get_option(key_handle, val_handle);
        if(get_err != SPUD_NO_ERROR){
          return get_err;
        }
        *((double*)val) = val_handle;
      }else if(rank == 1){
        vector<double> val_handle;
        OptionError get_err = OptionManager::get_option(key_handle, val_handle);
        if(get_err != SPUD_NO_ERROR){
          return get_err;
        }
        for(size_t i = 0;i < val_handle.size();i++){
          ((double*)val)[i] = val_handle[i];
        }
      }else if(rank == 2){
        vector< vector<double> > val_handle;
        OptionError get_err = OptionManager::get_option(key_handle, val_handle);
        if(get_err != SPUD_NO_ERROR){
          return get_err;
        }
        for(size_t i = 0;i < val_handle.size();i++){
          for(size_t j = 0;j < val_handle[0].size();j++){
            ((double*)val)[i * val_handle[0].size() + j] = val_handle[i][j];
          }
        }
      }else{
        return SPUD_RANK_ERROR;
      }
    }else if(type == SPUD_INT){
      if(rank == 0){
        int val_handle;
        OptionError get_err = OptionManager::get_option(key_handle, val_handle);
        if(get_err != SPUD_NO_ERROR){
          return get_err;
        }
        *((int*)val) = val_handle;
      }else if(rank == 1){
        vector<int> val_handle;
        OptionError get_err = OptionManager::get_option(key_handle, val_handle);
        if(get_err != SPUD_NO_ERROR){
          return get_err;
        }
        for(size_t i = 0;i < val_handle.size();i++){
          ((int*)val)[i] = val_handle[i];
        }
      }else if(rank == 2){
        vector< vector<int> > val_handle;
        OptionError get_err = OptionManager::get_option(key_handle, val_handle);
        if(get_err != SPUD_NO_ERROR){
          return get_err;
        }
        for(size_t i = 0;i < val_handle.size();i++){
          for(size_t j = 0;j < val_handle[0].size();j++){
            ((int*)val)[i * val_handle[0].size() + j] = val_handle[i][j];
          }
        }
      }else{
        return SPUD_RANK_ERROR;
      }
    }else if(type == SPUD_STRING){
      string val_handle;
      OptionError get_err = OptionManager::get_option(key_handle, val_handle);
      if(get_err != SPUD_NO_ERROR){
        return get_err;
      }
      memcpy(val, val_handle.c_str(), val_handle.size() * sizeof(char));
    }else{
      return SPUD_TYPE_ERROR;
    }
    
    return SPUD_NO_ERROR;
  }
  
  int spud_add_option(const char* key, const int* key_len){
    return OptionManager::add_option(string(key, *key_len));
  }
  
  int spud_set_option(const char* key, const int* key_len, const void* val, const int* type, const int* rank, const int* shape){
    string key_handle(key, *key_len);

    if(*type == SPUD_DOUBLE){
      if(*rank == 0){
        double val_handle = *((double*)val);
        return OptionManager::set_option(key_handle, val_handle);
      }else if(*rank == 1){
        vector<double> val_handle;
        for(int i = 0;i < shape[0];i++){
          val_handle.push_back(((double*)val)[i]);
        }
        return OptionManager::set_option(key_handle, val_handle);
      }else if(*rank == 2){
        vector< vector<double> > val_handle;
        for(int i = 0;i < shape[0];i++){
          val_handle.push_back(vector<double>());
          for(int j = 0;j < shape[1];j++){
            val_handle[i].push_back(((double*)val)[i * val_handle[0].size() + j]);
          }
        }
        return OptionManager::set_option(key_handle, val_handle);    
      }else{
        return SPUD_RANK_ERROR;
      }
    }else if(*type == SPUD_INT){
      if(*rank == 0){
        int val_handle = *((int*)val);
        return OptionManager::set_option(key_handle, val_handle);
      }else if(*rank == 1){
        vector<int> val_handle;
        for(int i = 0;i < shape[0];i++){
          val_handle.push_back(((int*)val)[i]);
        }
        return OptionManager::set_option(key_handle, val_handle);
      }else if(*rank == 2){
        vector< vector<int> > val_handle;
        for(int i = 0;i < shape[0];i++){
          val_handle.push_back(vector<int>());
          for(int j = 0;j < shape[1];j++){
            val_handle[i].push_back(((int*)val)[i * val_handle[0].size() + j]);
          }
        }
        return OptionManager::set_option(key_handle, val_handle);
      }else{
        return SPUD_RANK_ERROR;
      }
    }else if(*type == SPUD_STRING){
      return OptionManager::set_option(key_handle, string((char*)val, shape[0]));
    }else{
      return SPUD_TYPE_ERROR;
    }
    
    return SPUD_NO_ERROR;
  }
   
  int spud_set_option_attribute(const char* key, const int* key_len, const char* val, const int* val_len){
    return OptionManager::set_option_attribute(string(key, *key_len), string(val, *val_len));
  }
   
  int spud_delete_option(const char* key, const int* key_len){
    return OptionManager::delete_option(string(key, *key_len));
  }
}
