namespace PlayFab
{

using HANDLE = PFHandle;

// Simple handle table used to track and map open client handles 
template<typename T>
class HandleTable
{
public:
    HandleTable(HANDLE firstHandleValue);
    HandleTable(HandleTable const&) = delete;
    HandleTable(HandleTable&&) = delete;
    HandleTable& operator=(HandleTable const&) = delete;
    HandleTable& operator=(HandleTable&&) = delete;

    HANDLE MakeHandle(SharedPtr<T>&& object);
    void CloseHandle(HANDLE handle);

    SharedPtr<T> FromHandle(HANDLE handle) const;

private:
    mutable std::mutex m_mutex;
    Map<HANDLE, SharedPtr<T>> m_handles;
    HANDLE m_nextHandle;
};

//------------------------------------------------------------------------------
// Template implementations
//------------------------------------------------------------------------------

template<typename T>
HandleTable<T>::HandleTable(HANDLE firstHandleValue) :
    m_nextHandle{ firstHandleValue }
{
}

template<typename T>
HANDLE HandleTable<T>::MakeHandle(SharedPtr<T>&& object)
{
    std::unique_lock<std::mutex> lock{ m_mutex };

    HANDLE h = m_nextHandle++;
    m_handles.emplace(h, std::move(object));

    return h;
}

template<typename T>
void HandleTable<T>::CloseHandle(HANDLE handle)
{
    std::unique_lock<std::mutex> lock{ m_mutex };

    auto it = m_handles.find(handle);
    if (it == m_handles.end())
    {
        assert(false);
        TRACE_WARNING("Attempted to close invalid handle %llu", handle);
    }

    m_handles.erase(it);
}

template<typename T>
SharedPtr<T> HandleTable<T>::FromHandle(HANDLE handle) const
{
    std::unique_lock<std::mutex> lock{ m_mutex };
    auto it = m_handles.find(handle);
    if (it == m_handles.end())
    {
        assert(false);
        TRACE_WARNING("Attempted to close invalid handle %llu", handle);
    }

    assert(it->second);
    return it->second;
}

}