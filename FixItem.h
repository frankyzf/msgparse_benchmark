//
// Created by feng on 14/06/15.
//

#ifndef PARSEFIXMSG_FIXITEM_H
#define PARSEFIXMSG_FIXITEM_H


#include "common.h"

class FixItem {
public:

    FixItem()=default;
    FixItem(int tag, const string &value) :
            tag(tag), value(value) { }

    operator bool() {return tag > 0;}

    int getTag() const {
        return tag;
    }

    void setTag(int tag) {
        FixItem::tag = tag;
    }

    const string &getValue() const {
        return value;
    }

    void setValue(const string &value) {
        FixItem::value = value;
    }
protected:
    int tag;
    string value;

};


#endif //PARSEFIXMSG_FIXITEM_H
