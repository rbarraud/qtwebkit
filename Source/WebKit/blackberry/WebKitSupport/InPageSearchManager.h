/*
 * Copyright (C) 2012 Research In Motion Limited. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef InPageSearchManager_h
#define InPageSearchManager_h

#include "WTFString.h"

#include <wtf/RefPtr.h>

namespace WebCore {
class Range;
}

namespace BlackBerry {

namespace WebKit {

class WebPagePrivate;

class InPageSearchManager {
public:
    InPageSearchManager(WebPagePrivate*);
    ~InPageSearchManager();

    bool findNextString(const String& text, bool forward);

private:
    void clearTextMatches();
    void setMarkerActive(WebCore::Range*, bool active);

    WebPagePrivate* m_webPage;
    RefPtr<WebCore::Range> m_activeMatch;
    String m_activeSearchString;
    int m_activeMatchCount;
};

}
}

#endif // InPageSearchManager_h
