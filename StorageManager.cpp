//=============================================================================
// File: StorageManager.cpp
// Commit: 9
// Version: 0.2.0
//=============================================================================
//
// Currently a no-op stub (kept from the original skeleton). Nothing is
// persisted yet - key bindings live entirely in OpenWebRXProfile.cpp and
// are re-applied from flash (i.e. from your compiled sketch) on every
// boot. A natural future upgrade is to load/save the profile tables via
// Arduino's Preferences (NVS) library so bindings could be changed at
// runtime without reflashing; not required just to get this compiling.
//=============================================================================

#include "StorageManager.h"

StorageManager StorageManagerInstance;

void StorageManager::begin()
{
}

bool StorageManager::load()
{
    return true;
}

bool StorageManager::save()
{
    return true;
}
