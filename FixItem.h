//
// Created by feng on 14/06/15.
//

#ifndef PARSEFIXMSG_FIXITEM_H
#define PARSEFIXMSG_FIXITEM_H


#include "common.h"

class FixItem {
public:

    FixItem()=default;
    FixItem(int tag, const string &value, bool valid) : tag(tag), value(value), valid(valid) { }

    operator bool() {return valid;}

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

    bool isValid() const {
        return valid;
    }

    void setValid(bool valid) {
        FixItem::valid = valid;
    }

protected:
    int tag;
    string value;
    bool valid;

};


#endif //PARSEFIXMSG_FIXITEM_H
