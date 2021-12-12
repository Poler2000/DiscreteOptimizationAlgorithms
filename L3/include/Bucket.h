//
// Created by pawel on 12.12.2021.
//

#ifndef L3_BUCKET_H
#define L3_BUCKET_H

struct Bucket {
    long minLabel;
    long maxLabel;
    std::vector<std::list<int>> content;
    bool empty = true;
};

#endif //L3_BUCKET_H
