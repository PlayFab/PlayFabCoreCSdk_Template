#pragma once

#include <playfab/PFPlatform.h>

namespace PlayFab
{
namespace Detail
{

PFLocalStorageHooks& GetLocalStorageHandlers();
HRESULT SetLocalStorageHandlers(PFLocalStorageHooks& hooks);

}

}
