//=============================================================================
// File: StorageManager.h
// Commit: 7
//=============================================================================

#ifndef STORAGE_MANAGER_H
#define STORAGE_MANAGER_H

class StorageManager
{
public:
    void begin();

    bool load();
    bool save();
};

extern StorageManager StorageManagerInstance;

#endif