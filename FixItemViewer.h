//
// Created by feng on 14/06/15.
//

#ifndef PARSEFIXMSG_FIXITEMVIEWER_H
#define PARSEFIXMSG_FIXITEMVIEWER_H


class FixItemViewer {

public:
    FixItemViewer()=default;

    FixItemViewer(int tag, size_t valStart, size_t valEnd) : tag(tag), valStart(valStart), valEnd(valEnd) { }

    operator bool(){return tag > 0;}

protected:
    int tag;
    size_t valStart;
    size_t valEnd;
};


#endif //PARSEFIXMSG_FIXITEMVIEWER_H
