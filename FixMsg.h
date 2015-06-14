//
// Created by feng on 14/06/15.
//

#ifndef PARSEFIXMSG_FIXMSG_H
#define PARSEFIXMSG_FIXMSG_H

#include "common.h"
#include "FixItem.h"

class FixMsg {
public:
    FixMsg(const string &rawmsg) : rawMsg(rawmsg), cur(0), len(rawmsg.length()) { }
    const string &getRawMsg() const {
        return rawMsg;
    }
    FixItem getNextItem();
protected:
    string rawMsg;
    size_t cur;
    size_t len;

    friend struct FixItem;

};


#endif //PARSEFIXMSG_FIXMSG_H
