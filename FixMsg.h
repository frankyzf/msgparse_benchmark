//
// Created by feng on 14/06/15.
//

#ifndef PARSEFIXMSG_FIXMSG_H
#define PARSEFIXMSG_FIXMSG_H


#include "common.h"
#include "FixItem.h"
#include "FixItemViewer.h"

class FixMsg {
public:
    FixMsg(const string &rawmsg) :
            rawMsg(rawmsg), cur(0), len(rawmsg.length()),
            parsed(false){ }
    const string &getRawMsg() const {
        return rawMsg;
    }
    FixItem getNextItem();
    FixItemViewer getNextItemViewer();
    FixItemViewer getCachedNextItemViewer();
    void ParsingAll();

    FixItemViewer getNextItemViewer_SIMD();
    pair<int,int> getSplitPosition(int p);

protected:
    string rawMsg;
    size_t cur;
    size_t len;

    bool parsed;
    queue<FixItemViewer> items;
    friend struct FixItem;

};


#endif //PARSEFIXMSG_FIXMSG_H
