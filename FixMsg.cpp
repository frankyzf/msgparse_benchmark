//
// Created by feng on 14/06/15.
//

#include "FixMsg.h"
#include "FixItem.h"

FixItem FixMsg::getNextItem() {
    if(cur < len) {
        size_t sp = cur;
        while (sp < len && rawMsg[sp++] != tagDelim);
        if(sp > cur) {
            size_t vp = sp;
            while (vp < len && rawMsg[vp++] != valDelim);
            FixItem item {atoi(rawMsg.substr(cur, sp-cur).c_str()),
                         rawMsg.substr(sp+1, vp-sp-1) };
            cur = vp;
            return item;
        }
    }
    return FixItem(-1, "");
}

FixItemViewer FixMsg::getNextItemViewer() {
    if(cur < len) {
        size_t sp = cur;
        while (sp < len && rawMsg[sp++] != tagDelim);
        if(sp > cur) {
            size_t vp = sp;
            while (vp < len && rawMsg[vp++] != valDelim);
            FixItemViewer item {atoi(rawMsg.substr(cur, sp-cur).c_str()),
                         sp+1, vp};
            cur = vp;
            return item;
        }
    }
    return FixItemViewer(-1, 0, 0);
}


void FixMsg::ParsingAll() {
    while(cur < len)
    {
        size_t sp = cur;
        while (sp < len && rawMsg[sp++] != tagDelim);
        if(sp > cur) {
            size_t vp = sp;
            while (vp < len && rawMsg[vp++] != valDelim);
            items.push( FixItemViewer(atoi(rawMsg.substr(cur, sp-cur).c_str()),
                                sp+1, vp) );
            cur = vp+1;
        }
    }
}

FixItemViewer FixMsg::getCachedNextItemViewer() {
    if(!parsed)
    {
        ParsingAll();
        parsed = true;
    }

    if(items.size() > 0) {
        auto ret = items.front();
        items.pop();
        return ret;
    }
    else
        return FixItemViewer(-1,0,0);
}
