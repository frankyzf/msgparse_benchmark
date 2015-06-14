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
                         rawMsg.substr(sp+1, vp-sp-1), true};
            cur = vp;
            return item;
        }
    }
    return FixItem{};
}
