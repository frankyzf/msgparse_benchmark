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
            cur = vp;
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




FixItemViewer FixMsg::getNextItemViewer_SIMD() {
    if(cur < len)
    {
        pair<int, int> pp = getSplitPosition(cur);
        if(pp.first >=0 ){
            int oldcur = cur;
            cur = pp.second;
            return FixItemViewer(
                    atoi(rawMsg.substr(oldcur, pp.first - oldcur).c_str()),
                    pp.first+1, pp.second);
        }
    }
    return FixItemViewer(-1, 0, 0);
}


pair<int, int> FixMsg::getSplitPosition(int p) {
    // 16-byte align to the next boundary
    auto ret = make_pair(-1,-1);
    const char* nextAligned = reinterpret_cast<const char*>(
            (reinterpret_cast<size_t>(&rawMsg[p]) + 15) & ~15);
    //first check the unaligned data;
    while (&rawMsg[p] != nextAligned) {
        if (rawMsg[p] == '=')
            ret.first = p;
        else if (rawMsg[p] == '\001') {
            ret.second = p;
            return ret;
        }
    }
    static const char delimiter[16] = "=\001";
    const __m128i w = _mm_load_si128((const __m128i *)&delimiter[0]);
    for (; p<len; p += 16) {
        const __m128i s = _mm_load_si128((const __m128i *)&rawMsg[p]);
        unsigned r = _mm_cvtsi128_si32(
                _mm_cmpistrm(w, s,
                             _SIDD_UBYTE_OPS |
                             _SIDD_CMP_EQUAL_ANY |
                             _SIDD_BIT_MASK ));
        if (r >0 ) {

            int a = p + __builtin_ffs(r) - 1;
            if (rawMsg[a] == '='){
                ret.first = a;
                r = r & ~(1 < (16-__builtin_ffs(r)));
                a = p + __builtin_ffs(r) - 1;
            }
            if (rawMsg[a] == '\001') {
                ret.second =  a;
                return ret;
            }
        }
    }
        
}
