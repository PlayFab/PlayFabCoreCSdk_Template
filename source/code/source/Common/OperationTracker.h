// Global class that tracks ongoing operations in the SDK
//
// Needs the ability to cancel operations as well track when they have completed

#include "CancellationToken.h"
#include "AsyncOp.h"

namespace PlayFab
{

class OperationTracker
{
public:
    OperationTracker();
    OperationTracker(OperationTracker const&) = delete;
    OperationTracker(OperationTracker&&) = delete;
    OperationTracker& operator=(OperationTracker const&) = delete;
    OperationTracker& operator=(OperationTracker&&) = delete;

    HRESULT AddRunContext(void* operation, CancellationToken cancellationToken);
    HRESULT RemoveRunContext(void* operation);

    AsyncOp<void> CancelOperations();
};

}
