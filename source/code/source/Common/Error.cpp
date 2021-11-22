#include "stdafx.h"
#include "Error.h"

namespace PlayFab
{

HRESULT ServiceErrorToHR(ServiceErrorCode errorCode)
{
    // Translating most global errors that apply to all PlayFab APIs. See 
    // https://docs.microsoft.com/en-us/gaming/playfab/api-references/global-api-method-error-codes for more details about
    // the various global API errors.
    //
    // API specific errors are being translated to E_PF_SERVICEERROR. More details can be found in http response
    // and/or via SDK traces.

    switch (errorCode)
    {
    case ServiceErrorCode::Success:
    {
        return S_OK;
    }
    case ServiceErrorCode::UnkownError:
    case ServiceErrorCode::UnknownError:
    {
        return E_PF_UNKNOWNERROR;
    }
    case ServiceErrorCode::APIClientRequestRateLimitExceeded:
    case ServiceErrorCode::APIConcurrentRequestLimitExceeded:
    case ServiceErrorCode::ConcurrentEditError:
    case ServiceErrorCode::DataUpdateRateExceeded:
    {
        return E_PF_RATELIMITEXCEEDED;
    }
    case ServiceErrorCode::DownstreamServiceUnavailable:
    case ServiceErrorCode::ServiceUnavailable:
    {
        return E_PF_SERVICEUNAVAILABLE;
    }
    case ServiceErrorCode::OverLimit:
    {
        return E_PF_OVERGAMEMANAGERLIMIT;
    }
    case ServiceErrorCode::AccountBanned:
    {
        return E_PF_ACCOUNTBANNED;
    }
    case ServiceErrorCode::AccountDeleted:
    {
        return E_PF_ACCOUNTDELETED;
    }
    case ServiceErrorCode::AccountNotFound:
    {
        return E_PF_ACCOUNTNOTFOUND;
    }
    case ServiceErrorCode::APIRequestsDisabledForTitle:
    {
        return E_PF_APIREQUESTSDISABLEDFORTITLE;
    }
    case ServiceErrorCode::InvalidContentType:
    case ServiceErrorCode::InvalidParams:
    case ServiceErrorCode::InvalidRequest:
    case ServiceErrorCode::InvalidTitleId:
    {
        return E_PF_INVALIDREQUEST;
    }
    case ServiceErrorCode::NotAuthenticated:
    {
        return E_PF_NOTAUTHENTICATED;
    }
    case ServiceErrorCode::NotAuthorized:
    case ServiceErrorCode::NotAuthorizedByTitle:
    {
        return E_PF_NOTAUTHORIZED;
    }
    case ServiceErrorCode::ProfileDoesNotExist:
    {
        return E_PF_PROFILEDOESNOTEXIST;
    }
    case ServiceErrorCode::TitleDeleted:
    {
        return E_PF_TITLEDELETED;
    }
    case ServiceErrorCode::EntityTokenExpired:
    case ServiceErrorCode::EntityTokenRevoked:
    {
        return E_PF_INTERNAL_EXPIREDAUTHTOKEN;
    }
    default:
    {
        // Generic service error
        return E_PF_SERVICEERROR;
    }
    }
}

#define MAKE_HTTP_HRESULT(httpStatus) MAKE_HRESULT(1, 0x019, httpStatus)

HRESULT HttpStatusToHR(uint32_t httpStatus)
{
    // 2xx are http success codes
    if (httpStatus >= 200 && httpStatus < 300)
    {
        return S_OK;
    }
    else if (httpStatus == 1223)
    {
        // MSXML XHR bug: get_status() returns HTTP/1223 for HTTP/204:
        // http://blogs.msdn.com/b/ieinternals/archive/2009/07/23/the-ie8-native-xmlhttprequest-object.aspx
        // treat it as success code as well
        return S_OK;
    }
    else
    {
        switch (httpStatus)
        {
        case 300: return HTTP_E_STATUS_AMBIGUOUS;
        case 301: return HTTP_E_STATUS_MOVED;
        case 302: return HTTP_E_STATUS_REDIRECT;
        case 303: return HTTP_E_STATUS_REDIRECT_METHOD;
        case 304: return HTTP_E_STATUS_NOT_MODIFIED;
        case 305: return HTTP_E_STATUS_USE_PROXY;
        case 306: return HTTP_E_STATUS_REDIRECT_KEEP_VERB;

        case 400: return HTTP_E_STATUS_BAD_REQUEST;
        case 401: return HTTP_E_STATUS_DENIED;
        case 402: return HTTP_E_STATUS_PAYMENT_REQ;
        case 403: return HTTP_E_STATUS_FORBIDDEN;
        case 404: return HTTP_E_STATUS_NOT_FOUND;
        case 405: return HTTP_E_STATUS_BAD_METHOD;
        case 406: return HTTP_E_STATUS_NONE_ACCEPTABLE;
        case 407: return HTTP_E_STATUS_PROXY_AUTH_REQ;
        case 408: return HTTP_E_STATUS_REQUEST_TIMEOUT;
        case 409: return HTTP_E_STATUS_CONFLICT;
        case 410: return HTTP_E_STATUS_GONE;
        case 411: return HTTP_E_STATUS_LENGTH_REQUIRED;
        case 412: return HTTP_E_STATUS_PRECOND_FAILED;
        case 413: return HTTP_E_STATUS_REQUEST_TOO_LARGE;
        case 414: return HTTP_E_STATUS_URI_TOO_LONG;
        case 415: return HTTP_E_STATUS_UNSUPPORTED_MEDIA;
        case 416: return HTTP_E_STATUS_RANGE_NOT_SATISFIABLE;
        case 417: return HTTP_E_STATUS_EXPECTATION_FAILED;
        case 421: return MAKE_HTTP_HRESULT(421); // Misdirected request
        case 422: return MAKE_HTTP_HRESULT(422); // Unprocessable entity
        case 423: return MAKE_HTTP_HRESULT(423); // Locked
        case 424: return MAKE_HTTP_HRESULT(424); // Failed dependency
        case 426: return MAKE_HTTP_HRESULT(426); // Upgrade required
        case 428: return MAKE_HTTP_HRESULT(428); // Precondition required
        case 429: return MAKE_HTTP_HRESULT(429); // Too many requests
        case 431: return MAKE_HTTP_HRESULT(431); // Request header fields too large
        case 449: return MAKE_HTTP_HRESULT(449); // Retry with
        case 451: return MAKE_HTTP_HRESULT(451); // Unavailable for legal reasons

        case 500: return HTTP_E_STATUS_SERVER_ERROR;
        case 501: return HTTP_E_STATUS_NOT_SUPPORTED;
        case 502: return HTTP_E_STATUS_BAD_GATEWAY;
        case 503: return HTTP_E_STATUS_SERVICE_UNAVAIL;
        case 504: return HTTP_E_STATUS_GATEWAY_TIMEOUT;
        case 505: return HTTP_E_STATUS_VERSION_NOT_SUP;
        case 506: return MAKE_HTTP_HRESULT(506); // Variant also negotiates
        case 507: return MAKE_HTTP_HRESULT(507); // Insufficient storage
        case 508: return MAKE_HTTP_HRESULT(508); // Loop detected
        case 510: return MAKE_HTTP_HRESULT(510); // Not extended
        case 511: return MAKE_HTTP_HRESULT(511); // Network authentication required

        default: return HTTP_E_STATUS_UNEXPECTED;
        }
    }
}

HRESULT CurrentExceptionToHR()
{
    try
    {
        throw;
    }
    // std exceptions
    catch (const std::bad_alloc&) // is an exception
    {
        return E_OUTOFMEMORY;
    }
    catch (const std::bad_cast&) // is an exception
    {
        return E_NOINTERFACE;
    }
    catch (const std::invalid_argument&) // is a logic_error
    {
        return E_INVALIDARG;
    }
    catch (const std::out_of_range&) // is a logic_error
    {
        return E_BOUNDS;
    }
    catch (const std::length_error&) // is a logic_error
    {
        return __HRESULT_FROM_WIN32(ERROR_BAD_LENGTH);
    }
    catch (const std::overflow_error&) // is a runtime_error
    {
        return __HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW);
    }
    catch (const std::underflow_error&) // is a runtime_error
    {
        return __HRESULT_FROM_WIN32(ERROR_ARITHMETIC_OVERFLOW);
    }
    catch (const std::range_error&) // is a runtime_error
    {
        return E_BOUNDS;
    }
    catch (const std::system_error& ex) // is a runtime_error
    {
        if (ex.code().category() == std::system_category())
        {
            return __HRESULT_FROM_WIN32(ex.code().value());
        }
        else
        {
            return ex.code().value();
        }
    }
    catch (const std::logic_error&) // is an exception
    {
        return E_UNEXPECTED;
    }
    catch (const std::runtime_error&) // is an exception
    {
        return E_FAIL;
    }
    catch (const std::exception&) // base class for standard C++ exceptions
    {
        return E_FAIL;
    }
    catch (HRESULT exceptionHR)
    {
        return exceptionHR;
    }
    catch (...) // everything else
    {
        return E_FAIL;
    }
}

}
